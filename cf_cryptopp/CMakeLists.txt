cmake_minimum_required(VERSION 2.6)
project(cf_cryptopp CXX)

find_package(Crypto++ REQUIRED)

SET(SOURCES
	src/cryptopp_provider.cpp
	src/cryptopp_digest.cpp
	src/digest_list.h
)
SET(HEADERS
	include/cryptopp_digest.h
	include/cryptopp_provider.h
)

add_library(cf_cryptopp MODULE ${SOURCES} ${HEADERS})

set_target_properties(cf_cryptopp
	PROPERTIES
	PREFIX "")

target_link_libraries(cf_cryptopp cryptoface)

target_link_libraries(cf_cryptopp ${CRYPTO++_LIBRARIES})

include_directories(include ../cryptoface/include ${CRYPTO++_INCLUDE_DIR})
