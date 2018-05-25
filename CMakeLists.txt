##
## The CMakeLists of
##
## Copyright (C) 2018 Johann Lee <me@qinka.pro>
## GPLv3
##

## require for CMake 3.3
cmake_minimum_required(VERSION 3.3)

## Setting up build system
set (CMAKE_SYSTEM_NAME      Generic)
set (CMAKE_SYSTEM_PROCESSOR arm)
set (CMAKE_CROSSCOMPILING   TRUE)

# Project Kyo Test Bench
project(kyo-tb)

# Settings
# Cache
set (ARM_PREFIX "arm-none-" CACHE string "cc" )
# compiler
set (CMAKE_C_COMPILER "${ARM_PREFIX}gcc")
set (CMAKE_CXX_COMPILER "${ARM_PREFIX}g++")

## for platform
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  if (NOT (DEFINED "EXE_IGNORE"))
    set (EXE_POSTFIX ".exe") 
  endif (NOT (DEFINED "EXE_IGNORE"))
endif (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")

add_executable (kyo-tb1 src/kyo-tb1.c)
