#!/bin/bash

# 0) 检查是否存在build目录，如果不存在则创建
if [ ! -d "build" ]; then
  mkdir build
fi

# 1）进入build目录，编译，返回board目录
cd build

# 2）定义一些变量
os_type=$(uname -s)       # 获取操作系统类型
build_log="build_log.txt" # build 日志
build_start_timems=0      # 编译启动时间
build_end_timems=0        # 编译结束时间

# 判断操作系统类型
# if [ "$os_type" == "Linux" ]; then
#     echo "当前操作系统为 Linux"
# elif [ "$os_type" == "Darwin" ]; then
#     echo "当前操作系统为 macOS"

# 3）构建工程，并编译
if [[ "$os_type" == MINGW* ]]; then
    # windows
    echo "build: 当前操作系统为 Windows"
    cmake -G "MinGW Makefiles" ..                   # win操作系统需要用MinGW Makefiles
    build_start_timems=$(($(date +%s%N) / 1000000)) # 获取编译过程的启动时间
    mingw32-make -j4 2>&1 | tee $build_log          # 编译，并将编译结果保存在$build_log中，便于统计error和warning
    # mingw32-make -j4
    build_end_timems=$(($(date +%s%N) / 1000000))
else
    # *Unix
    echo "build: 当前操作系统类型: $os_type"
    cmake -G "Unix Makefiles" ..
    build_start_timems=$(($(date +%s) * 1000)) # 获取编译过程的启动时间
    # make -j4 2>&1 | tee $build_log             # 编译，并将编译结果保存在$build_log中，便于统计error和warning
    make -j4
    # export TERM=xterm-256color

    build_end_timems=$(($(date +%s) * 1000)) # 获取编译过程的结束时间
fi

# 4）计算编译消耗的时间，并显示打印出来
time_ms=$((build_end_timems - build_start_timems))
printf "\n [build info] --> Build finished.     Take time $(($time_ms / 1000)).$(($time_ms % 1000)) s.\n" # $time_ms ms.\n"

# 5）统计错误和警告，并显示数量
grep -E "(error|warning)" $build_log
error_count=$(grep -c "error" $build_log)
warning_count=$(grep -c "warning" $build_log)
echo " [build info] --> Build result is     errors: $error_count" "    warnings: $warning_count"

# 6）退出build目录
cd ..
