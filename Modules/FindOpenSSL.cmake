##
## Tries to find the required OpenSSL libraries. Once done this will define
## the variable OPENSSL_LIBRARIES.

message(STATUS "Looking for OpenSSL libraries")
if (MSVC)
  # /MD and /MDd are the standard values - if somone wants to use
  # others, the libnames have to change here too
  # use also ssl and ssleay32 in debug as fallback for openssl < 0.9.8b

  find_library(OPENSSL_LIBSSL_DEBUG
    NAMES ssleay32MDd ssl ssleay32
    PATHS ${OPENSSL_LIBRARY_DIR}
  )
  find_library(OPENSSL_LIBSSL_RELEASE
    NAMES ssleay32MD ssl ssleay32
    PATHS ${OPENSSL_LIBRARY_DIR}
  )
  find_library(OPENSSL_LIBCRYPTO_DEBUG
    NAMES libeay32MDd crypto libeay32
    PATHS ${OPENSSL_LIBRARY_DIR}
  )
  find_library(OPENSSL_LIBCRYPTO_RELEASE
    NAMES libeay32MD crypto libeay32
    PATHS ${OPENSSL_LIBRARY_DIR}
  )
   
  if (MSVC_IDE)
    if (NOT OPENSSL_LIBSSL_DEBUG OR NOT OPENSSL_LIBSSL_RELEASE)
      message(FATAL_ERROR
	      "Could not find the debug and release version of libssl.")
    endif(NOT OPENSSL_LIBSSL_DEBUG OR NOT OPENSSL_LIBSSL_RELEASE)
    if (NOT OPENSSL_LIBCRYPTO_DEBUG OR NOT OPENSSL_LIBCRYPTO_RELEASE)
      message(FATAL_ERROR
	      "Could not find the debug and release version of libcrypto.")
    endif(NOT OPENSSL_LIBCRYPTO_DEBUG OR NOT OPENSSL_LIBCRYPTO_RELEASE)

    set(OPENSSL_LIBSSL
      optimized ${OPENSSL_LIBSSL_RELEASE} 
      debug ${OPENSSL_LIBSSL_DEBUG})
    set(OPENSSL_LIBCRYPTO
      optimized ${OPENSSL_LIBCRYPTO_RELEASE}
      debug ${OPENSSL_LIBCRYPTO_DEBUG})
  else(MSVC_IDE)
    string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)
    if (CMAKE_BUILD_TYPE_TOLOWER MATCHES debug)
      set(OPENSSL_LIBSSL ${OPENSSL_LIBSSL_DEBUG})
      set(OPENSSL_LIBCRYPTO ${OPENSSL_LIBCRYPTO_DEBUG})
    else(CMAKE_BUILD_TYPE_TOLOWER MATCHES debug)
      set(OPENSSL_LIBSSL ${OPENSSL_LIBSSL_RELEASE})
      set(OPENSSL_LIBCRYPTO ${OPENSSL_LIBCRYPTO_RELEASE})
    endif(CMAKE_BUILD_TYPE_TOLOWER MATCHES debug)
  endif(MSVC_IDE)
  mark_as_advanced(OPENSSL_LIBSSL_DEBUG   OPENSSL_LIBCRYPTO_DEBUG
                   OPENSSL_LIBSSL_RELEASE OPENSSL_LIBCRYPTO_RELEASE)
else(MSVC)
  find_library(OPENSSL_LIBSSL NAMES ssl ssleay32)
  find_library(OPENSSL_LIBCRYPTO NAMES crypto libeay32)
endif(MSVC)


if (OPENSSL_LIBSSL AND OPENSSL_LIBCRYPTO)
  set(OPENSSL_LIBRARIES ${OPENSSL_LIBSSL} ${OPENSSL_LIBCRYPTO})
  mark_as_advanced(OPENSSL_LIBSSL OPENSSL_LIBCRYPTO)
  mark_as_advanced(OPENSSL_LIBRARIES)
  message(STATUS "Looking for OpenSSL libraries - found")
else (OPENSSL_LIBSSL AND OPENSSL_LIBCRYPTO)
  if (NOT OPENSSL_LIBSSL)
    message(FATAL_ERROR "Could not find libssl.")
  else (NOT OPENSSL_LIBSSL)
    message(FATAL_ERROR "Could not find libcrypto.")
  endif (NOT OPENSSL_LIBSSL)
endif(OPENSSL_LIBSSL AND OPENSSL_LIBCRYPTO)

