/*
 * Aspeed ADC
 *
 * Copyright 2017-2021 IBM Corp.
 *
 * Andrew Jeffery <andrew@aj.id.au>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef HW_ADC_ASPEED_ADC_H
#define HW_ADC_ASPEED_ADC_H

#include "hw/sysbus.h"

#define TYPE_ASPEED_ADC "aspeed.adc"
#define TYPE_ASPEED_2400_ADC TYPE_ASPEED_ADC "-ast2400"
#define TYPE_ASPEED_2500_ADC TYPE_ASPEED_ADC "-ast2500"
#define TYPE_ASPEED_2600_ADC TYPE_ASPEED_ADC "-ast2600"
OBJECT_DECLARE_TYPE(AspeedADCState, AspeedADCClass, ASPEED_ADC)

#define TYPE_ASPEED_ADC_ENGINE "aspeed.adc.engine"
OBJECT_DECLARE_SIMPLE_TYPE(AspeedADCEngineState, ASPEED_ADC_ENGINE)

#define ASPEED_ADC_NR_CHANNELS 16

typedef struct AspeedADCEngineState {
    /* <private> */
    SysBusDevice parent;

    MemoryRegion mmio;
    qemu_irq irq;
    uint32_t engine_id;
    uint32_t ch_off;

    uint32_t engine_ctrl;
    uint32_t irq_ctrl;
    uint32_t vga_detect_ctrl;
    uint32_t adc_clk_ctrl;
    uint32_t channels[ASPEED_ADC_NR_CHANNELS / 2];
    uint32_t bounds[ASPEED_ADC_NR_CHANNELS];
    uint32_t hysteresis[ASPEED_ADC_NR_CHANNELS];
    uint32_t irq_src;
    uint32_t comp_trim;
} AspeedADCEngineState;

typedef struct AspeedADCState {
    /* <private> */
    SysBusDevice parent;

    MemoryRegion mmio;
    qemu_irq irq;

    AspeedADCEngineState engines[2];
} AspeedADCState;

struct AspeedADCClass {
    SysBusDeviceClass parent_class;

    uint8_t nr_engines;
};

#endif /* HW_ADC_ASPEED_ADC_H */
