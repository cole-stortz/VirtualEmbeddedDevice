cmake_minimum_required(VERSION 3.10)
project(VirtualDevice)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(device
    src/main.cpp
    src/device.cpp
    src/tcp_client.cpp
    src/protocol.cpp
    src/program.cpp
    src/components/component.cpp
    src/components/led.cpp
    src/components/sensor.cpp
)

target_link_libraries(device ws2_32)