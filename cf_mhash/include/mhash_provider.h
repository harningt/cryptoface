/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef MHASH_PROVIDER_H
#define MHASH_PROVIDER_H

#include "provider.h"

#ifdef WIN32
#ifdef cf_mhash_EXPORTS
#define CF_MHASH_API __declspec(dllexport)
#else
#define CF_MHASH_API __declspec(dllimport)
#endif
#else
#define CF_MHASH_API __attribute__((visibility("default"))) extern
#endif

cf_rv_t CF_MHASH_API cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path);

#endif /* MHASH_PROVIDER_H */
