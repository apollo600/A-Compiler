#!/bin/bash

# 此脚本用于安装 flex 工具

# 设置遇到错误就停止执行后续指令
set -e

# 检查是否已经安装过 flex
flex --version
if [ $? ]; then
    echo "Warning: flex already exists, script ends"
    # exit
fi

# 获取 flex 发布版本
wget https://github.com/westes/flex/files/981163/flex-2.6.4.tar.gz -O flex.tar.gz -e use_proxy=yes -e http_proxy=127.0.0.1:7890

# 解压缩
tar -xvf flex.tar.gz 

# 创建 tools 文件夹
mkdir tools

# 进入目录并进行 UNIX 常规安装步骤
mv flex-* tools/flex
cd tools/flex
./configure
make -j8
sudo make install

# 添加链接库目录
echo "export LD_LIBRARY_PATH=/usr/local/lib" >> ~/.bashrc
source ~/.bashrc

# 检查是否安装成功
flex --version
if [ $? ]; then
    echo "Install flex Successfuly"
else
    echo "Install flex Failed"
fi
