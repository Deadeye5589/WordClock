/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * ws2812.h - interface declarations of WS2812 driver
 *
 * Copyright (c) 2014-2024 Frank Meyer - frank(at)uclock.de
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#ifndef WS2812_H
#define WS2812_H

#if defined (STM32F10X)
#  include "stm32f10x.h"
#  include "stm32f10x_gpio.h"
#  include "stm32f10x_rcc.h"
#  include "stm32f10x_tim.h"
#  include "stm32f10x_dma.h"
#elif defined (STM32F4XX)
#  include "stm32f4xx.h"
#  include "stm32f4xx_gpio.h"
#  include "stm32f4xx_rcc.h"
#  include "stm32f4xx_tim.h"
#  include "stm32f4xx_dma.h"
#endif

#include "misc.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * RGB LED color definition
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} TFTLED_RGB;

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * TFTLED interface definition
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
extern void     tftled_layout (uint_fast8_t);
extern void     tftled_layout_get_line (char *);
extern void     tftled_init (void);
extern void     tftled_refresh (uint_fast16_t);
extern void     tftled_set_led (uint_fast16_t, TFTLED_RGB *);
extern void     tftled_set_all_leds (TFTLED_RGB *, uint_fast16_t, uint_fast8_t);

#endif
