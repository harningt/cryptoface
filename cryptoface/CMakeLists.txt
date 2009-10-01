cmake_minimum_required(VERSION 2.6)
project(cryptoface_core C)

SET(SOURCES
	src/provider.c
	src/digest.c
)
SET(HEADERS
	include/cryptoface.h
	include/provider.h
	include/digest.h
	include/cryptoface_impl.h
)

add_library(cryptoface SHARED ${SOURCES} ${HEADERS})

IF(LINUX OR APPLE)
	target_link_libraries(cryptoface dl)
ENDIF(LINUX OR APPLE)

include_directories(include)
