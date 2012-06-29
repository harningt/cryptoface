/*
 * Copyright (c) 2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef TOMCRYPT_DIGEST_H_
#define TOMCRYPT_DIGEST_H_

#include "digest_impl.h"

extern struct cf_digest_ops tomcrypt_digest_ops;

cf_rv_t tomcrypt_digest_setup();
cf_rv_t tomcrypt_digest_cleanup();

#endif /* TOMCRYPT_DIGEST_H_ */
