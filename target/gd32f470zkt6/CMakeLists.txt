cmake_minimum_required(VERSION 3.10)

# set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR cortex-m4)
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(bc600_mcuboot VERSION 1.0.0)


SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_BUILD_TYPE "Release")

# 判断操作系统类型
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    message("当前操作系统为 Windows")
	set(COMPILE_PATH "C:/DevTools/GNU Arm Embedded Toolchain/10 2021.10/bin")
    set(CMAKE_C_COMPILER ${COMPILE_PATH}/arm-none-eabi-gcc.exe)
    set(CMAKE_ASM_COMPILER ${COMPILE_PATH}/arm-none-eabi-gcc.exe)
    set(CMAKE_CXX_COMPILER ${COMPILE_PATH}/arm-none-eabi-g++.exe)
    set(CMAKE_OBJCOPY ${COMPILE_PATH}/arm-none-eabi-objcopy.exe)
    set(CMAKE_SIZE ${COMPILE_PATH}/arm-none-eabi-size.exe)
else()
    message("当前操作系统为 *Unix")
    set(COMPILE_PATH "/Applications/ARM/bin" )
    set(CMAKE_C_COMPILER ${COMPILE_PATH}/arm-none-eabi-gcc)
    set(CMAKE_ASM_COMPILER ${COMPILE_PATH}/arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER ${COMPILE_PATH}/arm-none-eabi-g++)
    set(CMAKE_OBJCOPY ${COMPILE_PATH}/arm-none-eabi-objcopy)
    set(CMAKE_SIZE ${COMPILE_PATH}/arm-none-eabi-size)
endif()


# -Wall: 启用大多数常见的警告。这有助于发现潜在的问题和改进代码质量。
# -Wno-unknown-pragmas: 禁用对未知的 #pragma 的警告。有时，代码中可能包含针对特定编译器的 #pragma 指令，这可能导致一些编译器不认识的警告。这个选项告诉编译器忽略这些未知的 #pragma。
# -Dgcc: 定义一个名为 gcc 的宏。这可以在代码中使用条件编译指令，例如 #ifdef gcc 或 #ifndef gcc。
# -O0: 禁用优化。这样编译器将生成未经优化的代码，方便调试和调查问题。
# -gdwarf-2: 生成 DWARF 调试信息格式的调试信息。DWARF 是一种调试信息标准，用于在编译后的二进制文件中包含源代码和变量的调试信息。
# -g: 启用调试信息的生成。这个选项告诉编译器在生成的二进制文件中包含调试信息，以便在调试时能够进行符号级的调试。
SET(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections")
set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall  -Wno-unknown-pragmas -Dgcc -O0 -gdwarf-2 -g")  # -Wextra
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -Wall -Wno-unknown-pragmas  -Dgcc -O0 -gdwarf-2 -g") # -Wextra
set(CMAKE_ASM_FLAGS " -c ${MCU_FLAGS} -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g2 -ggdb")
# SET(CMAKE_C_FLAGS_RELEASE "-O3")
# set(CMAKE_C_COMPILER_WORKS TRUE)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_COMPILER_WORKS TRUE)


SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/script/linker_scripts/link.ld)
set(CMAKE_EXE_LINKER_FLAGS " ${MCU_FLAGS} -Wl,--gc-sections,-Map=${PROJECT_NAME}.map,-cref,-u,Reset_Handler -T ${LINKER_SCRIPT}")
# SET(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs -specs=nosys.specs -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref -Wl,--gc-sections")
set(CMAKE_CXX_STANDARD 14)


set(PRJ_ROOT_DIR "../../")

include_directories(
	${PRJ_ROOT_DIR}/aft_bsp_gd32/gd32_drivers
	${PRJ_ROOT_DIR}/aft_bsp_gd32/GD32F4xx_Firmware_Library/CMSIS
	${PRJ_ROOT_DIR}/aft_bsp_gd32/GD32F4xx_Firmware_Library/CMSIS/GD/GD32F4xx/Include
	${PRJ_ROOT_DIR}/aft_bsp_gd32/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Include

	${PRJ_ROOT_DIR}/aft_sdk/src
	${PRJ_ROOT_DIR}/aft_sdk/components/drivers
	${PRJ_ROOT_DIR}/aft_sdk/components/3rdparty/fal/inc
	${PRJ_ROOT_DIR}/aft_sdk/components/3rdparty/mcuboot/bootutil/include
	${PRJ_ROOT_DIR}/aft_sdk/components/3rdparty/mcuboot/bootutil/src
	${PRJ_ROOT_DIR}/aft_sdk/components/3rdparty/mcuboot/ext/tinycrypt/lib/include
	
	${PRJ_ROOT_DIR}/app
	${PRJ_ROOT_DIR}/target/gd32f470zkt6/board
	${PRJ_ROOT_DIR}/target/gd32f470zkt6/board/fal_porting
	${PRJ_ROOT_DIR}/target/gd32f470zkt6/board/mcuboot_porting/include
)

ADD_DEFINITIONS(
	-DUSE_STDPERIPH_DRIVER
	-DGD32F470
)

set(PROJECT_SOURCES

	${PRJ_ROOT_DIR}/app/app_main.c

	${PRJ_ROOT_DIR}/target/gd32f470zkt6/board/system_gd32f4xx.c
	${PRJ_ROOT_DIR}/target/gd32f470zkt6/board/sdk_board.c
	${PRJ_ROOT_DIR}/target/gd32f470zkt6/board/mcuboot_porting/src/flash_map_backend/flash_map_backend.c
	${PRJ_ROOT_DIR}/target/gd32f470zkt6/board/fal_porting/fal_flash_w25qxx_port.c
	
	${PRJ_ROOT_DIR}/aft_bsp_gd32/GD32F4xx_Firmware_Library/CMSIS/GD/GD32F4xx/Source/GCC/startup_gd32f4xx.s
	
    
	# ${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_i2c.c
	${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_syscfg.c
	${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_exti.c
	${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_gpio.c
	${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_rcu.c
	${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_misc.c
	${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_usart.c
	${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/GD32F4xx_standard_peripheral/Source/gd32f4xx_dma.c
	${CHIPLIB_DIR}/libraries/GD32F4xx_Firmware_Library/CMSIS/GD/GD32F4xx/Source/system_gd32f4xx.c

    ${RTOS_DIR}/libcpu/arm/common/div0.c
	${RTOS_DIR}/libcpu/arm/common/showmem.c
	${RTOS_DIR}/libcpu/arm/cortex-m4/context_gcc.S
	${RTOS_DIR}/libcpu/arm/cortex-m4/cpuport.c
    
    ${RTOS_DIR}/components/libc/compilers/common/cctype.c
	${RTOS_DIR}/components/libc/compilers/common/cstdlib.c
	${RTOS_DIR}/components/libc/compilers/common/cstring.c
	${RTOS_DIR}/components/libc/compilers/common/ctime.c
	${RTOS_DIR}/components/libc/compilers/common/cunistd.c
	${RTOS_DIR}/components/libc/compilers/common/cwchar.c
	${RTOS_DIR}/components/libc/compilers/newlib/syscalls.c
	${RTOS_DIR}/components/drivers/core/device.c
	${RTOS_DIR}/components/drivers/hwtimer/hwtimer.c
	# ${RTOS_DIR}/components/drivers/i2c/i2c-bit-ops.c
	# ${RTOS_DIR}/components/drivers/i2c/i2c_core.c
	# ${RTOS_DIR}/components/drivers/i2c/i2c_dev.c
	${RTOS_DIR}/components/drivers/ipc/completion.c
	${RTOS_DIR}/components/drivers/ipc/dataqueue.c
	${RTOS_DIR}/components/drivers/ipc/pipe.c
	${RTOS_DIR}/components/drivers/ipc/ringblk_buf.c
	${RTOS_DIR}/components/drivers/ipc/ringbuffer.c
	${RTOS_DIR}/components/drivers/ipc/waitqueue.c
	${RTOS_DIR}/components/drivers/ipc/workqueue.c
	${RTOS_DIR}/components/drivers/misc/pin.c
	${RTOS_DIR}/components/drivers/serial/serial.c
	${RTOS_DIR}/components/finsh/shell.c
	${RTOS_DIR}/components/finsh/msh.c
	${RTOS_DIR}/components/finsh/msh_parse.c
	${RTOS_DIR}/components/finsh/cmd.c

	${RTOS_DIR}/src/clock.c
	${RTOS_DIR}/src/components.c
	${RTOS_DIR}/src/idle.c
	${RTOS_DIR}/src/ipc.c
	${RTOS_DIR}/src/irq.c
	${RTOS_DIR}/src/kservice.c
	${RTOS_DIR}/src/mem.c
	${RTOS_DIR}/src/mempool.c
	${RTOS_DIR}/src/object.c
	${RTOS_DIR}/src/scheduler_up.c
	${RTOS_DIR}/src/thread.c
	${RTOS_DIR}/src/timer.c

)

add_executable(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})
# add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
# COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin 
# COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

# SET(ELF_FILE ${CMAKE_SOURCE_DIR}/build/bin/${PROJECT_NAME}.elf)
# SET(HEX_FILE ${CMAKE_SOURCE_DIR}/build/bin/${PROJECT_NAME}.hex)
# SET(BIN_FILE ${CMAKE_SOURCE_DIR}/build/bin/${PROJECT_NAME}.bin)

SET(ELF_FILE bin/${PROJECT_NAME}.elf)
SET(HEX_FILE bin/${PROJECT_NAME}.hex)
SET(BIN_FILE bin/${PROJECT_NAME}.bin)

get_filename_component(BIN_FILE_NAME ${BIN_FILE} NAME)
get_filename_component(HEX_FILE_NAME ${HEX_FILE} NAME)
get_filename_component(ELF_FILE_NAME ${ELF_FILE} NAME)

# message("binfile = ${BIN_FILE}" )
# message("binfilename = ${BIN_FILE_NAME}")

add_custom_command(TARGET "${PROJECT_NAME}.elf" POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Oihex  ${ELF_FILE} ${HEX_FILE}
    COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"

    # COMMAND ${CMAKE_SIZE} --format=berkeley ${ELF_FILE} ${HEX_FILE} 
    # COMMAND ${CMAKE_SIZE} --format=sysv ${ELF_FILE} ${HEX_FILE}
    # COMMAND ${CMAKE_SIZE} --format=posix ${ELF_FILE} ${HEX_FILE}
    COMMAND ${CMAKE_SIZE} --format=gnu ${ELF_FILE} ${HEX_FILE} 
    
    COMMENT "Invoking: Cross ARM GNU Print Size" )