##
## Tries to find the required OpenSSL libraries. Once done this will define
## the variable OPENSSL_LIBRARIES.

message(STATUS "Looking for OpenSSL libraries")
if (MSVC)
  # /MD and /MDd are the standard values - if somone wants to use
  # others, the libnames have to change here too
  # use also ssl and ssleay32 in debug as fallback for openssl < 0.9.8b
  set(OPENSSL_LIBRARY_DIR ${OPENSSL_LIBRARY_DIR} CACHE PATH "OpenSSL container")
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
  find_path(OPENSSL_INCLUDE_DIR openssl/opensslv.h ${OPENSSL_LIBRARY_DIR})

  if (MSVC_IDE)
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
                   OPENSSL_LIBSSL_RELEASE OPENSSL_LIBCRYPTO_RELEASE
                   OPENSSL_INCLUDE_DIR)
else(MSVC)
  find_library(OPENSSL_LIBSSL NAMES ssl ssleay32)
  find_library(OPENSSL_LIBCRYPTO NAMES crypto libeay32)
  find_path(OPENSSL_INCLUDE_DIR openssl/opensslv.h)
  mark_as_advanced(OPENSSL_INCLUDE_DIR)
endif(MSVC)


if (OPENSSL_LIBSSL AND OPENSSL_LIBCRYPTO)
  set(OPENSSL_LIBRARIES ${OPENSSL_LIBSSL} ${OPENSSL_LIBCRYPTO})
  mark_as_advanced(OPENSSL_LIBSSL OPENSSL_LIBCRYPTO)
  mark_as_advanced(OPENSSL_LIBRARIES)
  message(STATUS "Looking for OpenSSL libraries - found")
endif(OPENSSL_LIBSSL AND OPENSSL_LIBCRYPTO)
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenSSL DEFAULT_MSG OPENSSL_INCLUDE_DIR OPENSSL_LIBSSL OPENSSL_LIBCRYPTO)

