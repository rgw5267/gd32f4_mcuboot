#!/bin/bash

# 获取第一个参数
first_param=$1
# size=0xF0000        # 设置flash大小为 960kB，擦除的时候要用
# app_addr=0x08010000 # 设置falsh起始地址，一般32系列单片机都是0x08000000
size=0x300000                  # 设置flash大小为 3072kB，擦除的时候要用
app_addr=0x08000000          # 设置falsh起始地址，一般32系列单片机都是0x08000000
project_name="rtthread_demo" # 修改工程名称，换个工程必须进行此操作

# 判断第一个参数的值
if [ "$first_param" = "erase" ]; then
    # 在这里添加执行 擦除 操作的命令
    echo " ---erase mcu from $app_addr,size is $size ..."
    openocd -f mcu/gd32f4x_app_addr.cfg -c "init" -c "reset init" -c "halt" \
        -c "flash erase_address $app_addr $size" \
        -c "exit"

# elif [ "$first_param" = "boot" ]; then
#     # 烧录 bootloader
#     echo " --- program bootloader to mcu ..."
#     openocd -f mcu/openocd_gdlink_gd32f4xx.cfg -c "program mcu/boottloader_stm32f407ve_0x10000.bin 0x08000000 verify reset exit "

# elif [ "$first_param" = "app2" ]; then
#     echo " --- program app to mcu ...\n"
#     openocd -f mcu/openocd_gdlink_gd32f4xx.cfg \
#         -c "init" -c "reset init" -c "halt" \
#         -c "flash erase_address $app_addr $size " \
#         -c "flash write_image build/bin/rtthread_demo.bin $app_addr " \
#         -c "reset" -c "exit"
else
    # 默认 烧录
    echo " --- program app to mcu ..."
    openocd -f mcu/gd32f4x_app_addr.cfg -c "program build/bin/${project_name}.bin $app_addr verify reset exit "
fi



# ############################### 20231217 核定指令 #############################

## 查看目标芯片
# openocd -f mcu/stm32f4x_default_addr.cfg  -c "init;targets;"

# 下载bootloader
# openocd -f mcu/stm32f4x_default_addr.cfg  -c "program build/bootloader.bin 0x08000000 verify reset exit "

###  烧录应用程序，使用前请确保设定对的偏移地址
# elf文件 不能给起始地址，默认从0x08000000开始下载；给了地址，出错
# bin文件 必须给起始地址，从给定地址烧录； 不给地址，校验出错，下载不进去

# 烧录方法一[推荐]
# openocd -f mcu/stm32f4x_app_addr.cfg  -c "program build/bin/rtthread_demo.bin 0x08004000 verify reset exit "

# 烧录方法二
# openocd -f mcu/stm32f4x_default_addr.cfg \
#     -c "init" -c "reset init" -c "halt" \
#     -c "flash erase_address $app_addr $size " \
#     -c "flash write_image build/bin/rtthread_demo.bin 0x08004000 " \
#     -c "reset" -c "exit"

# 擦除: 从指定地址擦除
# flash erase_address [起始地址] [长度]
# openocd -f mcu/stm32f4x_default_addr.cfg -c "init" -c "reset init" -c "halt" \
#     -c "flash erase_address $app_addr $size" \
#     -c "reset" -c "exit"
