#ifndef CRYPTOFACE_IMPL_H_
#define CRYPTOFACE_IMPL_H_

#include "digest.h"

struct cf_provider_ops {
	cf_rv_t (*destroy)(cf_provider_t);
};
struct cf_digest_ops {
	cf_rv_t (*init)(cf_digest_t *,cf_provider_t,cf_digest_id_t);
	/* collect information */
	cf_rv_t (*list_begin)(cf_provider_t,void**);
	cf_rv_t (*list_next)(cf_provider_t,void**, struct cf_digest_info*);
	cf_rv_t (*list_end)(cf_provider_t,void**);
};

struct cf_provider {
	void *handle;
	struct cf_provider_ops provider_ops;
	struct cf_digest_ops digest_ops;
};

#endif /* CRYPTOFACE_IMPL_H_ */
