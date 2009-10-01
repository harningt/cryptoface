#ifndef OPENSSL_PROVIDER_H
#define OPENSSL_PROVIDER_H

#include "provider.h"

#ifdef WIN32
#ifdef cf_openssl_EXPORTS
#define CF_OPENSSL_API __declspec(dllexport)
#else
#define CF_OPENSSL_API __declspec(dllimport)
#endif
#else
#define CF_OPENSSL_API __attribute__((visibility, "default"))
#endif

CF_OPENSSL_API cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path);

#endif /* OPENSSL_PROVIDER_H */
