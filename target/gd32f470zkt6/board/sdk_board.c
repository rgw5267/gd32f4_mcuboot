/**
 * Change Logs:
 * Date           Author          Notes
 * 2023-06-15     rgw             first version
 */

#include "aft_sdk.h"
#include "sdk_board.h"

#define DBG_TAG "board"
#define DBG_LVL DBG_LOG
#include "sdk_log.h"

volatile uint32_t systicks = 0;

void board_power_gpio_init(void)
{

}

void board_power_on(void)
{

}
void board_power_off(void)
{

}

void SysTick_Handler(void)
{
    systicks++;
}

void SystemClock_Config(void)
{
    SysTick_Config(SystemCoreClock / SDK_SYSTICK_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, 0);
}

void board_init(void)
{
    SystemClock_Config();
}
