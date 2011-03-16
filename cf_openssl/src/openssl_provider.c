/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "openssl_provider.h"

#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "openssl_digest.h"

#include <openssl/evp.h>
#include <openssl/err.h>

static cf_rv_t _openssl_destroy_provider(cf_provider_t provider);

static struct cf_provider_ops openssl_provider_ops = {
	_openssl_destroy_provider
};

static cf_rv_t _openssl_init_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	/* PREPARE OPENSSL */
	ERR_load_crypto_strings();
	*provider = calloc(1, sizeof(**provider));
	if(!*provider)
		return CF_E_MEM;
	(*provider)->provider_ops = openssl_provider_ops;
	(*provider)->digest_ops = openssl_digest_ops;
	return CF_S_OK;
}

static cf_rv_t _openssl_destroy_provider(cf_provider_t provider) {
	free(provider);
	ERR_free_strings();
	EVP_cleanup();
	CRYPTO_cleanup_all_ex_data ();
	return CF_S_OK;
}

cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	return _openssl_init_provider(provider, attrs, path);
}
