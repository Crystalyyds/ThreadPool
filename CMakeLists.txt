cmake_minimum_required(VERSION 3.10)
project(Atmpool VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件
set(SOURCES
    main.cpp
    ATM.cpp
    Account.cpp
    BankSystem.cpp
    ThreadPool.cpp
)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR})

# 生成可执行文件
add_executable(Atmpool ${SOURCES})
