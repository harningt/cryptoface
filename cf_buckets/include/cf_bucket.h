/*
 * Copyright (c) 2012 Thomas Harning Jr. <harningt@gmail.com>
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef CF_BUCKET_H
#define CF_BUCKET_H

#include <stdlib.h> /* size_t */

/*
 * @TODO: Centralize result codes
 */

typedef struct cf_bucket *cf_bucket_t;

/**
 * Releases a bucket reference.
 *
 * @param bucket instance to release
 *
 * @returns 0 on success, non-zero on failure
 */
int cf_bucket_release(cf_bucket_t bucket);

#endif
