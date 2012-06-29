cmake_minimum_required(VERSION 2.6)
project(cf_openssl C)

find_package(cryptoface REQUIRED CONFIG PATHS ${CMAKE_MODULE_PATH})
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
	PREFIX "")

target_link_libraries(cf_openssl ${CRYPTOFACE_LIBRARIES})

target_link_libraries(cf_openssl ${OPENSSL_LIBCRYPTO})

include_directories(
    include
    ${CRYPTOFACE_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)
