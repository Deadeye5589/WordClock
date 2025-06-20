/*-----------------------------------------------------------------------------------------------------------------------------------------------
 * onewire.h - onewire lib
 *
 * Copyright (c) 2015-2024 Frank Meyer - frank(at)uclock.de
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *-----------------------------------------------------------------------------------------------------------------------------------------------
 */
#ifndef ONEWIRE_H
#define ONEWIRE_H

#if defined (STM32F1XX)
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#elif defined (STM32F4XX)
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#endif

#include "misc.h"
#include <string.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------
// One-Wire ROM codes
//-----------------------------------------------------------------------------------------------------------------------------------------------
#define  ONEWIRE_READ_ROM_CMD       0x33                                 // read ROM code
#define  ONEWIRE_MATCH_ROM_CMD      0x55                                 // select a slave

extern uint_fast8_t                 onewire_reset (void);
extern uint_fast8_t                 onewire_read_bit (void);
extern uint8_t                      onewire_read_byte (void);
extern void                         onewire_read (uint8_t *, uint8_t);
extern void                         onewire_write_byte (uint8_t);
extern void                         onewire_write (uint8_t *, uint8_t);
extern uint_fast8_t                 onewire_get_rom_code (uint8_t *);
extern uint_fast8_t                 onewirte_read_rom_code (void);
extern void                         onewire_init (void);

#endif
