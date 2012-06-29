/*
 * Copyright (c) 2012 Thomas Harning Jr. <harningt@gmail.com>
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef CF_BUCKET_MANAGER_INTERNAL_H
#define CF_BUCKET_MANAGER_INTERNAL_H

#include "cf_bucket_manager.h"

/**
 * Acquires a new bucket instance of a specific size.
 * The data must be >= sizeof base bucket as the front may be used for
 * management purposes (such as bucket re-use).
 *
 * @param bucket pointer to store allocated bucket in
 * @param manager pointer to operate on
 * @param size number of bytes to allocate for struct
 *
 * @returns 0 on success, non-zero on failure
 */
int cf_bucket_manager_allocate(cf_bucket_t *bucket, cf_bucket_manager_t manager, size_t size);

/**
 * Releases a bucket instance using its internally stored manager.
 *
 * @param bucket instance to release
 *
 * @returns 0 on success, non-zero on failure
 */
int cf_bucket_manager_release(cf_bucket_t bucket);

#endif
