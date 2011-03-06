#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "digest_impl.h"

#include <tomcrypt.h>

struct _tomcrypt_digest {
	struct cf_digest digest;
	const struct ltc_hash_descriptor *descriptor;
	hash_state state;
};

static struct _tomcrypt_digest *create_tomcrypt_digest_impl();

static cf_rv_t _digest_update(cf_digest_t digest, void *data, size_t data_len) {
	struct _tomcrypt_digest *impl = (struct _tomcrypt_digest*)digest;
	if (CRYPT_OK != impl->descriptor->process(&impl->state, data, data_len)) {
		return CF_E_UNKNOWN;
	}
	return CF_S_OK;
}

static cf_rv_t _digest_finish(cf_digest_t digest, void *output, size_t *output_len) {
	struct _tomcrypt_digest *impl = (struct _tomcrypt_digest*)digest;
	size_t real_len = impl->descriptor->hashsize;
	if(!output && output_len) {
		*output_len = real_len;
		return CF_S_OK;
	}
	if(!output && !output_len) {
		/* Internally cleanup since no output used */
		impl->descriptor = NULL;
		memset(&impl->state, 0, sizeof(impl->state));
		return CF_S_OK;
	}
	if(*output_len < real_len) {
		*output_len = real_len;
		return CF_E_INSUFFICIENT_BUFFER;
	}
	*output_len = real_len;
	if (CRYPT_OK != impl->descriptor->done(&impl->state, output)) {
		return CF_E_UNKNOWN;
	}
	/* Clean up state - done has already cleaned up state */
	impl->descriptor = NULL;
	return CF_S_OK;
}

static cf_rv_t _digest_clone(cf_digest_t *new_digest, cf_digest_t source) {
	/* WARNING: Not a standard defined item, however TomCrypt appears to use
	 * purely local values in hash state */
	struct _tomcrypt_digest *source_impl = (struct _tomcrypt_digest*)source;
	struct _tomcrypt_digest *impl = create_tomcrypt_digest_impl();
	if(!impl) {
		return CF_E_MEM;
	}
	impl->descriptor = source_impl->descriptor;

	/* Clone state */
	memcpy(&impl->state, &source_impl->state, sizeof(source_impl->state));
	return CF_S_OK;
}

static struct cf_digest_instance_ops tomcrypt_digest_instance_ops = {
	_digest_update,
	_digest_finish,
	_digest_clone
};

static cf_rv_t _digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	struct _tomcrypt_digest *impl;
	if (CRYPT_OK != hash_is_valid(id)) {
		return CF_E_UNKNOWN;
	}
	impl = create_tomcrypt_digest_impl();
	if (!impl) {
		return CF_E_MEM;
	}
	impl->descriptor = &hash_descriptor[id];

	if (CRYPT_OK != hash_descriptor[id].init(&impl->state)) {
		free(impl);
		return CF_E_UNKNOWN;
	}
	*digest = (cf_digest_t)impl;
	return CF_S_OK;
}

static struct _tomcrypt_digest *create_tomcrypt_digest_impl() {
	struct _tomcrypt_digest *impl = calloc(1, sizeof(*impl));
	if(!impl) {
		return NULL;
	}
	impl->digest.ops = &tomcrypt_digest_instance_ops;
	return impl;
}

/* collect information */
static cf_rv_t _digest_list_begin(cf_provider_t provider, void **iter) {
	*iter = (void*)0;
	return CF_S_OK;
}
static cf_rv_t _digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info) {
	int *id = (int*)iter;
	while(*id < TAB_SIZE) {
		const struct ltc_hash_descriptor *hash;
		if (CRYPT_OK != hash_is_valid(*id)) {
			++*id;
			continue;
		}
		hash = &hash_descriptor[*id];
		info->id = *id;
		info->name = hash->name;;
		info->block_size = hash->hashsize;
		++*id;
		return CF_S_OK;
	}
	return CF_S_COMPLETE;
}
static cf_rv_t _digest_list_end(cf_provider_t provider, void **iter) {
	*iter = NULL;
	return CF_S_OK;
}

struct cf_digest_ops tomcrypt_digest_ops = {
		_digest_init,
		_digest_list_begin,
		_digest_list_next,
		_digest_list_end
};

/* WARNING: Currently only handles one provider of tomcrypt open at once */
/* Initialization operations to register descriptors for lookup */
static const struct ltc_hash_descriptor *descriptors[] = {
#ifdef LTC_WHIRLPOOL
	&whirlpool_desc,
#endif
#ifdef LTC_SHA512
	&sha512_desc,
#endif
#ifdef LTC_SHA384
	&sha384_desc,
#endif
#ifdef LTC_SHA256
	&sha256_desc,
#endif
#ifdef LTC_SHA224
	&sha224_desc,
#endif
#ifdef LTC_SHA1
	&sha1_desc,
#endif
#ifdef LTC_MD5
	&md5_desc,
#endif
#ifdef LTC_MD4
	&md4_desc,
#endif
#ifdef LTC_MD2
	&md2_desc,
#endif
#ifdef LTC_TIGER
	&tiger_desc,
#endif
#ifdef LTC_RIPEMD128
	&rmd128_desc,
#endif
#ifdef LTC_RIPEMD160
	&rmd160_desc,
#endif
#ifdef LTC_RIPEMD256
	&rmd256_desc,
#endif
#ifdef LTC_RIPEMD320
	&rmd320_desc,
#endif
	NULL
};

cf_rv_t tomcrypt_digest_setup() {
	const struct ltc_hash_descriptor **ptr = descriptors;
	for (ptr; *ptr; *ptr++) {
		register_hash(*ptr);
	}
	return CF_S_OK;
}

cf_rv_t tomcrypt_digest_cleanup() {
	const struct ltc_hash_descriptor **ptr = descriptors;
	for (ptr; *ptr; *ptr++) {
		unregister_hash(*ptr);
	}
	return CF_S_OK;
}

