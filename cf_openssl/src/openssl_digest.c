/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "digest_impl.h"

#include <openssl/evp.h>
#include <openssl/err.h>

struct _openssl_digest {
	struct cf_digest digest;
	EVP_MD_CTX ctx;
};

static cf_digest_t create_evp_container();

static cf_rv_t _digest_update(cf_digest_t digest, void *data, size_t data_len) {
	struct _openssl_digest *impl = (struct _openssl_digest*)digest;
	if(!EVP_DigestUpdate(&impl->ctx, data, data_len)) {
		ERR_clear_error();
		return CF_E_UNKNOWN;
	}
	return CF_S_OK;
}

static cf_rv_t _digest_finish(cf_digest_t digest, void *output, size_t *output_len) {
	struct _openssl_digest *impl = (struct _openssl_digest*)digest;
	size_t real_len = EVP_MD_CTX_size(&impl->ctx);
	unsigned int digest_output_len;
	if(!output && output_len) {
		*output_len = real_len;
		return CF_S_OK;
	}
	if(!output && !output_len) {
		EVP_MD_CTX_cleanup(&impl->ctx);
		free(impl);
		return CF_S_OK;
	}
	if(*output_len < real_len) {
		*output_len = real_len;
		return CF_E_INSUFFICIENT_BUFFER;
	}
	*output_len = real_len;
	digest_output_len = *output_len;
	if(!EVP_DigestFinal(&impl->ctx, output, &digest_output_len)) {
		EVP_MD_CTX_cleanup(&impl->ctx);
		ERR_clear_error();
		free(impl);
		return CF_E_UNKNOWN;
	}
	*output_len = digest_output_len;
	free(impl);
	return CF_S_OK;
}

static cf_rv_t _digest_clone(cf_digest_t *new_digest, cf_digest_t source) {
	struct _openssl_digest *source_impl = (struct _openssl_digest*)source;
	struct _openssl_digest *target_impl;
	*new_digest = create_evp_container();
	target_impl = (struct _openssl_digest*)*new_digest;
	if(!target_impl) {
		return CF_E_MEM;
	}
	EVP_MD_CTX_init(&target_impl->ctx);
	if(!EVP_MD_CTX_copy(&target_impl->ctx, &source_impl->ctx)) {
		free(target_impl);
		ERR_clear_error();
		*new_digest = NULL;
		return CF_E_MEM; // likely error...
	}
	return CF_S_OK;
}

static struct cf_digest_instance_ops openssl_digest_instance_ops = {
	_digest_update,
	_digest_finish,
	_digest_clone
};

static cf_digest_t create_evp_container() {
	struct _openssl_digest *impl = calloc(1, sizeof(*impl));
	if(!impl)
		return NULL;
	impl->digest.ops = &openssl_digest_instance_ops;
	return (cf_digest_t)impl;
}

static cf_rv_t _digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	const EVP_MD *md = (const EVP_MD*)id;
	struct _openssl_digest *impl;
	*digest = create_evp_container();
	impl = (struct _openssl_digest*)*digest;
	if(!impl) {
		return CF_E_MEM;
	}
	EVP_MD_CTX_init(&impl->ctx);
	if(!EVP_DigestInit_ex(&impl->ctx, md, NULL)) {
		free(impl);
		ERR_clear_error();
		*digest = NULL;
		return CF_E_UNKNOWN;
	}
	return CF_S_OK;
}

typedef const EVP_MD *(*EVP_MD_CTOR)(void);

static EVP_MD_CTOR hash_list[] = {
#ifndef OPENSSL_NO_MD2
	EVP_md2,
#endif
#ifndef OPENSSL_NO_MD4
	EVP_md4,
#endif
#ifndef OPENSSL_NO_MD5
	EVP_md5,
#endif
#ifndef OPENSSL_NO_SHA
	EVP_sha1,
/* EVAL INCLUDING DSS - tied to DSA.. SHA1 tied to RSA... */
#if 0
	EVP_dss1,
#endif
#ifdef OPENSSL_FIPS
#ifndef OPENSSL_NO_SHA256
	EVP_sha224,
	EVP_sha256,
#endif
#ifndef OPENSSL_NO_SHA512
	EVP_sha384,
	EVP_sha512,
#endif
#endif
#endif
#ifndef OPENSSL_NO_MDC2
	EVP_mdc2,
#endif
#ifndef OPENSSL_NO_RIPEMD
	EVP_ripemd160,
#endif
	NULL
};

/* collect information */
static cf_rv_t _digest_list_begin(cf_provider_t provider, void **iter) {
	*iter = (void*)hash_list;
	return CF_S_OK;
}
static cf_rv_t _digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info) {
	EVP_MD_CTOR **_iter = (EVP_MD_CTOR**)iter;
	const EVP_MD *md;
	if(!_iter || !*_iter || !**_iter)
		return CF_S_COMPLETE;
	md = (**_iter)();
	info->id = (cf_digest_id_t)md;
	info->name = EVP_MD_name(md);
	info->block_size = EVP_MD_size(md);
	*iter = (void*)(*_iter + 1);
	return CF_S_OK;
}
static cf_rv_t _digest_list_end(cf_provider_t provider, void **iter) {
	*iter = NULL;
	return CF_S_OK;
}

struct cf_digest_ops openssl_digest_ops = {
		_digest_init,
		_digest_list_begin,
		_digest_list_next,
		_digest_list_end
};
