/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "digest_impl.h"

#include <beecrypt/beecrypt.h>

struct _beecrypt_digest {
	struct cf_digest digest;
	hashFunction *hash;
	char param[1];
};

/* Minus 1 to account for space taken by param */
#define BEECRYPT_DIGEST_STRUCT_SIZE(paramSize) (sizeof(struct _beecrypt_digest) - 1 + (paramSize))

static cf_digest_t create_beecrypt_container(hashFunction *hash);

static cf_rv_t _digest_update(cf_digest_t digest, void *data, size_t data_len) {
	struct _beecrypt_digest *impl = (struct _beecrypt_digest*)digest;
	/* TODO: check return value */
	impl->hash->update((void*)impl->param, data, data_len);
	return CF_S_OK;
}

static cf_rv_t _digest_finish(cf_digest_t digest, void *output, size_t *output_len) {
	struct _beecrypt_digest *impl = (struct _beecrypt_digest*)digest;
	size_t real_len = impl->hash->digestsize;
	if(!output && output_len) {
		*output_len = real_len;
		return CF_S_OK;
	}
	if(!output && !output_len) {
		free(impl);
		return CF_S_OK;
	}
	if(*output_len < real_len) {
		*output_len = real_len;
		return CF_E_INSUFFICIENT_BUFFER;
	}
	*output_len = real_len;
	/* TODO: check return value */
	impl->hash->digest((void*)impl->param, output);
	free(impl);
	return CF_S_OK;
}

static cf_rv_t _digest_clone(cf_digest_t *new_digest, cf_digest_t source) {
	struct _beecrypt_digest *source_impl = (struct _beecrypt_digest*)source;
	hashFunction *hash = source_impl->hash;
	*new_digest = create_beecrypt_container(hash);
	if(!*new_digest) {
		return CF_E_MEM;
	}
	/* Copy the state - unknown safety */
	memcpy(((struct _beecrypt_digest *)new_digest)->param, source_impl->param, hash->paramsize);
	return CF_S_OK;
}

static struct cf_digest_instance_ops beecrypt_digest_instance_ops = {
	_digest_update,
	_digest_finish,
	_digest_clone
};

static cf_digest_t create_beecrypt_container(hashFunction *hash) {
	/* Allocate size for structure + additional param data at end - extra padding in */
	struct _beecrypt_digest *impl = calloc(1, BEECRYPT_DIGEST_STRUCT_SIZE(hash->paramsize));
	if(!impl) {
		return NULL;
	}
	impl->digest.ops = &beecrypt_digest_instance_ops;
	impl->hash = hash;
	/* TODO: check return value */
	hash->reset(impl->param);
	return (cf_digest_t)impl;
}

static cf_rv_t _digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	hashFunction *hash = (hashFunction*)id;
	*digest = create_beecrypt_container(hash);
	if(!*digest) {
		return CF_E_MEM;
	}
	return CF_S_OK;
}
/* collect information */
static cf_rv_t _digest_list_begin(cf_provider_t provider, void **iter) {
	*iter = (void*)0;
	return CF_S_OK;
}
static cf_rv_t _digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info) {
	int *id = (int*)iter;
	while(*id < hashFunctionCount()) {
		const hashFunction *hash = hashFunctionGet(*id);
		if(!hash) {
			++*id;
			continue;
		}
		info->id = (cf_digest_id_t)hash;
		info->name = hash->name;
		info->block_size = hash->digestsize;
		++*id;
		return CF_S_OK;
	}
	return CF_S_COMPLETE;
}
static cf_rv_t _digest_list_end(cf_provider_t provider, void **iter) {
	*iter = NULL;
	return CF_S_OK;
}

struct cf_digest_ops beecrypt_digest_ops = {
	_digest_init,
	_digest_list_begin,
	_digest_list_next,
	_digest_list_end
};
