cmake_minimum_required(VERSION 2.6)
project(cf_nettle C)

find_package(cryptoface REQUIRED CONFIG PATHS ${CMAKE_MODULE_PATH})
find_package(Nettle REQUIRED)

SET(SOURCES
	src/nettle_provider.c
	src/nettle_digest.c
	src/digest_list.h
)
SET(HEADERS
	include/nettle_digest.h
	include/nettle_provider.h
)

add_library(cf_nettle MODULE ${SOURCES} ${HEADERS})

set_target_properties(cf_nettle
	PROPERTIES
	PREFIX "")

target_link_libraries(cf_nettle ${CRYPTOFACE_LIBRARIES})

target_link_libraries(cf_nettle ${NETTLE_LIBRARIES})

include_directories(
    include
    ${CRYPTOFACE_INCLUDE_DIRS}
    ${NETTLE_INCLUDE_DIR}
)
