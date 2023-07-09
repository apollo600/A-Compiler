#!/bin/bash

# 此脚本用于安装 bison 工具

# 设置遇到错误就停止执行后续指令
set -e

# 检查是否已经安装过 flex
bison --version
if [ $? ]; then
    echo "Warning: bison already exists, script ends"
    # exit
fi

# 进入根目录
cd ..

# 获取 flex 发布版本
wget http://ftp.gnu.org/gnu/bison/bison-3.8.tar.gz -O bison.tar.gz -e use_proxy=yes -e http_proxy=127.0.0.1:7890

# 解压缩
tar -xvf bison.tar.gz 

# 创建 tools 文件夹
mkdir tools

# 进入目录并进行 UNIX 常规安装步骤
mv bison-* tools/bison
cd tools/bison
./configure
make -j8
sudo make install

# 检查是否安装成功
bison --version
if [ $? ]; then
    echo "Install bison Successfuly"
else
    echo "Install bison Failed"
fi
