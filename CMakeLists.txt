cmake_minimum_required(VERSION 4.0)

set(DIALUP_DIR "$ENV{LOCALAPPDATA}/DialUp")
include("${DIALUP_DIR}/build-tools/PreProject.cmake")

project(DialUp-SDK VERSION 1.0 LANGUAGES CXX)

set(SOURCES
    generated/impl/Runtime.cpp
    generated/impl/Schema.cpp

    generated/impl/AkAudio_classes.cpp
    generated/impl/Core_classes.cpp
    generated/impl/Engine_classes.cpp
    generated/impl/GFxUI_classes.cpp
    generated/impl/IpDrv_classes.cpp
    generated/impl/OnlineSubsystemEOS_classes.cpp
    generated/impl/ProjectX_classes.cpp
    generated/impl/TAGame_classes.cpp
    generated/impl/WinDrv_classes.cpp
)

set(INCLUDES generated/include)

include("${DIALUP_DIR}/build-tools/SDK.cmake")

dialup_setup_sdk(${PROJECT_NAME}
    SOURCES ${SOURCES}
    INCLUDES ${INCLUDES}
    DESTINATION sdk-plugin
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SDK_BUILD)
