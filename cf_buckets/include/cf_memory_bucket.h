/*
 * Copyright (c) 2012 Thomas Harning Jr. <harningt@gmail.com>
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef CF_MEMORY_BUCKET_H
#define CF_MEMORY_BUCKET_H

#include "cf_bucket.h"
#include "cf_bucket_manager.h"

/* Header for simple memory-based buckets */

/**
 * Acquires a static, readonly, no-release bucket.
 *
 * @param bucket pointer to store the result in
 * @param data pointer to data
 * @param data_len length of data
 *
 * @return 0 on success, non-zero on failure
 */
int cf_memory_bucket_static_new(cf_bucket_t *bucket, cf_bucket_manager_t manager, void *data, size_t data_len);

#endif
