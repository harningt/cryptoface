#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "mhash_digest.h"

static cf_rv_t _mhash_destroy_provider(cf_provider_t provider);

static struct cf_provider_ops mhash_provider_ops = {
	_mhash_destroy_provider
};

static cf_rv_t _mhash_init_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	*provider = calloc(1, sizeof(**provider));
	if(!*provider)
		return CF_E_MEM;
	(*provider)->provider_ops = mhash_provider_ops;
	(*provider)->digest_ops = mhash_digest_ops;
	return CF_S_OK;
}

static cf_rv_t _mhash_destroy_provider(cf_provider_t provider) {
	free(provider);
	return CF_S_OK;
}

cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	return _mhash_init_provider(provider, attrs, path);
}
