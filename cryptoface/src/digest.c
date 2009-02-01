#include "digest.h"

#include "cryptoface_impl.h"

#include "digest_impl.h"

cf_rv_t cf_digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	if(!provider->digest_ops.init)
		return CF_E_NOT_IMPLEMENTED;
	return provider->digest_ops.init(digest, provider, id);
}

cf_rv_t cf_digest_update(cf_digest_t digest, void *data, size_t data_len) {
	return digest->ops->update(digest, data, data_len);
}

cf_rv_t cf_digest_finish(cf_digest_t digest, void *buffer, size_t *buffer_len) {
	return digest->ops->finish(digest, buffer, buffer_len);
}

cf_rv_t cf_digest_clone(cf_digest_t *new_digest, cf_digest_t source) {
	if(!source->ops->clone)
		return CF_E_NOT_IMPLEMENTED;
	return source->ops->clone(new_digest, source);
}

/* list available digests */
cf_rv_t cf_digest_list_begin(cf_provider_t provider, void **iter) {
	if(!provider->digest_ops.list_begin)
		return CF_E_NOT_IMPLEMENTED;
	return provider->digest_ops.list_begin(provider, iter);
}

cf_rv_t cf_digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info) {
	return provider->digest_ops.list_next(provider, iter, info);
}

cf_rv_t cf_digest_list_end(cf_provider_t provider, void **iter) {
	return provider->digest_ops.list_end(provider, iter);
}
