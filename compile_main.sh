#!/bin/bash

# Set the paths to the NDK and toolchain
NDK_PATH=~/android-ndk-r21b-linux-x86_64/android-ndk-r21b # Replace with the correct path
TOOLCHAIN_PATH=$NDK_PATH/toolchains/llvm/prebuilt/linux-x86_64/bin
export PATH=$TOOLCHAIN_PATH:$PATH

# Set the correct toolchain prefix for the desired architecture (aarch64-linux-android)
TOOLCHAIN_PREFIX=aarch64-linux-android29

# Specify the cross-compiler
CC=$TOOLCHAIN_PREFIX-clang

# Specify the sysroot and include paths
SYSROOT="--sysroot=$NDK_PATH/toolchains/llvm/prebuilt/linux-x86_64/sysroot"
INCLUDE_PATH="-isystem=$NDK_PATH/sysroot/usr/include"

# Compile the C file and generate an executable
$CC -o main main.c $SYSROOT $INCLUDE_PATH -static

# Print a message indicating successful compilation
echo "Compilation completed. Executable: main"
file main

