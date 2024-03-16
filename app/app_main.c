/**
 * Copyright (c) 2022 Infinitech Technology Co., Ltd
 * 
 * Change Logs:
 * Date           Author       Notes
 * {data}         rgw          first version
 */
#include "aft_sdk.h"
#include "sdk_board.h"
#include "SEGGER_RTT.h"
#include "fal.h"

#include <bootutil/bootutil.h>
#include "bootutil/image.h"

#define DBG_LVL DBG_LOG
#define DBG_TAG "main"
#include "sdk_log.h"

///* retarget the C library printf function to the USART */
//int fputc(int ch, FILE *f)
//{
//    SEGGER_RTT_PutChar(0, (uint8_t)ch);
//    return ch;
//}


void JumpToApp(uint32_t AppAddr)
{
  void (*SysMemBootJump)(void);
    

  SysTick->CTRL = 0;
  SysTick->LOAD = 0;
  SysTick->VAL = 0;


  __set_PRIMASK(1);
    

  for (uint32_t i = 0; i < 8; i++)
  {
    NVIC->ICER[i]=0xFFFFFFFF;
    NVIC->ICPR[i]=0xFFFFFFFF;
  } 


  __set_PRIMASK(0);


  SysMemBootJump = (void (*)(void)) (*((uint32_t *) (AppAddr + 4)));


  __set_MSP(*(uint32_t *)AppAddr);


  __set_CONTROL(0);


  SysMemBootJump(); 

  while (1)
  {

  }
}

struct arm_vector_table {
    uint32_t msp;
    uint32_t reset;
};


/**
  * @brief ?? image
  * @param struct boot_rsp * rsp: 
  * retval N/A.
  */
static void do_boot(struct boot_rsp * rsp)
{
    struct arm_vector_table *vt;
    const struct fal_partition *fal_part = NULL;

    fal_part = fal_partition_find("primary");

    uint32_t image_off = MCU_FLASH_START_ADRESS + fal_part->offset + rsp->br_image_off;
    uint32_t raw_imgae_off = image_off + rsp->br_hdr->ih_hdr_size;
    LOG_I("imgae_off=0x%x flashid=%d", image_off, rsp->br_flash_dev_id);
    LOG_I("raw_imgae_off=0x%x", raw_imgae_off);

    JumpToApp(raw_imgae_off);

//    vt = (struct arm_vector_table *)(raw_imgae_off);
//    SysTick->CTRL = 0;

//    SCB->VTOR = (uint32_t)vt;
//    __set_MSP(*(__IO uint32_t *)vt->msp);
//    ((void (*)(void))vt->reset)();

//    while(1)
//    {
//        rt_thread_mdelay(500);
//    }
}


int main(void)
{

    struct boot_rsp rsp;
    fih_int fih_rc = FIH_FAILURE;
    
    board_init();
    LOG_D("Hello SDK\n");
//    JumpToApp(0x08021000);
    fal_init();
//    boot_set_pending(0);
    // MCUboot validates the application images and prepares the booting process.
    FIH_CALL(boot_go, fih_rc, &rsp);

    if (FIH_NOT_EQ(fih_rc, FIH_SUCCESS)) {
        LOG_E("Unable to find bootable image");
        FIH_PANIC; // infinite loop
    }
    
    do_boot(&rsp);
    while(1)
    {
    }
}
