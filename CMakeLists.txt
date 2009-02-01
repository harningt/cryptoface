cmake_minimum_required(VERSION 2.6)
project(cryptoface C)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

ADD_SUBDIRECTORY(cryptoface)
ADD_SUBDIRECTORY(cf_mhash)
ADD_SUBDIRECTORY(cf_openssl)
ADD_SUBDIRECTORY(luacf)

ADD_SUBDIRECTORY(cf_test)
