cmake_minimum_required(VERSION 4.0)

set(DIALUP_DIR "$ENV{LOCALAPPDATA}/DialUp")
include("${DIALUP_DIR}/build-tools/PreProject.cmake")
include("${DIALUP_DIR}/build-tools/GameBinaryDir.cmake")

project(AllTests)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${DIALUP_DIR}/sdk-plugin/include
    ${DIALUP_DIR}/include/v1
    ${DIALUP_DIR}/include/external/doctest/include
    ${DIALUP_DIR}/include/external/fmt/include
)

set(SOURCES
    main.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set(CMAKE_PREFIX_PATH "${DIALUP_DIR}/sdk-plugin")
find_package(DialUp-SDK REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE DialUp-SDK::DialUp-SDK)

target_compile_definitions(AllTests PRIVATE TEST_BUILD)

target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)

include("${DIALUP_DIR}/build-tools/PostProject.cmake")
