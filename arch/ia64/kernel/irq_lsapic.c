/*
 * LSAPIC Interrupt Controller
 *
 * This takes care of interrupts that are generated by the CPU's
 * internal Streamlined Advanced Programmable Interrupt Controller
 * (LSAPIC), such as the ITC and IPI interrupts.
    *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 2000 Hewlett-Packard Co
 * Copyright (C) 2000 David Mosberger-Tang <davidm@hpl.hp.com>
 */

#include <linux/sched.h>
#include <linux/irq.h>

static unsigned int
lsapic_noop_startup (struct irq_data *data)
{
    return 0;
}

static void
lsapic_noop (struct irq_data *data)
{
    /* nothing to do... */
}

static int lsapic_retrigger(struct irq_data *data)
{
    ia64_resend_irq(data->irq);

    return 1;
}

struct irq_chip irq_type_ia64_lsapic = {
    .name =			"LSAPIC",
    .irq_startup =		lsapic_noop_startup,
    .irq_shutdown =		lsapic_noop,
    .irq_enable =		lsapic_noop,
    .irq_disable =		lsapic_noop,
    .irq_ack =		lsapic_noop,
    .irq_retrigger =	lsapic_retrigger,
};
