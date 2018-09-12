cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(WindowsPlugin)

file(GLOB SOURCE_FILES "src/*.cc" "src/*.h")

include(node_modules/node-cmake/NodeJS.cmake)
nodejs_init()
add_nodejs_module(${PROJECT_NAME} ${SOURCE_FILES})

#link_libraries(lgdi32)
#target_link_libraries(${PROJECT_NAME} lgdi32)

#file(GLOB SOURCE_FILES "*.cc" "*.h" "./node_modules/nan/*.cc" "./node_modules/nan/*.h")

#add_library(${PROJECT_NAME} ${SOURCE_FILES} "./node_modules/nan/nan.h")
#
#include_directories(.)
#include_directories(node_modules\nan)
#include_directories({}})
#target_include_directories(${PROJECT_NAME} PUBLIC ./node_modules/nan/nan.h)
#target_include_directories(${PROJECT_NAME} PUBLIC ./node_modules/nan)
#target_include_directories(${PROJECT_NAME} PUBLIC "./node_modules/nan/nan.h")
#target_include_directories(${PROJECT_NAME} PUBLIC "./node_modules/nan")
#include_directories(./node_modules/nan/nan.h)
#include_directories(./node_modules/nan)
