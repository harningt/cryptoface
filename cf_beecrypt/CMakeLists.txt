cmake_minimum_required(VERSION 2.6)
project(cf_beecrypt C)

find_package(BeeCrypt REQUIRED)

SET(SOURCES
	src/beecrypt_provider.c
	src/beecrypt_digest.c
)
SET(HEADERS
	include/beecrypt_digest.h
	include/beecrypt_provider.h
)

add_library(cf_beecrypt MODULE ${SOURCES} ${HEADERS})

set_target_properties(cf_beecrypt
	PROPERTIES
	PREFIX ""
	COMPILE_FLAGS "${BEECRYPT_C_FLAGS}"
	LINK_FLAGS "${BEECRYPT_LINK_FLAGS}")

target_link_libraries(cf_beecrypt cryptoface)

target_link_libraries(cf_beecrypt ${BEECRYPT_LIBRARIES})

include_directories(include ../cryptoface/include ${BEECRYPT_INCLUDE_DIR})
