cmake_minimum_required(VERSION 3.10.2)
# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

if(CMAKE_VERSION VERSION_LESS "3.11.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Wigdets REQUIRED)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

#add_subdirectory(blink)
#add_subdirectory(uart_exp)

add_executable(read_port
               read_port.c
)

target_link_libraries(read_port Qt5::Widgets)