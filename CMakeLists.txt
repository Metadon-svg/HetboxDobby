cmake_minimum_required(VERSION 3.10)
project(hitbox_module)

set(CMAKE_CXX_STANDARD 17)

if(ANDROID)
   set(CMAKE_SYSTEM_NAME Android)
   set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(hitbox_module SHARED ${SOURCES})

target_include_directories(hitbox_module PRIVATE include)

set(DOBBY_LIB "${CMAKE_CURRENT_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a")
target_link_libraries(hitbox_module PRIVATE ${DOBBY_LIB} log dl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fvisibility=hidden")
