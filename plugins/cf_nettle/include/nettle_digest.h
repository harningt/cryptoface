/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef NETTLE_DIGEST_H_
#define NETTLE_DIGEST_H_

#include "digest_impl.h"

extern struct cf_digest_ops nettle_digest_ops;

void cleanup_nettle_digest();

#endif /* NETTLE_DIGEST_H_ */
