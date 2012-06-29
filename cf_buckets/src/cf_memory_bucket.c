/*
 * Copyright (c) 2012 Thomas Harning Jr. <harningt@gmail.com>
 * Released under the MIT license.  See included LICENSE details.
 */
#include "cf_memory_bucket.h"
#include "cf_bucket_internal.h"

static int cf_memory_bucket_static_release(cf_bucket_t bucket);

static const struct cf_bucket_ops STATIC_OPS = {
    cf_memory_bucket_static_release
};

struct cf_memory_bucket
{
    struct cf_bucket parent;
    void *data;
    size_t data_len;
    /* TODO: add bucket memory manager reference */
};

int cf_memory_bucket_static_new(cf_bucket_t *bucket, cf_bucket_manager_t manager, void *data, size_t data_len)
{
    struct cf_memory_bucket *instance = NULL;
    if (!bucket || (!data && data_len != 0)) {
        return -1;
    }
    instance = calloc(1, sizeof(*instance));
    if (!instance) {
        return -2;
    }
    instance->parent.ops = &STATIC_OPS;
    instance->data = data;
    instance->data_len = data_len;

    *bucket = &instance->parent;

    return 0;
}

static int cf_memory_bucket_static_release(cf_bucket_t bucket)
{
    if (!bucket) {
        return -1;
    }
    if (bucket->ops != &STATIC_OPS) {
        return -1;
    }
    free(bucket);
    return 0;
}
