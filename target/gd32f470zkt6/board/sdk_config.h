/**
 * Change Logs:
 * Date           Author          Notes
 * 2023-06-15     rgw             first version
 */

#ifndef __SDK_CONFIG_H
#define __SDK_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


/* os port config */
#define SDK_USE_NO_RTOS


#define SDK_SYSTICK_PER_SECOND 1000
#define SDK_UART_RX_FIFO_LEN    512

#define SDK_RTC_CLOCK_SELECT_LSI
// #define SDK_RTC_CLOCK_SELECT_LSE

/* at device */
#define AT_CMD_MAX_LEN (512)

//////////////////////SEGGER RTT Config
#define SEGGER_RTT_MAX_NUM_UP_BUFFERS             (1)     // Max. number of up-buffers (T->H) available on this target    (Default: 3)
#define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS           (1)     // Max. number of down-buffers (H->T) available on this target  (Default: 3)
#define BUFFER_SIZE_UP                            (512)  // Size of the buffer for terminal output of target, up to host (Default: 1k)
// #define SEGGER_RTT_MODE_DEFAULT                   SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL

///////////////////// modbus //////////////////////
#define MODBUS_BUF_SIZE 200

#ifdef __cplusplus
}
#endif

#endif /* __SDK_CONFIG_H */