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
#define CF_MHASH_API __attribute__((visibility, "default"))
#endif

CF_MHASH_API cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs attrs, const char *path);

#endif /* MHASH_PROVIDER_H */
