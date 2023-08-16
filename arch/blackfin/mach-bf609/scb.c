/*
 * arch/blackfin/mach-common/scb-init.c - reprogram system cross bar priority
 *
 * Copyright 2012 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <asm/blackfin.h>
#include <asm/scb.h>

struct scb_mi_prio scb_data[] = {
#ifdef CONFIG_SCB0_MI0
    {
        REG_SCB0_ARBR0, REG_SCB0_ARBW0, 32, {
            CONFIG_SCB0_MI0_SLOT0,
            CONFIG_SCB0_MI0_SLOT1,
            CONFIG_SCB0_MI0_SLOT2,
            CONFIG_SCB0_MI0_SLOT3,
            CONFIG_SCB0_MI0_SLOT4,
            CONFIG_SCB0_MI0_SLOT5,
            CONFIG_SCB0_MI0_SLOT6,
            CONFIG_SCB0_MI0_SLOT7,
            CONFIG_SCB0_MI0_SLOT8,
            CONFIG_SCB0_MI0_SLOT9,
            CONFIG_SCB0_MI0_SLOT10,
            CONFIG_SCB0_MI0_SLOT11,
            CONFIG_SCB0_MI0_SLOT12,
            CONFIG_SCB0_MI0_SLOT13,
            CONFIG_SCB0_MI0_SLOT14,
            CONFIG_SCB0_MI0_SLOT15,
            CONFIG_SCB0_MI0_SLOT16,
            CONFIG_SCB0_MI0_SLOT17,
            CONFIG_SCB0_MI0_SLOT18,
            CONFIG_SCB0_MI0_SLOT19,
            CONFIG_SCB0_MI0_SLOT20,
            CONFIG_SCB0_MI0_SLOT21,
            CONFIG_SCB0_MI0_SLOT22,
            CONFIG_SCB0_MI0_SLOT23,
            CONFIG_SCB0_MI0_SLOT24,
            CONFIG_SCB0_MI0_SLOT25,
            CONFIG_SCB0_MI0_SLOT26,
            CONFIG_SCB0_MI0_SLOT27,
            CONFIG_SCB0_MI0_SLOT28,
            CONFIG_SCB0_MI0_SLOT29,
            CONFIG_SCB0_MI0_SLOT30,
            CONFIG_SCB0_MI0_SLOT31
        },
    },
#endif
#ifdef CONFIG_SCB0_MI1
    {
        REG_SCB0_ARBR1, REG_SCB0_ARBW1, 32, {
            CONFIG_SCB0_MI1_SLOT0,
            CONFIG_SCB0_MI1_SLOT1,
            CONFIG_SCB0_MI1_SLOT2,
            CONFIG_SCB0_MI1_SLOT3,
            CONFIG_SCB0_MI1_SLOT4,
            CONFIG_SCB0_MI1_SLOT5,
            CONFIG_SCB0_MI1_SLOT6,
            CONFIG_SCB0_MI1_SLOT7,
            CONFIG_SCB0_MI1_SLOT8,
            CONFIG_SCB0_MI1_SLOT9,
            CONFIG_SCB0_MI1_SLOT10,
            CONFIG_SCB0_MI1_SLOT11,
            CONFIG_SCB0_MI1_SLOT12,
            CONFIG_SCB0_MI1_SLOT13,
            CONFIG_SCB0_MI1_SLOT14,
            CONFIG_SCB0_MI1_SLOT15,
            CONFIG_SCB0_MI1_SLOT16,
            CONFIG_SCB0_MI1_SLOT17,
            CONFIG_SCB0_MI1_SLOT18,
            CONFIG_SCB0_MI1_SLOT19,
            CONFIG_SCB0_MI1_SLOT20,
            CONFIG_SCB0_MI1_SLOT21,
            CONFIG_SCB0_MI1_SLOT22,
            CONFIG_SCB0_MI1_SLOT23,
            CONFIG_SCB0_MI1_SLOT24,
            CONFIG_SCB0_MI1_SLOT25,
            CONFIG_SCB0_MI1_SLOT26,
            CONFIG_SCB0_MI1_SLOT27,
            CONFIG_SCB0_MI1_SLOT28,
            CONFIG_SCB0_MI1_SLOT29,
            CONFIG_SCB0_MI1_SLOT30,
            CONFIG_SCB0_MI1_SLOT31
        },
    },
#endif
#ifdef CONFIG_SCB0_MI2
    {
        REG_SCB0_ARBR2, REG_SCB0_ARBW2, 32, {
            CONFIG_SCB0_MI2_SLOT0,
            CONFIG_SCB0_MI2_SLOT1,
            CONFIG_SCB0_MI2_SLOT2,
            CONFIG_SCB0_MI2_SLOT3,
            CONFIG_SCB0_MI2_SLOT4,
            CONFIG_SCB0_MI2_SLOT5,
            CONFIG_SCB0_MI2_SLOT6,
            CONFIG_SCB0_MI2_SLOT7,
            CONFIG_SCB0_MI2_SLOT8,
            CONFIG_SCB0_MI2_SLOT9,
            CONFIG_SCB0_MI2_SLOT10,
            CONFIG_SCB0_MI2_SLOT11,
            CONFIG_SCB0_MI2_SLOT12,
            CONFIG_SCB0_MI2_SLOT13,
            CONFIG_SCB0_MI2_SLOT14,
            CONFIG_SCB0_MI2_SLOT15,
            CONFIG_SCB0_MI2_SLOT16,
            CONFIG_SCB0_MI2_SLOT17,
            CONFIG_SCB0_MI2_SLOT18,
            CONFIG_SCB0_MI2_SLOT19,
            CONFIG_SCB0_MI2_SLOT20,
            CONFIG_SCB0_MI2_SLOT21,
            CONFIG_SCB0_MI2_SLOT22,
            CONFIG_SCB0_MI2_SLOT23,
            CONFIG_SCB0_MI2_SLOT24,
            CONFIG_SCB0_MI2_SLOT25,
            CONFIG_SCB0_MI2_SLOT26,
            CONFIG_SCB0_MI2_SLOT27,
            CONFIG_SCB0_MI2_SLOT28,
            CONFIG_SCB0_MI2_SLOT29,
            CONFIG_SCB0_MI2_SLOT30,
            CONFIG_SCB0_MI2_SLOT31
        },
    },
#endif
#ifdef CONFIG_SCB0_MI3
    {
        REG_SCB0_ARBR3, REG_SCB0_ARBW3, 32, {
            CONFIG_SCB0_MI3_SLOT0,
            CONFIG_SCB0_MI3_SLOT1,
            CONFIG_SCB0_MI3_SLOT2,
            CONFIG_SCB0_MI3_SLOT3,
            CONFIG_SCB0_MI3_SLOT4,
            CONFIG_SCB0_MI3_SLOT5,
            CONFIG_SCB0_MI3_SLOT6,
            CONFIG_SCB0_MI3_SLOT7,
            CONFIG_SCB0_MI3_SLOT8,
            CONFIG_SCB0_MI3_SLOT9,
            CONFIG_SCB0_MI3_SLOT10,
            CONFIG_SCB0_MI3_SLOT11,
            CONFIG_SCB0_MI3_SLOT12,
            CONFIG_SCB0_MI3_SLOT13,
            CONFIG_SCB0_MI3_SLOT14,
            CONFIG_SCB0_MI3_SLOT15,
            CONFIG_SCB0_MI3_SLOT16,
            CONFIG_SCB0_MI3_SLOT17,
            CONFIG_SCB0_MI3_SLOT18,
            CONFIG_SCB0_MI3_SLOT19,
            CONFIG_SCB0_MI3_SLOT20,
            CONFIG_SCB0_MI3_SLOT21,
            CONFIG_SCB0_MI3_SLOT22,
            CONFIG_SCB0_MI3_SLOT23,
            CONFIG_SCB0_MI3_SLOT24,
            CONFIG_SCB0_MI3_SLOT25,
            CONFIG_SCB0_MI3_SLOT26,
            CONFIG_SCB0_MI3_SLOT27,
            CONFIG_SCB0_MI3_SLOT28,
            CONFIG_SCB0_MI3_SLOT29,
            CONFIG_SCB0_MI3_SLOT30,
            CONFIG_SCB0_MI3_SLOT31
        },
    },
#endif
#ifdef CONFIG_SCB0_MI4
    {
        REG_SCB0_ARBR4, REG_SCB4_ARBW0, 32, {
            CONFIG_SCB0_MI4_SLOT0,
            CONFIG_SCB0_MI4_SLOT1,
            CONFIG_SCB0_MI4_SLOT2,
            CONFIG_SCB0_MI4_SLOT3,
            CONFIG_SCB0_MI4_SLOT4,
            CONFIG_SCB0_MI4_SLOT5,
            CONFIG_SCB0_MI4_SLOT6,
            CONFIG_SCB0_MI4_SLOT7,
            CONFIG_SCB0_MI4_SLOT8,
            CONFIG_SCB0_MI4_SLOT9,
            CONFIG_SCB0_MI4_SLOT10,
            CONFIG_SCB0_MI4_SLOT11,
            CONFIG_SCB0_MI4_SLOT12,
            CONFIG_SCB0_MI4_SLOT13,
            CONFIG_SCB0_MI4_SLOT14,
            CONFIG_SCB0_MI4_SLOT15,
            CONFIG_SCB0_MI4_SLOT16,
            CONFIG_SCB0_MI4_SLOT17,
            CONFIG_SCB0_MI4_SLOT18,
            CONFIG_SCB0_MI4_SLOT19,
            CONFIG_SCB0_MI4_SLOT20,
            CONFIG_SCB0_MI4_SLOT21,
            CONFIG_SCB0_MI4_SLOT22,
            CONFIG_SCB0_MI4_SLOT23,
            CONFIG_SCB0_MI4_SLOT24,
            CONFIG_SCB0_MI4_SLOT25,
            CONFIG_SCB0_MI4_SLOT26,
            CONFIG_SCB0_MI4_SLOT27,
            CONFIG_SCB0_MI4_SLOT28,
            CONFIG_SCB0_MI4_SLOT29,
            CONFIG_SCB0_MI4_SLOT30,
            CONFIG_SCB0_MI4_SLOT31
        },
    },
#endif
#ifdef CONFIG_SCB0_MI5
    {
        REG_SCB0_ARBR5, REG_SCB0_ARBW5, 16, {
            CONFIG_SCB0_MI5_SLOT0,
            CONFIG_SCB0_MI5_SLOT1,
            CONFIG_SCB0_MI5_SLOT2,
            CONFIG_SCB0_MI5_SLOT3,
            CONFIG_SCB0_MI5_SLOT4,
            CONFIG_SCB0_MI5_SLOT5,
            CONFIG_SCB0_MI5_SLOT6,
            CONFIG_SCB0_MI5_SLOT7,
            CONFIG_SCB0_MI5_SLOT8,
            CONFIG_SCB0_MI5_SLOT9,
            CONFIG_SCB0_MI5_SLOT10,
            CONFIG_SCB0_MI5_SLOT11,
            CONFIG_SCB0_MI5_SLOT12,
            CONFIG_SCB0_MI5_SLOT13,
            CONFIG_SCB0_MI5_SLOT14,
            CONFIG_SCB0_MI5_SLOT15
        },
    },
#endif
#ifdef CONFIG_SCB1_MI0
    {
        REG_SCB1_ARBR0, REG_SCB1_ARBW0, 20, {
            CONFIG_SCB1_MI0_SLOT0,
            CONFIG_SCB1_MI0_SLOT1,
            CONFIG_SCB1_MI0_SLOT2,
            CONFIG_SCB1_MI0_SLOT3,
            CONFIG_SCB1_MI0_SLOT4,
            CONFIG_SCB1_MI0_SLOT5,
            CONFIG_SCB1_MI0_SLOT6,
            CONFIG_SCB1_MI0_SLOT7,
            CONFIG_SCB1_MI0_SLOT8,
            CONFIG_SCB1_MI0_SLOT9,
            CONFIG_SCB1_MI0_SLOT10,
            CONFIG_SCB1_MI0_SLOT11,
            CONFIG_SCB1_MI0_SLOT12,
            CONFIG_SCB1_MI0_SLOT13,
            CONFIG_SCB1_MI0_SLOT14,
            CONFIG_SCB1_MI0_SLOT15,
            CONFIG_SCB1_MI0_SLOT16,
            CONFIG_SCB1_MI0_SLOT17,
            CONFIG_SCB1_MI0_SLOT18,
            CONFIG_SCB1_MI0_SLOT19
        },
    },
#endif
#ifdef CONFIG_SCB2_MI0
    {
        REG_SCB2_ARBR0, REG_SCB2_ARBW0, 10, {
            CONFIG_SCB2_MI0_SLOT0,
            CONFIG_SCB2_MI0_SLOT1,
            CONFIG_SCB2_MI0_SLOT2,
            CONFIG_SCB2_MI0_SLOT3,
            CONFIG_SCB2_MI0_SLOT4,
            CONFIG_SCB2_MI0_SLOT5,
            CONFIG_SCB2_MI0_SLOT6,
            CONFIG_SCB2_MI0_SLOT7,
            CONFIG_SCB2_MI0_SLOT8,
            CONFIG_SCB2_MI0_SLOT9
        },
    },
#endif
#ifdef CONFIG_SCB3_MI0
    {
        REG_SCB3_ARBR0, REG_SCB3_ARBW0, 16, {
            CONFIG_SCB3_MI0_SLOT0,
            CONFIG_SCB3_MI0_SLOT1,
            CONFIG_SCB3_MI0_SLOT2,
            CONFIG_SCB3_MI0_SLOT3,
            CONFIG_SCB3_MI0_SLOT4,
            CONFIG_SCB3_MI0_SLOT5,
            CONFIG_SCB3_MI0_SLOT6,
            CONFIG_SCB3_MI0_SLOT7,
            CONFIG_SCB3_MI0_SLOT8,
            CONFIG_SCB3_MI0_SLOT9,
            CONFIG_SCB3_MI0_SLOT10,
            CONFIG_SCB3_MI0_SLOT11,
            CONFIG_SCB3_MI0_SLOT12,
            CONFIG_SCB3_MI0_SLOT13,
            CONFIG_SCB3_MI0_SLOT14,
            CONFIG_SCB3_MI0_SLOT15
        },
    },
#endif
#ifdef CONFIG_SCB4_MI0
    {
        REG_SCB4_ARBR0, REG_SCB4_ARBW0, 16, {
            CONFIG_SCB4_MI0_SLOT0,
            CONFIG_SCB4_MI0_SLOT1,
            CONFIG_SCB4_MI0_SLOT2,
            CONFIG_SCB4_MI0_SLOT3,
            CONFIG_SCB4_MI0_SLOT4,
            CONFIG_SCB4_MI0_SLOT5,
            CONFIG_SCB4_MI0_SLOT6,
            CONFIG_SCB4_MI0_SLOT7,
            CONFIG_SCB4_MI0_SLOT8,
            CONFIG_SCB4_MI0_SLOT9,
            CONFIG_SCB4_MI0_SLOT10,
            CONFIG_SCB4_MI0_SLOT11,
            CONFIG_SCB4_MI0_SLOT12,
            CONFIG_SCB4_MI0_SLOT13,
            CONFIG_SCB4_MI0_SLOT14,
            CONFIG_SCB4_MI0_SLOT15
        },
    },
#endif
#ifdef CONFIG_SCB5_MI0
    {
        REG_SCB5_ARBR0, REG_SCB5_ARBW0, 8, {
            CONFIG_SCB5_MI0_SLOT0,
            CONFIG_SCB5_MI0_SLOT1,
            CONFIG_SCB5_MI0_SLOT2,
            CONFIG_SCB5_MI0_SLOT3,
            CONFIG_SCB5_MI0_SLOT4,
            CONFIG_SCB5_MI0_SLOT5,
            CONFIG_SCB5_MI0_SLOT6,
            CONFIG_SCB5_MI0_SLOT7
        },
    },
#endif
#ifdef CONFIG_SCB6_MI0
    {
        REG_SCB6_ARBR0, REG_SCB6_ARBW0, 4, {
            CONFIG_SCB6_MI0_SLOT0,
            CONFIG_SCB6_MI0_SLOT1,
            CONFIG_SCB6_MI0_SLOT2,
            CONFIG_SCB6_MI0_SLOT3
        },
    },
#endif
#ifdef CONFIG_SCB7_MI0
    {
        REG_SCB7_ARBR0, REG_SCB7_ARBW0, 6, {
            CONFIG_SCB7_MI0_SLOT0,
            CONFIG_SCB7_MI0_SLOT1,
            CONFIG_SCB7_MI0_SLOT2,
            CONFIG_SCB7_MI0_SLOT3,
            CONFIG_SCB7_MI0_SLOT4,
            CONFIG_SCB7_MI0_SLOT5
        },
    },
#endif
#ifdef CONFIG_SCB8_MI0
    {
        REG_SCB8_ARBR0, REG_SCB8_ARBW0, 8, {
            CONFIG_SCB8_MI0_SLOT0,
            CONFIG_SCB8_MI0_SLOT1,
            CONFIG_SCB8_MI0_SLOT2,
            CONFIG_SCB8_MI0_SLOT3,
            CONFIG_SCB8_MI0_SLOT4,
            CONFIG_SCB8_MI0_SLOT5,
            CONFIG_SCB8_MI0_SLOT6,
            CONFIG_SCB8_MI0_SLOT7
        },
    },
#endif
#ifdef CONFIG_SCB9_MI0
    {
        REG_SCB9_ARBR0, REG_SCB9_ARBW0, 10, {
            CONFIG_SCB9_MI0_SLOT0,
            CONFIG_SCB9_MI0_SLOT1,
            CONFIG_SCB9_MI0_SLOT2,
            CONFIG_SCB9_MI0_SLOT3,
            CONFIG_SCB9_MI0_SLOT4,
            CONFIG_SCB9_MI0_SLOT5,
            CONFIG_SCB9_MI0_SLOT6,
            CONFIG_SCB9_MI0_SLOT7,
            CONFIG_SCB9_MI0_SLOT8,
            CONFIG_SCB9_MI0_SLOT9
        },
    },
#endif
    { 0, }
};
