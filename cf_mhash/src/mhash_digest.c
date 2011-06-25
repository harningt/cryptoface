/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "digest_impl.h"

#include <mhash.h>

struct _mhash_digest {
	struct cf_digest digest;
	MHASH mhash;
};

static cf_digest_t create_mhash_container(MHASH hash);

static cf_rv_t _digest_update(cf_digest_t digest, void *data, size_t data_len) {
	struct _mhash_digest *impl = (struct _mhash_digest*)digest;
	mhash(impl->mhash, data, data_len);
	return CF_S_OK;
}

static cf_rv_t _digest_finish(cf_digest_t digest, void *output, size_t *output_len) {
	struct _mhash_digest *impl = (struct _mhash_digest*)digest;
	size_t real_len = mhash_get_block_size(mhash_get_mhash_algo(impl->mhash));
	if(!output && output_len) {
		*output_len = real_len;
		return CF_S_OK;
	}
	if(!output && !output_len) {
		mhash_deinit(impl->mhash, NULL);
		impl->mhash = NULL;
		free(impl);
		return CF_S_OK;
	}
	if(*output_len < real_len) {
		*output_len = real_len;
		return CF_E_INSUFFICIENT_BUFFER;
	}
	*output_len = real_len;
	mhash_deinit(impl->mhash, output);
	free(impl);
	return CF_S_OK;
}

static cf_rv_t _digest_clone(cf_digest_t *new_digest, cf_digest_t source) {
	struct _mhash_digest *source_impl = (struct _mhash_digest*)source;
	MHASH tmp = mhash_cp(source_impl->mhash);
	if(MHASH_FAILED == tmp)
		return CF_E_MEM;
	*new_digest = create_mhash_container(tmp);
	if(!*new_digest) {
		mhash_deinit(tmp, NULL);
		return CF_E_MEM;
	}
	return CF_S_OK;
}

static struct cf_digest_instance_ops mhash_digest_instance_ops = {
	_digest_update,
	_digest_finish,
	_digest_clone
};

static cf_digest_t create_mhash_container(MHASH hash) {
	struct _mhash_digest *impl = calloc(1, sizeof(*impl));
	if(!impl)
		return NULL;
	impl->digest.ops = &mhash_digest_instance_ops;
	impl->mhash = hash;
	return (cf_digest_t)impl;
}

static cf_rv_t _digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	MHASH hash = mhash_init((hashid)id);
	if(MHASH_FAILED == hash)
		return CF_E_UNKNOWN;
	*digest = create_mhash_container(hash);
	if(!*digest) {
		mhash_deinit(hash, NULL);
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
	while(*id <= mhash_count()) {
		const char *name = (const char*)mhash_get_hash_name_static(*id);
		if(!name) {
			++*id;
			continue;
		}
		info->id = *id;
		info->name = name;
		info->block_size = mhash_get_block_size(*id);
		++*id;
		return CF_S_OK;
	}
	return CF_S_COMPLETE;
}
static cf_rv_t _digest_list_end(cf_provider_t provider, void **iter) {
	*iter = NULL;
	return CF_S_OK;
}

struct cf_digest_ops mhash_digest_ops = {
		_digest_init,
		_digest_list_begin,
		_digest_list_next,
		_digest_list_end
};
