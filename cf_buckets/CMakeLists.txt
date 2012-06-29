cmake_minimum_required(VERSION 2.6)
project(cf_buckets C)

# Pulldown libarena
find_package(libarena REQUIRED CONFIG PATHS ${CMAKE_MODULE_PATH})
# Pulldown cryptoface for error definitions, at least until a common error
# system is in place
find_package(cryptoface REQUIRED CONFIG PATHS ${CMAKE_MODULE_PATH})

SET(SOURCES
    src/cf_bucket.c
    src/cf_bucket_manager.c
    src/cf_memory_bucket.c
)
SET(HEADERS
    include/cf_bucket_internal.h
    include/cf_bucket_manager_internal.h
)
SET(PUBLIC_HEADERS
    include/cf_bucket.h
    include/cf_bucket_manager.h
    include/cf_memory_bucket.h
)

add_library(cf_buckets STATIC ${SOURCES} ${HEADERS} ${PUBLIC_HEADERS})

target_link_libraries(cf_buckets ${LIBARENA_LIBRARIES})
target_link_libraries(cf_buckets ${CRYPTOFACE_LIBRARIES})

include_directories(
    include
    ${LIBARENA_INCLUDE_DIRS}
    ${CRYPTOFACE_INCLUDE_DIRS}
)
