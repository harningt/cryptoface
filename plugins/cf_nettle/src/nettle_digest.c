/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "digest_impl.h"

#include <string.h> /* memcpy */
#include <nettle/nettle-meta.h>

struct _nettle_digest {
	struct cf_digest digest;
	const struct nettle_hash *hash;
	char context[1];
};
#define NETTLE_DIGEST_STRUCT_SIZE(context_size) (sizeof (struct _nettle_digest) - 1 + context_size)

static cf_digest_t create_hash_container(const struct nettle_hash *hash);

static cf_rv_t _digest_update(cf_digest_t digest, void *data, size_t data_len) {
	struct _nettle_digest *impl = (struct _nettle_digest*)digest;
	impl->hash->update((void*)impl->context, data_len, data);
	return CF_S_OK;
}

static cf_rv_t _digest_finish(cf_digest_t digest, void *output, size_t *output_len) {
	struct _nettle_digest *impl = (struct _nettle_digest*)digest;
	size_t real_len = impl->hash->digest_size;
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
	impl->hash->digest((void*)impl->context, *output_len, output);
	free(impl);
	return CF_S_OK;
}

static cf_rv_t _digest_clone(cf_digest_t *new_digest, cf_digest_t source) {
	struct _nettle_digest *impl = (struct _nettle_digest*)impl;
	struct _nettle_digest *new_impl;
	*new_digest = create_hash_container(impl->hash);
	if (!*new_digest) {
		return CF_E_MEM;
	}
	new_impl = (struct _nettle_digest*)*new_digest;
	memcpy(new_impl->context, impl->context, impl->hash->context_size);
	return CF_S_OK;
}

static struct cf_digest_instance_ops nettle_digest_instance_ops = {
	_digest_update,
	_digest_finish,
	_digest_clone
};

static cf_digest_t create_hash_container(const struct nettle_hash *hash) {
	struct _nettle_digest *impl = (struct _nettle_digest*)calloc(1, NETTLE_DIGEST_STRUCT_SIZE(hash->context_size));
	if(!impl) {
		return NULL;
	}
	impl->hash = hash;
	impl->digest.ops = &nettle_digest_instance_ops;
	return (cf_digest_t)impl;
}

static cf_rv_t _digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	const struct nettle_hash *hash = (struct nettle_hash *)id;
	struct _nettle_digest *impl;
	*digest = create_hash_container(hash);
	impl = (struct _nettle_digest*)*digest;
	if(!impl) {
		return CF_E_MEM;
	}
	hash->init((void*)impl->context);
	return CF_S_OK;
}

#define DIGEST(digest) (&digest),

static const struct nettle_hash *hash_list[] = {
#include "digest_list.h"
	NULL
};
#undef DIGEST

/* collect information */
static cf_rv_t _digest_list_begin(cf_provider_t provider, void **iter) {
	*iter = (void*)hash_list;
	return CF_S_OK;
}
static cf_rv_t _digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info) {
	const struct nettle_hash** hash_iter = (const struct nettle_hash**)*iter;
	const struct nettle_hash *hash = hash_iter ? *hash_iter : NULL;
	if(!hash) {
		return CF_S_COMPLETE;
	}
	info->id = (cf_digest_id_t)hash;
	info->name = hash->name;
	info->block_size = hash->digest_size;
	*iter = (void*)(hash_iter + 1);
	return CF_S_OK;
}
static cf_rv_t _digest_list_end(cf_provider_t provider, void **iter) {
	*iter = NULL;
	return CF_S_OK;
}

struct cf_digest_ops nettle_digest_ops = {
	_digest_init,
	_digest_list_begin,
	_digest_list_next,
	_digest_list_end
};
