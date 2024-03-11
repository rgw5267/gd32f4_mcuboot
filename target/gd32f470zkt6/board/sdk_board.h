/**
 * Change Logs:
 * Date           Author          Notes
 * 2023-06-15     rgw             first version
 */

#ifndef __SDK_BOARD_H
#define __SDK_BOARD_H

#include "gd32f4xx.h"
//#include "stm32l0xx_ll_flash.h"
//#include "main.h"

#include "aft_sdk.h"
#include "sdk_uart.h"
#include "sdk_rtc.h"
#include "sdk_adc.h"
#include "sdk_watchdog.h"
#include "sdk_common.h"
#include "sdk_flash.h"
#include "sdk_swi2c.h"

#include "app_main.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Hardware Drivers Config */

#define SOC_SERIES_STM32F4xx
// #define SOC_CHIP_STM32L071xC

#define MCU_FLASH_SIZE             (1 * 1024 * 1024)
#define MCU_FLASH_PAGE_SIZE        (128 * 1024)

#define MCU_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define MCU_FLASH_END_ADDRESS      ((uint32_t)(MCU_FLASH_START_ADRESS + MCU_FLASH_SIZE))


extern sdk_uart_t lpuart;
extern sdk_uart_t uart1;
extern sdk_uart_t uart2;
extern sdk_uart_t uart5;
extern sdk_rtc_t rtc;
extern sdk_adc_t adc;
extern sdk_watchdog_t wdt;
extern sdk_flash_t gd32_onchip_flash;
extern sdk_swi2c_t swi2c1;

#define uart_net     lpuart
#define uart_bl      uart2
#define uart_gnss    uart1
#define uart_rs485   uart5
#define onchip_flash gd32_onchip_flash

#define assert SDK_ASSERT

void board_init(void);

void board_power_gpio_init(void);
void board_power_on(void);
void board_power_off(void);

#ifdef __cplusplus
}
#endif

#endif /* __SDK_BOARD_H */
