cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(custom_transform)
set(LIB_NAME "_custom_parser")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external_libs/LightGBM)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_library(${LIB_NAME} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/examples/freeform2_parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/external_libs/LightGBM/include)

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/external_libs/LightGBM/include)

target_link_libraries(${LIB_NAME}
    -Wl,--no-as-needed
    -Wl,--start-group
    _lightgbm
    _transform
    -Wl,--end-group
)
