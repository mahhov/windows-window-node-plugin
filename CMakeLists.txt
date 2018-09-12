cmake_minimum_required(VERSION 3.12)
project(nanTest)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(nanTest
        .gitignore
        a.exe
        binding.gyp
        doesitwork.js
        index.js
        package.json
        Window.cc
        Window.h
        WindowNan.cc)

target_link_libraries(nanTest lgdi32 nan)

include_directories(${CMAKE_JS_INC} node_modules/nan)
