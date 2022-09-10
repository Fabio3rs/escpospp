cmake_minimum_required (VERSION 3.0)
project (EscPospp)

set(testing_mode "false")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCES
    "escpospp/*.hpp"
    "escpospp/*.h"
    "src/*.cpp"
)

include_directories(./)

if(testing_mode STREQUAL "true")
    LIST(REMOVE_ITEM SOURCES
        src/main.cpp)
    add_executable(EscPospp ${SOURCES})
else()
    add_library(EscPospp ${SOURCES})
endif()
target_compile_options(EscPospp PUBLIC -Weverything -Wpedantic -Wno-unused-member-function -std=c++17 -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)

target_link_libraries(EscPospp usb-1.0)

add_executable(main tests/main.cpp)
target_link_libraries(main EscPospp)
