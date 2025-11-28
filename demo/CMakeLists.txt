cmake_minimum_required(VERSION 3.27)
project(xbc_demo)

set(PORTAUDIO_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/portaudio/portaudio")
set(PORTAUDIO_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/portaudio")
include_directories(${PORTAUDIO_INCLUDE_DIR})
link_directories(${PORTAUDIO_LIB_DIR})

set(RTC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/rtc/rtc")
set(RTC_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/rtc")
include_directories(${RTC_INCLUDE_DIR})
link_directories(${RTC_LIB_DIR})

set(LIBRSX_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/rsx")
set(LIBRSX_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/rsx")
include_directories(${LIBRSX_INCLUDE_DIR})
link_directories(${LIBRSX_LIB_DIR})

add_executable(demo
        src/main.c
)

find_path(MHD_INCLUDE_DIR microhttpd.h)
find_library(MHD_LIBRARY microhttpd)

include_directories(
        ${CMAKE_SOURCE_DIR}/lib/rtc/rtc
        ${CMAKE_SOURCE_DIR}/lib/portaudio/portaudio
)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(DEST_DIR "${CMAKE_BINARY_DIR}/cnf")

add_custom_command(
        OUTPUT ${DEST_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${DEST_DIR}
)

add_custom_command(
        OUTPUT ${DEST_DIR}/routes.json ${DEST_DIR}/config.xbc
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOURCE_DIR}/config.xbc ${DEST_DIR}/config.xbc
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOURCE_DIR}/routes.json ${DEST_DIR}/routes.json
        DEPENDS ${SOURCE_DIR}/config.xbc ${SOURCE_DIR}/routes.json
        COMMENT "prepare files to build directory"
)

add_custom_target(
        PREPARE_COMPILE ALL
        DEPENDS ${DEST_DIR}/routes.json ${DEST_DIR}/config.xbc
)

target_link_libraries(demo PRIVATE xbc
        microhttpd
        ${CMAKE_SOURCE_DIR}/lib/rtc/libdatachannel.a
        ${CMAKE_SOURCE_DIR}/lib/rtc/libjuice.a
        ${CMAKE_SOURCE_DIR}/lib/rtc/libsrtp2.a
        ${CMAKE_SOURCE_DIR}/lib/rtc/libusrsctp.a
        ${CMAKE_SOURCE_DIR}/lib/portaudio/libportaudio.a
        pthread dl
        pulse-simple
        pulse
        asound
        jack
        m z png stdc++)

add_dependencies(demo PREPARE_COMPILE)
