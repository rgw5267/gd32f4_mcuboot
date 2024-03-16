#! /bin/bash

# imgtool.py 位置
IMGTOOL_PY="D:\Documents\Code\uml\bc600_mcuboot\aft_sdk\src\3rdparty\mcuboot\scripts\imgtool.py"

# 输入文件
INPUT_FILE="d:\Downloads\GD32F4xx_Firmware_Library_V3.2.0\GD32F4xx_Firmware_Library_V3.2.0\Template\Keil_project\Project.bin"

# 输出文件
OUTPUT_TEST_FILE="D:\Downloads\GD32F4xx_Firmware_Library_V3.2.0\GD32F4xx_Firmware_Library_V3.2.0\Template\Keil_project\upgrade_test_signed_Project.bin"
OUTPUT_CONFIRM_FILE="D:\Downloads\GD32F4xx_Firmware_Library_V3.2.0\GD32F4xx_Firmware_Library_V3.2.0\Template\Keil_project\upgrade_confirm_signed_Project.bin"

# key
KEY_FILE="D:\Documents\Code\uml\bc600_mcuboot\target\gd32f470zkt6\board\mcuboot_porting\src\keys\ed25519.pem"

# 执行签名命令
python $IMGTOOL_PY sign \
  --key $KEY_FILE \
  --public-key-format hash \
  --version 1.0.0 \
  --header-size 0x1000 \
  --pad-header \
  --slot-size 0x60000 \
  --pad \
  --align 4 \
  $INPUT_FILE $OUTPUT_TEST_FILE

# 执行签名命令
python $IMGTOOL_PY sign \
  --key $KEY_FILE \
  --public-key-format hash \
  --version 1.0.0 \
  --header-size 0x1000 \
  --pad-header \
  --slot-size 0x60000 \
  --pad \
  --align 4 \
  --confirm \
  $INPUT_FILE $OUTPUT_CONFIRM_FILE

echo "签名成功"
