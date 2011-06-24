/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "digest_impl.h"

#include <crypto++/cryptlib.h>
#include <crypto++/factory.h>

/* Pull in the digest_list just for the headers */
#define INCLUDE_DIGEST_HEADERS
#include "digest_list.h"
#undef INCLUDE_DIGEST_HEADERS

struct _cryptopp_digest {
	struct cf_digest digest;
	CryptoPP::HashTransformation *hash;
};

static cf_digest_t create_hash_container();

static cf_rv_t _digest_update(cf_digest_t digest, void *data, size_t data_len) {
	struct _cryptopp_digest *impl = (struct _cryptopp_digest*)digest;
	try {
		impl->hash->Update((byte*)data, data_len);
	} catch (std::exception &e) {
		(void)e;
		return CF_E_UNKNOWN;
	}
	return CF_S_OK;
}

static cf_rv_t _digest_finish(cf_digest_t digest, void *output, size_t *output_len) {
	struct _cryptopp_digest *impl = (struct _cryptopp_digest*)digest;
	size_t real_len = impl->hash->DigestSize();
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
		impl->hash->Final((byte*)output);
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
	/* No cloning digests currently (all clone ops throw) */
	return CF_E_NOT_IMPLEMENTED;
}

static struct cf_digest_instance_ops cryptopp_digest_instance_ops = {
	_digest_update,
	_digest_finish,
	_digest_clone
};

static cf_digest_t create_hash_container() {
	struct _cryptopp_digest *impl = (struct _cryptopp_digest*)calloc(1, sizeof(*impl));
	if(!impl) {
		return NULL;
	}
	impl->digest.ops = &cryptopp_digest_instance_ops;
	return (cf_digest_t)impl;
}

typedef CryptoPP::ObjectFactory<CryptoPP::HashTransformation> HashFactory;

template<typename T>
class HashFactoryInstance : public HashFactory {
	virtual CryptoPP::HashTransformation *CreateObject() const {
		return new T;
	}
};

/* TODO: Use central c-based map structure */
/* TODO: Remove use of 'static' modifiable value and move to provider */
static CryptoPP::ObjectFactoryRegistry<CryptoPP::HashTransformation> *digest_registry = NULL;

static void init_registry() {
	if (digest_registry) {
		return;
	}
	digest_registry = new CryptoPP::ObjectFactoryRegistry<CryptoPP::HashTransformation>;
#define DIGEST(TYPENAME) digest_registry->RegisterFactory(CryptoPP::TYPENAME::StaticAlgorithmName(), new HashFactoryInstance<CryptoPP::TYPENAME>);
#include "digest_list.h"
#undef DIGEST
}

static cf_rv_t _digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	init_registry();
	const char *md = (const char *)id;
	const HashFactory *factory = digest_registry->GetFactory(md);
	if (!factory) {
		return CF_E_UNKNOWN;
	}
	struct _cryptopp_digest *impl;
	*digest = create_hash_container();
	impl = (struct _cryptopp_digest*)*digest;
	if(!impl) {
		return CF_E_MEM;
	}
	try {
		impl->hash = factory->CreateObject();
	} catch (std::exception &e) {
		(void)e;
		free(impl);
		return CF_E_MEM;
	}
	return CF_S_OK;
}

#define DIGEST(TYPENAME) { \
	(cf_digest_id_t)CryptoPP::TYPENAME::StaticAlgorithmName(), \
	CryptoPP::TYPENAME::StaticAlgorithmName(), \
	CryptoPP::TYPENAME::DIGESTSIZE \
},

static struct cf_digest_info hash_list[] = {
#include "digest_list.h"
	{ (cf_digest_id_t)0, NULL, 0 }
};
#undef DIGEST

/* collect information */
static cf_rv_t _digest_list_begin(cf_provider_t provider, void **iter) {
	*iter = (void*)hash_list;
	return CF_S_OK;
}
static cf_rv_t _digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info) {
	const struct cf_digest_info *info_iter = (const struct cf_digest_info *)*iter;
	if(!info_iter || !info_iter->name) {
		return CF_S_COMPLETE;
	}
	info->id = info_iter->id;
	info->name = info_iter->name;
	info->block_size = info_iter->block_size;
	*iter = (void*)(info_iter + 1);
	return CF_S_OK;
}
static cf_rv_t _digest_list_end(cf_provider_t provider, void **iter) {
	*iter = NULL;
	return CF_S_OK;
}

struct cf_digest_ops cryptopp_digest_ops = {
		_digest_init,
		_digest_list_begin,
		_digest_list_next,
		_digest_list_end
};

void cleanup_cryptopp_digest()
{
	if (digest_registry) {
		delete digest_registry;
		digest_registry = NULL;
	}
}
