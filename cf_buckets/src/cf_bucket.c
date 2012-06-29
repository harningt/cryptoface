/*
 * Copyright (c) 2012 Thomas Harning Jr. <harningt@gmail.com>
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cf_bucket.h"
#include "cf_bucket_internal.h"

int cf_bucket_release(cf_bucket_t bucket)
{
    if (!bucket) {
        return -1;
    }
    return bucket->ops->release(bucket);
}
