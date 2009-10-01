cmake_minimum_required(VERSION 2.6)
project(cryptoface_core C)

SET(SOURCES
	src/provider.c
	src/digest.c
	src/module_loader.c
)
SET(HEADERS
	include/cryptoface.h
	include/provider.h
	include/digest.h
	include/cryptoface_impl.h
	include/module_loader.h
)

add_library(cryptoface SHARED ${SOURCES} ${HEADERS})

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR APPLE)
	target_link_libraries(cryptoface dl)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR APPLE)

include_directories(include)
