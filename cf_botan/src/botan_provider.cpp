/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "botan_provider.h"

#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "botan_digest.h"


#include <botan/botan.h>
using namespace Botan;

static cf_rv_t _botan_destroy_provider(cf_provider_t provider);

static struct cf_provider_ops botan_provider_ops = {
	_botan_destroy_provider
};

static cf_rv_t _botan_init_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	*provider = (cf_provider_t)calloc(1, sizeof(**provider));
	if(!*provider) {
		return CF_E_MEM;
	}
	(*provider)->provider_ops = botan_provider_ops;
	(*provider)->digest_ops = botan_digest_ops;
	/* PREPARE Botan */
	try {
		LibraryInitializer::initialize();
	} catch (std::exception &e) {
		(void)e;
		free(*provider);
		*provider = NULL;
		return CF_E_UNKNOWN;
	}

	return CF_S_OK;
}
static cf_rv_t _botan_destroy_provider(cf_provider_t provider) {
	LibraryInitializer::deinitialize();
	free(provider);
	return CF_S_OK;
}

cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	return _botan_init_provider(provider, attrs, path);
}
