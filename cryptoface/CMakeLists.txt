cmake_minimum_required(VERSION 2.6)
project(cryptoface_core C)

set(CRYPTOFACE_VERSION 0.0.0)

include(WriteBasicConfigVersionFile)

SET(SOURCES
	src/provider.c
	src/digest.c
	src/module_loader.c
)
SET(PUBLIC_HEADERS
	include/cryptoface.h
	include/provider.h
	include/digest.h
	include/cryptoface_impl.h
	include/digest_impl.h
	include/module_loader.h
)
SET(HEADERS
    ${PUBLIC_HEADERS}
)

add_library(cryptoface SHARED ${SOURCES} ${HEADERS})

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR APPLE)
	target_link_libraries(cryptoface dl)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR APPLE)

include_directories(include)

file(COPY ${PUBLIC_HEADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

get_filename_component(CRYPTOFACE_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR} ABSOLUTE)
configure_file(cryptoface-config.cmake.in ${CF_MODULE_PATH}/cryptoface-config.cmake @ONLY)
export(TARGETS cryptoface APPEND FILE ${CF_MODULE_PATH}/cryptoface-config.cmake)
WRITE_BASIC_CONFIG_VERSION_FILE(
    ${CF_MODULE_PATH}/cryptoface-config-version.cmake
    VERSION ${CRYPTOFACE_VERSION}
    COMPATIBILITY SameMajorVersion)

