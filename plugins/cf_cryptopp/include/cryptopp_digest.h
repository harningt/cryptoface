/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef CRYPTOPP_DIGEST_H_
#define CRYPTOPP_DIGEST_H_

#include "digest_impl.h"

extern struct cf_digest_ops cryptopp_digest_ops;

void cleanup_cryptopp_digest();

#endif /* CRYPTOPP_DIGEST_H_ */
