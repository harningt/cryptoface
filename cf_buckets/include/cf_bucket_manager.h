/*
 * Copyright (c) 2012 Thomas Harning Jr. <harningt@gmail.com>
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef CF_BUCKET_MANAGER_H
#define CF_BUCKET_MANAGER_H

#include "cf_bucket.h"

/**
 * Manager for bucket instantiation and release.
 */

typedef struct cf_bucket_manager *cf_bucket_manager_t;

/**
 * Obtains a new bucket manager instance.
 *
 * @param manager pointer to store new manage instance
 *
 * @returns 0 on success, non-zero on failure
 */
int cf_bucket_manager_new(cf_bucket_manager_t *manager);

/**
 * Releases a bucket manager instance.
 *
 * @param manager instance to operate on
 *
 * @returns 0 on success, non-zero on failure
 */
int cf_bucket_manager_destroy(cf_bucket_manager_t manager);

#endif
