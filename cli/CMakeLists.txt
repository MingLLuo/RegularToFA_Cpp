cmake_minimum_required(VERSION 3.26)
project(lexical)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

add_executable(regToNfaTest tests/regToNfaTest.cpp)
target_include_directories(regToNfaTest PRIVATE src)

add_executable(regScanTest tests/regScanTest.cpp)
target_include_directories(regScanTest PRIVATE src)

add_executable(nfaToDfaTest tests/nfaToDfaTest.cpp)
target_include_directories(nfaToDfaTest PRIVATE src)

add_executable(testGenerate tests/testGenerate.cpp)
target_include_directories(testGenerate PRIVATE src)