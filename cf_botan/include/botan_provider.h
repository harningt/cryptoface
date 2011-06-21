/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef BOTAN_PROVIDER_H
#define BOTAN_PROVIDER_H

#include "provider.h"

#ifdef WIN32
#ifdef cf_botan_EXPORTS
#define CF_BOTAN_API __declspec(dllexport)
#else
#define CF_BOTAN_API __declspec(dllimport)
#endif
#else
#define CF_BOTAN_API __attribute__((visibility("default"))) extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

cf_rv_t CF_BOTAN_API cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path);

#ifdef __cplusplus
}
#endif

#endif /* BOTAN_PROVIDER_H */
