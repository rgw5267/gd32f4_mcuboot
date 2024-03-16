#! /bin/bash

# imgtool.py 位置
IMGTOOL_PY="D:\Documents\Code\uml\bc600_mcuboot\aft_sdk\src\3rdparty\mcuboot\scripts\imgtool.py"

# 输入文件
INPUT_FILE="d:\Downloads\GD32F4xx_Firmware_Library_V3.2.0\GD32F4xx_Firmware_Library_V3.2.0\Template\Keil_project\Project.bin"

# 输出文件
OUTPUT_FILE="D:\Downloads\GD32F4xx_Firmware_Library_V3.2.0\GD32F4xx_Firmware_Library_V3.2.0\Template\Keil_project\signed_Project.bin"

# key
KEY_FILE="D:\Documents\Code\uml\bc600_mcuboot\target\gd32f470zkt6\board\mcuboot_porting\src\keys\ed25519.pem"

# 执行签名命令
python $IMGTOOL_PY sign \
  --key $KEY_FILE \
  --public-key-format hash \
  --version 1.0.0 \
  --header-size 0x1000 \
  --align 4 \
  --slot-size 0x40000 \
  --pad-header \
  $INPUT_FILE $OUTPUT_FILE

echo "签名成功：$OUTPUT_FILE"
