#include "cryptoface.h"
#include "cryptoface_impl.h"
#include "digest_impl.h"

#include <gcrypt.h>

struct _gcrypt_digest {
	struct cf_digest digest;
	gcry_md_hd_t handle;
};

static cf_digest_t create_gcrypt_container(gcry_md_hd_t handle);

static cf_rv_t _digest_update(cf_digest_t digest, void *data, size_t data_len) {
	struct _gcrypt_digest *impl = (struct _gcrypt_digest*)digest;
	gcry_md_write(impl->handle, data, data_len);
	return CF_S_OK;
}

static cf_rv_t _digest_finish(cf_digest_t digest, void *output, size_t *output_len) {
	struct _gcrypt_digest *impl = (struct _gcrypt_digest*)digest;
	int algo = gcry_md_get_algo(impl->handle);
	size_t real_len = gcry_md_get_algo_dlen(algo);
	const char *md_output;
	if(!output && output_len) {
		*output_len = real_len;
		return CF_S_OK;
	}
	if(!output && !output_len) {
		gcry_md_close(impl->handle);
		impl->handle = NULL;
		return CF_S_OK;
	}
	if(*output_len < real_len) {
		*output_len = real_len;
		return CF_E_INSUFFICIENT_BUFFER;
	}
	*output_len = real_len;
	/* Read default digest output */
	gcry_md_final(impl->handle);
	md_output = gcry_md_read(impl->handle, 0);
	memcpy(output, md_output, real_len);
	gcry_md_close(impl->handle);
	impl->handle = NULL;
	return CF_S_OK;
}

static cf_rv_t _digest_clone(cf_digest_t *new_digest, cf_digest_t source) {
	struct _gcrypt_digest *source_impl = (struct _gcrypt_digest*)source;
	gcry_md_hd_t tmp;
	gcry_error_t rv = gcry_md_copy(&tmp, source_impl->handle);
	if (GPG_ERR_NO_ERROR != gpg_err_code(rv)) {
		return CF_E_UNKNOWN;
	}
	*new_digest = create_gcrypt_container(tmp);
	if(!*new_digest) {
		gcry_md_close(tmp);
		return CF_E_MEM;
	}
	return CF_S_OK;
}

static struct cf_digest_instance_ops gcrypt_digest_instance_ops = {
	_digest_update,
	_digest_finish,
	_digest_clone
};

static cf_digest_t create_gcrypt_container(gcry_md_hd_t handle) {
	struct _gcrypt_digest *impl = calloc(1, sizeof(*impl));
	if(!impl) {
		return NULL;
	}
	impl->digest.ops = &gcrypt_digest_instance_ops;
	impl->handle = handle;
	return (cf_digest_t)impl;
}

static cf_rv_t _digest_init(cf_digest_t *digest, cf_provider_t provider, cf_digest_id_t id) {
	gcry_md_hd_t handle = NULL;
	gcry_error_t rv = gcry_md_open(&handle, id, 0);
	if (GPG_ERR_NO_ERROR != gpg_err_code(rv)) {
		return CF_E_UNKNOWN;
	}
	*digest = create_gcrypt_container(handle);
	if(!*digest) {
		gcry_md_close(handle);
		return CF_E_MEM;
	}
	return CF_S_OK;
}
/* collect information */
struct gcrypt_digest_iter {
	int *list;
	int list_length;
	int idx;
};

static cf_rv_t _digest_list_begin(cf_provider_t provider, void **iter) {
	struct gcrypt_digest_iter *iter_value = calloc(1, sizeof(*iter));
	gcry_error_t rv;
	if (!iter_value) {
		rv = CF_E_MEM;
		goto fail;
	}
	rv = gcry_md_list(NULL, &iter_value->list_length);
	if (GPG_ERR_NO_ERROR != gcry_err_code(rv)) {
		rv = CF_E_UNKNOWN;
		goto fail;
	}
	iter_value->list = calloc(iter_value->list_length, sizeof(*iter_value->list));
	rv = gcry_md_list(iter_value->list, &iter_value->list_length);
	if (GPG_ERR_NO_ERROR != gcry_err_code(rv)) {
		rv = CF_E_UNKNOWN;
		goto fail;
	}
	*iter = iter_value;
	return CF_S_OK;
fail:
	if (iter_value) {
		if (iter_value->list) {
			free(iter_value->list);
			iter_value->list = NULL;
		}
		free(iter_value);
		iter_value = NULL;
	}
	return rv;
}
static cf_rv_t _digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info) {
	struct gcrypt_digest_iter *iter_value = *iter;
	while(iter_value->idx < iter_value->list_length) {
		int algo = iter_value->list[iter_value->idx];
		info->id = algo;
		info->name = gcry_md_algo_name(algo);
		info->block_size = gcry_md_get_algo_dlen(algo);
		++iter_value->idx;
		return CF_S_OK;
	}
	return CF_S_COMPLETE;
}
static cf_rv_t _digest_list_end(cf_provider_t provider, void **iter) {
	struct gcrypt_digest_iter *iter_value = *iter;
	if (iter_value) {
		if (iter_value->list) {
			free(iter_value->list);
			iter_value->list = NULL;
		}
		free(iter_value);
		iter_value = NULL;
	}
	*iter = NULL;
	return CF_S_OK;
}

struct cf_digest_ops gcrypt_digest_ops = {
		_digest_init,
		_digest_list_begin,
		_digest_list_next,
		_digest_list_end
};
