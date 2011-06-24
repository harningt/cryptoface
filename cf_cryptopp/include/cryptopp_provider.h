/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef CRYPTOPP_PROVIDER_H
#define CRYPTOPP_PROVIDER_H

#include "provider.h"

#ifdef WIN32
#ifdef cf_cryptopp_EXPORTS
#define CF_CRYPTOPP_API __declspec(dllexport)
#else
#define CF_CRYPTOPP_API __declspec(dllimport)
#endif
#else
#define CF_CRYPTOPP_API __attribute__((visibility("default"))) extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

cf_rv_t CF_CRYPTOPP_API cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTOPP_PROVIDER_H */
