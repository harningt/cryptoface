/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "nettle_provider.h"

#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "nettle_digest.h"


static cf_rv_t _nettle_destroy_provider(cf_provider_t provider);

static struct cf_provider_ops nettle_provider_ops = {
	_nettle_destroy_provider
};

static cf_rv_t _nettle_init_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	*provider = (cf_provider_t)calloc(1, sizeof(**provider));
	if(!*provider) {
		return CF_E_MEM;
	}
	(*provider)->provider_ops = nettle_provider_ops;
	(*provider)->digest_ops = nettle_digest_ops;
	return CF_S_OK;
}
static cf_rv_t _nettle_destroy_provider(cf_provider_t provider) {
	free(provider);
	return CF_S_OK;
}

cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	return _nettle_init_provider(provider, attrs, path);
}
