/**
 * Change Logs:
 * Date           Author          Notes
 * 2024-01-19     rgw             first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include "sdk_board.h"

#define FAL_PART_HAS_TABLE_CFG

#define FAL_USING_ONCHIP_FLASH_DEV_NAME           "onchip_flash"
#define FAL_USING_NOR_FLASH_DEV_NAME              "norflash0"

/* ===================== Flash device Configuration ========================= */
extern struct fal_flash_dev nor_flash0;
extern const struct fal_flash_dev onchip_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &onchip_flash0,                                                  \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {FAL_PART_MAGIC_WORD, "boot"      , FAL_USING_ONCHIP_FLASH_DEV_NAME, 0         , 64  * 1024, 0}, \
    {FAL_PART_MAGIC_WORD, "params"    , FAL_USING_ONCHIP_FLASH_DEV_NAME, 64  * 1024, 64  * 1024, 0}, \
    {FAL_PART_MAGIC_WORD, "primary"   , FAL_USING_ONCHIP_FLASH_DEV_NAME, 128 * 1024, 384 * 1024, 0}, \
    {FAL_PART_MAGIC_WORD, "secondary" , FAL_USING_ONCHIP_FLASH_DEV_NAME, 512 * 1024, 384 * 1024, 0}, \
    {FAL_PART_MAGIC_WORD, "scratch"   , FAL_USING_ONCHIP_FLASH_DEV_NAME, 896 * 1024, 128 * 1024, 0}, \
}

#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
