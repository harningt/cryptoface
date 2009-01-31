#ifndef DIGEST_H_
#define DIGEST_H_

#include "cryptoface.h"

typedef struct cf_digest *cf_digest_t;

struct cf_digest_info {
	int id;
	const char *name;
	size_t block_size;
};

cf_rv_t cf_digest_init(cf_digest_t *digest, cf_provider_t provider, int id);

cf_rv_t cf_digest_update(cf_digest_t digest, void *data, size_t data_len);

cf_rv_t cf_digest_finish(cf_digest_t digest, void *buffer, size_t *buffer_len);

cf_rv_t cf_digest_destroy(cf_digest_t digest);

cf_rv_t cf_digest_clone(cf_digest_t *new_digest, cf_digest_t source);

/* list available digests */
cf_rv_t cf_digest_list_begin(cf_provider_t provider, void **iter);

cf_rv_t cf_digest_list_next(cf_provider_t provider, void **iter, struct cf_digest_info *info);

cf_rv_t cf_digest_list_end(cf_provider_t provider, void **iter);

#endif /* DIGEST_H_ */
