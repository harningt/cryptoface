/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef BEECRYPT_PROVIDER_H
#define BEECRYPT_PROVIDER_H

#include "provider.h"

#ifdef WIN32
#ifdef cf_beecrypt_EXPORTS
#define CF_BEECRYPT_API __declspec(dllexport)
#else
#define CF_BEECRYPT_API __declspec(dllimport)
#endif
#else
#define CF_BEECRYPT_API __attribute__((visibility("default"))) extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

cf_rv_t CF_BEECRYPT_API cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path);

#ifdef __cplusplus
}
#endif

#endif /* BEECRYPT_PROVIDER_H */
