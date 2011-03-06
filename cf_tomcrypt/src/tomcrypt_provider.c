#include "tomcrypt_provider.h"

#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "tomcrypt_digest.h"

static cf_rv_t _tomcrypt_destroy_provider(cf_provider_t provider);

static struct cf_provider_ops tomcrypt_provider_ops = {
	_tomcrypt_destroy_provider
};

static cf_rv_t _tomcrypt_init_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	cf_rv_t ret;
	*provider = calloc(1, sizeof(**provider));
	if(!*provider) {
		return CF_E_MEM;
	}
	(*provider)->provider_ops = tomcrypt_provider_ops;
	(*provider)->digest_ops = tomcrypt_digest_ops;
	ret = tomcrypt_digest_setup();
	if (CF_S_OK != ret) {
		free(provider);
		return ret;
	}
	return CF_S_OK;
}

static cf_rv_t _tomcrypt_destroy_provider(cf_provider_t provider) {
	(void)tomcrypt_digest_cleanup();
	free(provider);
	return CF_S_OK;
}

cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	return _tomcrypt_init_provider(provider, attrs, path);
}
