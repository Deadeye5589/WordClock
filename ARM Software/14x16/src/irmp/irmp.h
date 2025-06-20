/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * irmp.h
 *
 * Copyright (c) 2009-2024 Frank Meyer - frank(at)uclock.de
 *
 * $Id: irmp.h,v 1.91 2015/01/26 12:50:02 fm Exp $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef _IRMP_H_
#define _IRMP_H_

#include "irmpsystem.h"

#ifndef IRMP_USE_AS_LIB
#  include "irmpconfig.h"
#endif

#if defined (ATMEL_AVR)
#  define _CONCAT(a,b)                          a##b
#  define CONCAT(a,b)                           _CONCAT(a,b)
#  define IRMP_PORT                             CONCAT(PORT, IRMP_PORT_LETTER)
#  define IRMP_DDR                              CONCAT(DDR, IRMP_PORT_LETTER)
#  define IRMP_PIN                              CONCAT(PIN, IRMP_PORT_LETTER)
#  define IRMP_BIT                              IRMP_BIT_NUMBER
#  define input(x)                              ((x) & (1 << IRMP_BIT))
#elif defined (PIC_C18)
#  define input(x)                              (x)
#elif defined (PIC_CCS)
#  define input(x)                              (x)
#elif defined (ARM_STM32)
#  define _CONCAT(a,b)                          a##b
#  define CONCAT(a,b)                           _CONCAT(a,b)
#  define IRMP_PORT                             CONCAT(GPIO, IRMP_PORT_LETTER)
#  if defined (ARM_STM32L1XX)
#    define IRMP_PORT_RCC                       CONCAT(RCC_AHBPeriph_GPIO, IRMP_PORT_LETTER)
#  elif defined (ARM_STM32F10X)
#    define IRMP_PORT_RCC                       CONCAT(RCC_APB2Periph_GPIO, IRMP_PORT_LETTER)
#  elif defined (ARM_STM32F4XX)
#    define IRMP_PORT_RCC                       CONCAT(RCC_AHB1Periph_GPIO, IRMP_PORT_LETTER)
#  endif
#  define IRMP_BIT                              CONCAT(GPIO_Pin_, IRMP_BIT_NUMBER)
#  define IRMP_PIN                              IRMP_PORT   // for use with input(x) below
#  define input(x)                              (GPIO_ReadInputDataBit(x, IRMP_BIT))
#  ifndef USE_STDPERIPH_DRIVER
#    warning The STM32 port of IRMP uses the ST standard peripheral drivers which are not enabled in your build configuration.
#  endif
#elif defined (STELLARIS_ARM_CORTEX_M4)
#  define _CONCAT(a,b)                          a##b
#  define CONCAT(a,b)                           _CONCAT(a,b)
#  define IRMP_PORT_PERIPH                      CONCAT(SYSCTL_PERIPH_GPIO, IRMP_PORT_LETTER)
#  define IRMP_PORT_BASE                        CONCAT(GPIO_PORT, CONCAT(IRMP_PORT_LETTER, _BASE))
#  define IRMP_PORT_PIN                         CONCAT(GPIO_PIN_, IRMP_BIT_NUMBER)
#  define IRMP_PIN                              IRMP_PORT_PIN
#  define input(x)                              ((uint8_t)(ROM_GPIOPinRead(IRMP_PORT_BASE, IRMP_PORT_PIN)))
#  define sei()                                 IntMasterEnable()
#endif

#if IRMP_SUPPORT_DENON_PROTOCOL == 1 && IRMP_SUPPORT_RUWIDO_PROTOCOL == 1
#  warning DENON protocol conflicts wih RUWIDO, please enable only one of both protocols
#  warning RUWIDO protocol disabled
#  undef IRMP_SUPPORT_RUWIDO_PROTOCOL
#  define IRMP_SUPPORT_RUWIDO_PROTOCOL          0
#endif

#if IRMP_SUPPORT_RC6_PROTOCOL == 1 && IRMP_SUPPORT_ROOMBA_PROTOCOL == 1
#  warning RC6 protocol conflicts wih ROOMBA, please enable only one of both protocols
#  warning ROOMBA protocol disabled
#  undef IRMP_SUPPORT_ROOMBA_PROTOCOL
#  define IRMP_SUPPORT_ROOMBA_PROTOCOL          0
#endif

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && IRMP_SUPPORT_ORTEK_PROTOCOL == 1
#  warning RC5 protocol conflicts wih ORTEK, please enable only one of both protocols
#  warning ORTEK protocol disabled
#  undef IRMP_SUPPORT_ORTEK_PROTOCOL
#  define IRMP_SUPPORT_ORTEK_PROTOCOL           0
#endif

#if IRMP_SUPPORT_FDC_PROTOCOL == 1 && IRMP_SUPPORT_ORTEK_PROTOCOL == 1
#  warning FDC protocol conflicts wih ORTEK, please enable only one of both protocols
#  warning ORTEK protocol disabled
#  undef IRMP_SUPPORT_ORTEK_PROTOCOL
#  define IRMP_SUPPORT_ORTEK_PROTOCOL           0
#endif

#if IRMP_SUPPORT_ORTEK_PROTOCOL == 1 && IRMP_SUPPORT_NETBOX_PROTOCOL == 1
#  warning ORTEK protocol conflicts wih NETBOX, please enable only one of both protocols
#  warning NETBOX protocol disabled
#  undef IRMP_SUPPORT_NETBOX_PROTOCOL
#  define IRMP_SUPPORT_NETBOX_PROTOCOL          0
#endif

#if IRMP_SUPPORT_SIEMENS_PROTOCOL == 1 && F_INTERRUPTS < 15000
#  warning F_INTERRUPTS too low, SIEMENS protocol disabled (should be at least 15000)
#  undef IRMP_SUPPORT_SIEMENS_PROTOCOL
#  define IRMP_SUPPORT_SIEMENS_PROTOCOL         0
#endif

#if IRMP_SUPPORT_RUWIDO_PROTOCOL == 1 && F_INTERRUPTS < 15000
#  warning F_INTERRUPTS too low, RUWIDO protocol disabled (should be at least 15000)
#  undef IRMP_SUPPORT_RUWIDO_PROTOCOL
#  define IRMP_SUPPORT_RUWIDO_PROTOCOL          0
#endif

#if IRMP_SUPPORT_RECS80_PROTOCOL == 1 && F_INTERRUPTS < 15000
#  warning F_INTERRUPTS too low, RECS80 protocol disabled (should be at least 15000)
#  undef IRMP_SUPPORT_RECS80_PROTOCOL
#  define IRMP_SUPPORT_RECS80_PROTOCOL          0
#endif

#if IRMP_SUPPORT_RECS80EXT_PROTOCOL == 1 && F_INTERRUPTS < 15000
#  warning F_INTERRUPTS too low, RECS80EXT protocol disabled (should be at least 15000)
#  undef IRMP_SUPPORT_RECS80EXT_PROTOCOL
#  define IRMP_SUPPORT_RECS80EXT_PROTOCOL       0
#endif

#if IRMP_SUPPORT_LEGO_PROTOCOL == 1 && F_INTERRUPTS < 20000
#  warning F_INTERRUPTS too low, LEGO protocol disabled (should be at least 20000)
#  undef IRMP_SUPPORT_LEGO_PROTOCOL
#  define IRMP_SUPPORT_LEGO_PROTOCOL            0
#endif

#if IRMP_SUPPORT_SAMSUNG48_PROTOCOL == 1 && IRMP_SUPPORT_SAMSUNG_PROTOCOL == 0
#  warning SAMSUNG48 protocol needs also SAMSUNG protocol, SAMSUNG protocol enabled
#  undef IRMP_SUPPORT_SAMSUNG_PROTOCOL
#  define IRMP_SUPPORT_SAMSUNG_PROTOCOL         1
#endif

#if IRMP_SUPPORT_JVC_PROTOCOL == 1 && IRMP_SUPPORT_NEC_PROTOCOL == 0
#  warning JVC protocol needs also NEC protocol, NEC protocol enabled
#  undef IRMP_SUPPORT_NEC_PROTOCOL
#  define IRMP_SUPPORT_NEC_PROTOCOL             1
#endif

#if IRMP_SUPPORT_NEC16_PROTOCOL == 1 && IRMP_SUPPORT_NEC_PROTOCOL == 0
#  warning NEC16 protocol needs also NEC protocol, NEC protocol enabled
#  undef IRMP_SUPPORT_NEC_PROTOCOL
#  define IRMP_SUPPORT_NEC_PROTOCOL             1
#endif

#if IRMP_SUPPORT_NEC42_PROTOCOL == 1 && IRMP_SUPPORT_NEC_PROTOCOL == 0
#  warning NEC42 protocol needs also NEC protocol, NEC protocol enabled
#  undef IRMP_SUPPORT_NEC_PROTOCOL
#  define IRMP_SUPPORT_NEC_PROTOCOL             1
#endif

#if IRMP_SUPPORT_LGAIR_PROTOCOL == 1 && IRMP_SUPPORT_NEC_PROTOCOL == 0
#  warning LGAIR protocol needs also NEC protocol, NEC protocol enabled
#  undef IRMP_SUPPORT_NEC_PROTOCOL
#  define IRMP_SUPPORT_NEC_PROTOCOL             1
#endif

#if IRMP_SUPPORT_RCMM_PROTOCOL == 1 && F_INTERRUPTS < 20000
#  warning F_INTERRUPTS too low, RCMM protocol disabled (should be at least 20000)
#  undef IRMP_SUPPORT_RCMM_PROTOCOL
#  define IRMP_SUPPORT_RCMM_PROTOCOL            0
#endif

#if F_INTERRUPTS > 20000
#error F_INTERRUPTS too high (should be not greater than 20000)
#endif

#include "irmpprotocols.h"

#define IRMP_FLAG_REPETITION            0x01

extern void                             irmp_init (void);
extern uint_fast8_t                     irmp_get_data (IRMP_DATA *);
extern uint_fast8_t                     irmp_is_busy (void);
extern uint_fast8_t                     irmp_ISR (void);

#if IRMP_PROTOCOL_NAMES == 1
extern const char * const               irmp_protocol_names[IRMP_N_PROTOCOLS + 1] PROGMEM;
#endif

#if IRMP_USE_CALLBACK == 1
extern void                             irmp_set_callback_ptr (void (*cb)(uint_fast8_t));
#endif // IRMP_USE_CALLBACK == 1

#endif /* _IRMP_H_ */
