/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cryptopp_provider.h"

#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "cryptopp_digest.h"


static cf_rv_t _cryptopp_destroy_provider(cf_provider_t provider);

static struct cf_provider_ops cryptopp_provider_ops = {
	_cryptopp_destroy_provider
};

static cf_rv_t _cryptopp_init_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	*provider = (cf_provider_t)calloc(1, sizeof(**provider));
	if(!*provider) {
		return CF_E_MEM;
	}
	(*provider)->provider_ops = cryptopp_provider_ops;
	(*provider)->digest_ops = cryptopp_digest_ops;
	return CF_S_OK;
}
static cf_rv_t _cryptopp_destroy_provider(cf_provider_t provider) {
	cleanup_cryptopp_digest();
	free(provider);
	return CF_S_OK;
}

cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	return _cryptopp_init_provider(provider, attrs, path);
}
