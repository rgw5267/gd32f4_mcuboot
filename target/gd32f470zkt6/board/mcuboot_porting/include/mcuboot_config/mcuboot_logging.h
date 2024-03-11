#ifndef __MCUBOOT_LOGGING_H
#define __MCUBOOT_LOGGING_H

/****************************************************************************
 * Included Files
 ****************************************************************************/


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define MCUBOOT_LOG_MODULE_DECLARE(...)
#define MCUBOOT_LOG_MODULE_REGISTER(...)

extern void sdklog(char *level, char *module, const char *format, ...);
#define MCUBOOT_LOG_ERR(format, ...) \
    sdklog("ERROR", "boot", format, ##__VA_ARGS__)

#define MCUBOOT_LOG_WRN(format, ...) \
    sdklog("WARN", "boot", format, ##__VA_ARGS__)

#define MCUBOOT_LOG_INF(format, ...) \
    sdklog("INFO", "boot", format, ##__VA_ARGS__)

#define MCUBOOT_LOG_DBG(format, ...) \
    sdklog("DEBUG", "boot", format, ##__VA_ARGS__)

#endif /* __MCUBOOT_LOGGING_H */
