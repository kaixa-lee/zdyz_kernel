/*
 * clkt_clksel.c - OMAP2/3/4 clksel clock functions
 *
 * Copyright (C) 2005-2008 Texas Instruments, Inc.
 * Copyright (C) 2004-2010 Nokia Corporation
 *
 * Contacts:
 * Richard Woodruff <r-woodruff2@ti.com>
 * Paul Walmsley
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 * clksel clocks are clocks that do not have a fixed parent, or that
 * can divide their parent's rate, or possibly both at the same time, based
 * on the contents of a hardware register bitfield.
 *
 * All of the various mux and divider settings can be encoded into
 * struct clksel* data structures, and then these can be autogenerated
 * from some hardware database for each new chip generation.  This
 * should avoid the need to write, review, and validate a lot of new
 * clock code for each new chip, since it can be exported from the SoC
 * design flow.  This is now done on OMAP4.
 *
 * The fusion of mux and divider clocks is a software creation.  In
 * hardware reality, the multiplexer (parent selection) and the
 * divider exist separately.  XXX At some point these clksel clocks
 * should be split into "divider" clocks and "mux" clocks to better
 * match the hardware.
 *
 * (The name "clksel" comes from the name of the corresponding
 * register field in the OMAP2/3 family of SoCs.)
 *
 * XXX Currently these clocks are only used in the OMAP2/3/4 code, but
 * many of the OMAP1 clocks should be convertible to use this
 * mechanism.
 */
#undef DEBUG

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/clk-provider.h>
#include <linux/io.h>
#include <linux/bug.h>

#include "clock.h"

/* Private functions */

/**
 * _get_clksel_by_parent() - return clksel struct for a given clk & parent
 * @clk: OMAP struct clk ptr to inspect
 * @src_clk: OMAP struct clk ptr of the parent clk to search for
 *
 * Scan the struct clksel array associated with the clock to find
 * the element associated with the supplied parent clock address.
 * Returns a pointer to the struct clksel on success or NULL on error.
 */
static const struct clksel *_get_clksel_by_parent(struct clk_hw_omap *clk,
        struct clk *src_clk)
{
    const struct clksel *clks;

    if (!src_clk) {
        return NULL;
    }

    for (clks = clk->clksel; clks->parent; clks++)
        if (clks->parent == src_clk) {
            break;    /* Found the requested parent */
        }

    if (!clks->parent) {
        /* This indicates a data problem */
        WARN(1, "clock: %s: could not find parent clock %s in clksel array\n",
             __clk_get_name(clk->hw.clk), __clk_get_name(src_clk));
        return NULL;
    }

    return clks;
}

/**
 * _write_clksel_reg() - program a clock's clksel register in hardware
 * @clk: struct clk * to program
 * @v: clksel bitfield value to program (with LSB at bit 0)
 *
 * Shift the clksel register bitfield value @v to its appropriate
 * location in the clksel register and write it in.  This function
 * will ensure that the write to the clksel_reg reaches its
 * destination before returning -- important since PRM and CM register
 * accesses can be quite slow compared to ARM cycles -- but does not
 * take into account any time the hardware might take to switch the
 * clock source.
 */
static void _write_clksel_reg(struct clk_hw_omap *clk, u32 field_val)
{
    u32 v;

    v = omap2_clk_readl(clk, clk->clksel_reg);
    v &= ~clk->clksel_mask;
    v |= field_val << __ffs(clk->clksel_mask);
    omap2_clk_writel(v, clk, clk->clksel_reg);

    v = omap2_clk_readl(clk, clk->clksel_reg); /* OCP barrier */
}

/**
 * _clksel_to_divisor() - turn clksel field value into integer divider
 * @clk: OMAP struct clk to use
 * @field_val: register field value to find
 *
 * Given a struct clk of a rate-selectable clksel clock, and a register field
 * value to search for, find the corresponding clock divisor.  The register
 * field value should be pre-masked and shifted down so the LSB is at bit 0
 * before calling.  Returns 0 on error or returns the actual integer divisor
 * upon success.
 */
static u32 _clksel_to_divisor(struct clk_hw_omap *clk, u32 field_val)
{
    const struct clksel *clks;
    const struct clksel_rate *clkr;
    struct clk *parent;

    parent = __clk_get_parent(clk->hw.clk);

    clks = _get_clksel_by_parent(clk, parent);
    if (!clks) {
        return 0;
    }

    for (clkr = clks->rates; clkr->div; clkr++) {
        if (!(clkr->flags & cpu_mask)) {
            continue;
        }

        if (clkr->val == field_val) {
            break;
        }
    }

    if (!clkr->div) {
        /* This indicates a data error */
        WARN(1, "clock: %s: could not find fieldval %d for parent %s\n",
             __clk_get_name(clk->hw.clk), field_val,
             __clk_get_name(parent));
        return 0;
    }

    return clkr->div;
}

/**
 * _divisor_to_clksel() - turn clksel integer divisor into a field value
 * @clk: OMAP struct clk to use
 * @div: integer divisor to search for
 *
 * Given a struct clk of a rate-selectable clksel clock, and a clock
 * divisor, find the corresponding register field value.  Returns the
 * register field value _before_ left-shifting (i.e., LSB is at bit
 * 0); or returns 0xFFFFFFFF (~0) upon error.
 */
static u32 _divisor_to_clksel(struct clk_hw_omap *clk, u32 div)
{
    const struct clksel *clks;
    const struct clksel_rate *clkr;
    struct clk *parent;

    /* should never happen */
    WARN_ON(div == 0);

    parent = __clk_get_parent(clk->hw.clk);
    clks = _get_clksel_by_parent(clk, parent);
    if (!clks) {
        return ~0;
    }

    for (clkr = clks->rates; clkr->div; clkr++) {
        if (!(clkr->flags & cpu_mask)) {
            continue;
        }

        if (clkr->div == div) {
            break;
        }
    }

    if (!clkr->div) {
        pr_err("clock: %s: could not find divisor %d for parent %s\n",
               __clk_get_name(clk->hw.clk), div,
               __clk_get_name(parent));
        return ~0;
    }

    return clkr->val;
}

/**
 * _read_divisor() - get current divisor applied to parent clock (from hdwr)
 * @clk: OMAP struct clk to use.
 *
 * Read the current divisor register value for @clk that is programmed
 * into the hardware, convert it into the actual divisor value, and
 * return it; or return 0 on error.
 */
static u32 _read_divisor(struct clk_hw_omap *clk)
{
    u32 v;

    if (!clk->clksel || !clk->clksel_mask) {
        return 0;
    }

    v = omap2_clk_readl(clk, clk->clksel_reg);
    v &= clk->clksel_mask;
    v >>= __ffs(clk->clksel_mask);

    return _clksel_to_divisor(clk, v);
}

/* Public functions */

/**
 * omap2_clksel_round_rate_div() - find divisor for the given clock and rate
 * @clk: OMAP struct clk to use
 * @target_rate: desired clock rate
 * @new_div: ptr to where we should store the divisor
 *
 * Finds 'best' divider value in an array based on the source and target
 * rates.  The divider array must be sorted with smallest divider first.
 * This function is also used by the DPLL3 M2 divider code.
 *
 * Returns the rounded clock rate or returns 0xffffffff on error.
 */
u32 omap2_clksel_round_rate_div(struct clk_hw_omap *clk,
                                unsigned long target_rate,
                                u32 *new_div)
{
    unsigned long test_rate;
    const struct clksel *clks;
    const struct clksel_rate *clkr;
    u32 last_div = 0;
    struct clk *parent;
    unsigned long parent_rate;
    const char *clk_name;

    parent = __clk_get_parent(clk->hw.clk);
    clk_name = __clk_get_name(clk->hw.clk);
    parent_rate = __clk_get_rate(parent);

    if (!clk->clksel || !clk->clksel_mask) {
        return ~0;
    }

    pr_debug("clock: clksel_round_rate_div: %s target_rate %ld\n",
             clk_name, target_rate);

    *new_div = 1;

    clks = _get_clksel_by_parent(clk, parent);
    if (!clks) {
        return ~0;
    }

    for (clkr = clks->rates; clkr->div; clkr++) {
        if (!(clkr->flags & cpu_mask)) {
            continue;
        }

        /* Sanity check */
        if (clkr->div <= last_div)
            pr_err("clock: %s: clksel_rate table not sorted\n",
                   clk_name);

        last_div = clkr->div;

        test_rate = parent_rate / clkr->div;

        if (test_rate <= target_rate) {
            break;    /* found it */
        }
    }

    if (!clkr->div) {
        pr_err("clock: %s: could not find divisor for target rate %ld for parent %s\n",
               clk_name, target_rate, __clk_get_name(parent));
        return ~0;
    }

    *new_div = clkr->div;

    pr_debug("clock: new_div = %d, new_rate = %ld\n", *new_div,
             (parent_rate / clkr->div));

    return parent_rate / clkr->div;
}

/*
 * Clocktype interface functions to the OMAP clock code
 * (i.e., those used in struct clk field function pointers, etc.)
 */

/**
 * omap2_clksel_find_parent_index() - return the array index of the current
 * hardware parent of @hw
 * @hw: struct clk_hw * to find the current hardware parent of
 *
 * Given a struct clk_hw pointer @hw to the 'hw' member of a struct
 * clk_hw_omap record representing a source-selectable hardware clock,
 * read the hardware register and determine what its parent is
 * currently set to.  Intended to be called only by the common clock
 * framework struct clk_hw_ops.get_parent function pointer.  Return
 * the array index of this parent clock upon success -- there is no
 * way to return an error, so if we encounter an error, just WARN()
 * and pretend that we know that we're doing.
 */
u8 omap2_clksel_find_parent_index(struct clk_hw *hw)
{
    struct clk_hw_omap *clk = to_clk_hw_omap(hw);
    const struct clksel *clks;
    const struct clksel_rate *clkr;
    u32 r, found = 0;
    struct clk *parent;
    const char *clk_name;
    int ret = 0, f = 0;

    parent = __clk_get_parent(hw->clk);
    clk_name = __clk_get_name(hw->clk);

    /* XXX should be able to return an error */
    WARN((!clk->clksel || !clk->clksel_mask),
         "clock: %s: attempt to call on a non-clksel clock", clk_name);

    r = omap2_clk_readl(clk, clk->clksel_reg) & clk->clksel_mask;
    r >>= __ffs(clk->clksel_mask);

    for (clks = clk->clksel; clks->parent && !found; clks++) {
        for (clkr = clks->rates; clkr->div && !found; clkr++) {
            if (!(clkr->flags & cpu_mask)) {
                continue;
            }

            if (clkr->val == r) {
                found = 1;
                ret = f;
            }
        }
        f++;
    }

    /* This indicates a data error */
    WARN(!found, "clock: %s: init parent: could not find regval %0x\n",
         clk_name, r);

    return ret;
}


/**
 * omap2_clksel_recalc() - function ptr to pass via struct clk .recalc field
 * @clk: struct clk *
 *
 * This function is intended to be called only by the clock framework.
 * Each clksel clock should have its struct clk .recalc field set to this
 * function.  Returns the clock's current rate, based on its parent's rate
 * and its current divisor setting in the hardware.
 */
unsigned long omap2_clksel_recalc(struct clk_hw *hw, unsigned long parent_rate)
{
    unsigned long rate;
    u32 div = 0;
    struct clk_hw_omap *clk = to_clk_hw_omap(hw);

    if (!parent_rate) {
        return 0;
    }

    div = _read_divisor(clk);
    if (!div) {
        rate = parent_rate;
    } else {
        rate = parent_rate / div;
    }

    pr_debug("%s: recalc'd %s's rate to %lu (div %d)\n", __func__,
             __clk_get_name(hw->clk), rate, div);

    return rate;
}

/**
 * omap2_clksel_round_rate() - find rounded rate for the given clock and rate
 * @clk: OMAP struct clk to use
 * @target_rate: desired clock rate
 *
 * This function is intended to be called only by the clock framework.
 * Finds best target rate based on the source clock and possible dividers.
 * rates. The divider array must be sorted with smallest divider first.
 *
 * Returns the rounded clock rate or returns 0xffffffff on error.
 */
long omap2_clksel_round_rate(struct clk_hw *hw, unsigned long target_rate,
                             unsigned long *parent_rate)
{
    struct clk_hw_omap *clk = to_clk_hw_omap(hw);
    u32 new_div;

    return omap2_clksel_round_rate_div(clk, target_rate, &new_div);
}

/**
 * omap2_clksel_set_rate() - program clock rate in hardware
 * @clk: struct clk * to program rate
 * @rate: target rate to program
 *
 * This function is intended to be called only by the clock framework.
 * Program @clk's rate to @rate in the hardware.  The clock can be
 * either enabled or disabled when this happens, although if the clock
 * is enabled, some downstream devices may glitch or behave
 * unpredictably when the clock rate is changed - this depends on the
 * hardware. This function does not currently check the usecount of
 * the clock, so if multiple drivers are using the clock, and the rate
 * is changed, they will all be affected without any notification.
 * Returns -EINVAL upon error, or 0 upon success.
 */
int omap2_clksel_set_rate(struct clk_hw *hw, unsigned long rate,
                          unsigned long parent_rate)
{
    struct clk_hw_omap *clk = to_clk_hw_omap(hw);
    u32 field_val, validrate, new_div = 0;

    if (!clk->clksel || !clk->clksel_mask) {
        return -EINVAL;
    }

    validrate = omap2_clksel_round_rate_div(clk, rate, &new_div);
    if (validrate != rate) {
        return -EINVAL;
    }

    field_val = _divisor_to_clksel(clk, new_div);
    if (field_val == ~0) {
        return -EINVAL;
    }

    _write_clksel_reg(clk, field_val);

    pr_debug("clock: %s: set rate to %ld\n", __clk_get_name(hw->clk),
             __clk_get_rate(hw->clk));

    return 0;
}

/*
 * Clksel parent setting function - not passed in struct clk function
 * pointer - instead, the OMAP clock code currently assumes that any
 * parent-setting clock is a clksel clock, and calls
 * omap2_clksel_set_parent() by default
 */

/**
 * omap2_clksel_set_parent() - change a clock's parent clock
 * @clk: struct clk * of the child clock
 * @new_parent: struct clk * of the new parent clock
 *
 * This function is intended to be called only by the clock framework.
 * Change the parent clock of clock @clk to @new_parent.  This is
 * intended to be used while @clk is disabled.  This function does not
 * currently check the usecount of the clock, so if multiple drivers
 * are using the clock, and the parent is changed, they will all be
 * affected without any notification.  Returns -EINVAL upon error, or
 * 0 upon success.
 */
int omap2_clksel_set_parent(struct clk_hw *hw, u8 field_val)
{
    struct clk_hw_omap *clk = to_clk_hw_omap(hw);

    if (!clk->clksel || !clk->clksel_mask) {
        return -EINVAL;
    }

    _write_clksel_reg(clk, field_val);
    return 0;
}
