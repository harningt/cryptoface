#include "gcrypt_provider.h"

#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "gcrypt_digest.h"

#include <gcrypt.h>

static cf_rv_t _gcrypt_destroy_provider(cf_provider_t provider);

static struct cf_provider_ops gcrypt_provider_ops = {
	_gcrypt_destroy_provider
};

static cf_rv_t _gcrypt_init_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	*provider = calloc(1, sizeof(**provider));
	if(!*provider) {
		return CF_E_MEM;
	}

	/* Version check should be the very first call because it
	 * makes sure that important subsystems are intialized. */
	if (!gcry_check_version(GCRYPT_VERSION)) {
		free(*provider);
		*provider = NULL;
		return CF_E_UNKNOWN;
	}
	/* Disable secure memory.  */
	gcry_control (GCRYCTL_DISABLE_SECMEM, 0);

	/* ... If required, other initialization goes here.  */
	/* Tell Libgcrypt that initialization has completed. */
	gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);

	(*provider)->provider_ops = gcrypt_provider_ops;
	(*provider)->digest_ops = gcrypt_digest_ops;
	return CF_S_OK;
}

static cf_rv_t _gcrypt_destroy_provider(cf_provider_t provider) {
	free(provider);
	return CF_S_OK;
}

cf_rv_t cf_init_loaded_provider(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	return _gcrypt_init_provider(provider, attrs, path);
}
