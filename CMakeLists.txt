# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(FalconEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_definitions(SKSE_SUPPORT_XBYAK)

find_package(CommonLibSSE-NG REQUIRED)

add_library(FalconEngine MODULE
    src/Main.cpp
    src/ShipInteriorBubble.cpp
    src/MovementController.cpp
    src/Hooks.cpp
)

target_link_libraries(FalconEngine PRIVATE CommonLibSSE-NG::CommonLibSSE-NG)
