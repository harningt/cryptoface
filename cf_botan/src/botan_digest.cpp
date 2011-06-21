/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "digest_impl.h"

#include <botan/botan.h>
using namespace Botan;

struct _botan_digest {
	struct cf_digest digest;
	HashFunction *hash;
};

static cf_digest_t create_hash_container();

static cf_rv_t _digest_update(cf_digest_t digest, void *data, size_t data_len) {
	struct _botan_digest *impl = (struct _botan_digest*)digest;
	try {
		impl->hash->update((byte*)data, data_len);
	} catch (std::exception &e) {
		(void)e;
		return CF_E_UNKNOWN;
	}	
	return CF_S_OK;
}

static cf_rv_t _digest_finish(cf_digest_t digest, void *output, size_t *output_len) {
	struct _botan_digest *impl = (struct _botan_digest*)digest;
	size_t real_len = impl->hash->output_length();
	unsigned int digest_output_len;
	if(!output && output_len) {
		*output_len = real_len;
		return CF_S_OK;
	}
	if(!output && !output_len) {
		delete impl->hash;
		impl->hash = NULL;
		free(impl);
		return CF_S_OK;
	}
	if(*output_len < real_len) {
		*output_len = real_len;
		return CF_E_INSUFFICIENT_BUFFER;
	}
	*output_len = real_len;
	try {
		impl->hash->final((byte*)output);
	} catch (std::exception &e) {
		(void)e;
		return CF_E_UNKNOWN;
	}
	delete impl->hash;
	impl->hash = NULL;
	free(impl);
	return CF_S_OK;
}

static cf_rv_t _digest_clone(cf_digest_t *new_digest, cf_digest_t source) {
	/* No known way of copying digest */
	return CF_E_NOT_IMPLEMENTED;
}

static struct cf_digest_instance_ops botan_digest_instance_ops = {
	_digest_update,
	_digest_finish,
	_digest_clone
};

static cf_digest_t create_hash_container() {
	struct _botan_digest *impl = (struct _botan_digest*)calloc(1, sizeof(*impl));
	if(!impl) {
		return NULL;
	}
	impl->digest.ops = &botan_digest_instance_ops;
	return (cf_digest_t)impl;
}

static cf_rv_t _digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	const char *md = (const char *)id;
	const HashFunction *hash = retrieve_hash(md);
	if (!hash) {
		return CF_E_UNKNOWN;
	}
	struct _botan_digest *impl;
	*digest = create_hash_container();
	impl = (struct _botan_digest*)*digest;
	if(!impl) {
		return CF_E_MEM;
	}
	try {
		impl->hash = hash->clone();
	} catch (std::exception &e) {
		(void)e;
		free(impl);
		return CF_E_MEM;
	}
	return CF_S_OK;
}

static const char * hash_list[] = {
	"Adler32",
	"BMW-512",
	"CRC24",
	"CRC32",
	"GOST-34.11",
	"HAS-160",
	"Keccak-1600(224)",
	"Keccak-1600(256)",
	"Keccak-1600(384)",
	"Keccak-1600(512)",
	"MD2",
	"MD4",
	"MD5",
	"RIPEMD-128",
	"RIPEMD-160",
	"SHA-160",
	"SHA-224",
	"SHA-256",
	"SHA-384",
	"SHA-512",
	"Tiger(16)",
	"Tiger(20)",
	"Tiger(24)",
	"Skein-512",
	"Skein-512(1024)", /* Not sure if valid */
	"Whirlpool",
	NULL
};

/* collect information */
static cf_rv_t _digest_list_begin(cf_provider_t provider, void **iter) {
	*iter = (void*)hash_list;
	return CF_S_OK;
}
static cf_rv_t _digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info) {
	const char **md_iter = (const char **)*iter;
	const char *md;
	const HashFunction *hash;
	if(!md_iter || !*md_iter) {
		return CF_S_COMPLETE;
	}
	md = *md_iter;
	hash = retrieve_hash(md);
	while (!hash) {
		md_iter++;
		if (!*md_iter) {
			return CF_S_COMPLETE;
		}
		md = *md_iter;
		hash = retrieve_hash(md);
	}
	info->id = (cf_digest_id_t)md;
	info->name = md;
	info->block_size = hash->output_length();
	*iter = (void*)(md_iter + 1);
	return CF_S_OK;
}
static cf_rv_t _digest_list_end(cf_provider_t provider, void **iter) {
	*iter = NULL;
	return CF_S_OK;
}

struct cf_digest_ops botan_digest_ops = {
		_digest_init,
		_digest_list_begin,
		_digest_list_next,
		_digest_list_end
};
