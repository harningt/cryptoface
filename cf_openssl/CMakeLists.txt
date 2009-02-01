cmake_minimum_required(VERSION 2.6)
project(cf_openssl)

find_package(OpenSSL REQUIRED)

SET(SOURCES
	src/openssl_provider.c
	src/openssl_digest.c
)
SET(HEADERS
	include/openssl_digest.h
)

add_library(cf_openssl MODULE ${SOURCES} ${HEADERS})

set_target_properties(cf_openssl
	PROPERTIES
	PREFIX ""
	LIBRARY_OUTPUT_DIRECTORY ../bin)

target_link_libraries(cf_openssl cryptoface)

target_link_libraries(cf_openssl ${OPENSSL_LIBCRYPTO})

include_directories(include ../cryptoface/include ${OPENSSL_INCLUDE_DIR})
