/*
 * Copyright (c) 2018 Open Source Foundries Limited
 * Copyright (c) 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __MCUBOOT_CONFIG_H__
#define __MCUBOOT_CONFIG_H__

/*
 * Signature types
 */
// #define MCUBOOT_SIGN_EC256
#define MCUBOOT_SIGN_ED25519
#define HAVE_KEYS

/*
 * Upgrade mode
 *
 * The default is to support A/B image swapping with rollback.  Other modes
 * with simpler code path, which only supports overwriting the existing image
 * with the update image or running the newest image directly from its flash
 * partition, are also available.
 *
 * You can enable only one mode at a time from the list below to override
 * the default upgrade mode.
 */
// #  define MCUBOOT_SWAP_USING_MOVE 1
/* Uncomment to enable the overwrite-only code path. */
#define MCUBOOT_OVERWRITE_ONLY

#ifdef MCUBOOT_OVERWRITE_ONLY
/* Uncomment to only erase and overwrite those primary slot sectors needed
 * to install the new image, rather than the entire image slot. */
#define MCUBOOT_OVERWRITE_ONLY_FAST
#endif


#define MCUBOOT_USE_MBED_TLS
// #define MCUBOOT_USE_TINYCRYPT

/*
 * Always check the signature of the image in the primary slot before booting,
 * even if no upgrade was performed. This is recommended if the boot
 * time penalty is acceptable.
 */
#define MCUBOOT_VALIDATE_PRIMARY_SLOT

/*
 * Flash abstraction
 */

/*
 * Enabling this option uses newer flash map APIs. This saves RAM and
 * avoids deprecated API usage.
*/
#define MCUBOOT_USE_FLASH_AREA_GET_SECTORS //uses newer flash map APIs

/* Default maximum number of flash sectors per image slot; change
 * as desirable. */
#define MCUBOOT_MAX_IMG_SECTORS 3

/* Default number of separately updateable images; change in case of
 * multiple images. */
#define MCUBOOT_IMAGE_NUMBER 1 //Only one image (two slots) supported for now

/*
 * Logging
 */

/*
 * If logging is enabled the following functions must be defined by the
 * platform:
 *
 *    MCUBOOT_LOG_MODULE_REGISTER(domain)
 *      Register a new log module and add the current C file to it.
 *
 *    MCUBOOT_LOG_MODULE_DECLARE(domain)
 *      Add the current C file to an existing log module.
 *
 *    MCUBOOT_LOG_ERR(...)
 *    MCUBOOT_LOG_WRN(...)
 *    MCUBOOT_LOG_INF(...)
 *    MCUBOOT_LOG_DBG(...)
 *
 * The function priority is:
 *
 *    MCUBOOT_LOG_ERR > MCUBOOT_LOG_WRN > MCUBOOT_LOG_INF > MCUBOOT_LOG_DBG
 */
#define MCUBOOT_HAVE_LOGGING 1

/*
 * Assertions
 */

/* Uncomment if your platform has its own mcuboot_config/mcuboot_assert.h.
 * If so, it must provide an ASSERT macro for use by bootutil. Otherwise,
 * "assert" is used. */
#define MCUBOOT_HAVE_ASSERT_H

/*
 * Watchdog feeding
 */

/* This macro might be implemented if the OS / HW watchdog is enabled while
 * doing a swap upgrade and the time it takes for a swapping is long enough
 * to cause an unwanted reset. If implementing this, the OS main.c must also
 * enable the watchdog (if required)!
 *
 * #define MCUBOOT_WATCHDOG_FEED()
 *    do { do watchdog feeding here! } while (0)
 */

/* If a OS ports support single thread mode or is bare-metal then:
 * This macro implements call that switches CPU to an idle state, from which
 * the CPU may be woken up by, for example, UART transmission event.
 * 
 * Otherwise this macro should be no-op.
 */
#define MCUBOOT_CPU_IDLE() \
    do {                   \
    } while (0)

#define MCUBOOT_WATCHDOG_FEED() \
    do {                        \
    } while(0)
#endif /* __MCUBOOT_CONFIG_H__ */
