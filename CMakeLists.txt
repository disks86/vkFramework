cmake_minimum_required(VERSION 3.15)
project(vkFramework)

set(CMAKE_CXX_STANDARD 20)

set(Vulkan_LIBRARIES "$ENV{VULKAN_SDK}/lib/vulkan-1.lib")
set(Vulkan_INCLUDE_DIRS "$ENV{VULKAN_SDK}/Include/")
message(STATUS "Using module to find Vulkan")
find_package(Vulkan REQUIRED)

add_compile_definitions(MAKEDLL)

add_library(vkFramework SHARED Application.cpp Application.h Helpers.h Helpers.cpp LogManager.cpp LogManager.h)