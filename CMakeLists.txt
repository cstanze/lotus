cmake_minimum_required(VERSION 3.0)

project(Lotus)

execute_process(COMMAND date "+%a %b %d, %Y at %H:%M:%S" OUTPUT_VARIABLE BUILD_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)

set(ORIGIN "$ORIGIN")
if(APPLE)
	set(ORIGIN "@loader_path")
endif()
set(CMAKE_INSTALL_RPATH "${ORIGIN}/../lib/feral;${ORIGIN}/.")
set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_MACOSX_RPATH TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file("${PROJECT_SOURCE_DIR}/include/lotus/config.h.in" "${PROJECT_SOURCE_DIR}/include/lotus/config.h" @ONLY)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

include(AddLotus)

add_subdirectory(src)
