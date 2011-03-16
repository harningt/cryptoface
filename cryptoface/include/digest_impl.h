/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef DIGEST_IMPL_H_
#define DIGEST_IMPL_H_

#include "digest.h"
#include "cryptoface.h"

struct cf_digest_instance_ops {
	cf_rv_t (*update)(cf_digest_t,void*,size_t);
	cf_rv_t (*finish)(cf_digest_t,void*,size_t*);
	cf_rv_t (*clone)(cf_digest_t*,cf_digest_t);
};

struct cf_digest {
	struct cf_digest_instance_ops *ops;
};

#endif /* DIGEST_IMPL_H_ */
