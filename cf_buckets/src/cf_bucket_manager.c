/*
 * Copyright (c) 2012 Thomas Harning Jr. <harningt@gmail.com>
 * Released under the MIT license.  See included LICENSE details.
 */

#include "cf_bucket_manager_internal.h"
#include "cf_bucket_internal.h"

#include "arena/proto.h"

#include <string.h> /* memset */

struct cf_bucket_manager {
    /* Standard allocator for buckets and associated data */
    const struct arena_prototype *arena;
};

int cf_bucket_manager_new(cf_bucket_manager_t *manager)
{
    if (!manager) {
        return -1;
    }
    *manager = calloc(1, sizeof(**manager));
    if (!*manager) {
        return -1;
    }
    (*manager)->arena = ARENA_STDLIB;
    return 0;
}

int cf_bucket_manager_destroy(cf_bucket_manager_t manager)
{
    if (!manager) {
        return -1;
    }
    /* TODO: perform any state cleanup on buckets allocated */
    free(manager);
    return 0;
}


int cf_bucket_manager_allocate(cf_bucket_t *bucket, cf_bucket_manager_t manager, size_t size)
{
    if (size < sizeof(**bucket)) {
        return -1;
    }
    *bucket = manager->arena->malloc(manager->arena, size, 0);
    if (!*bucket) {
        return -1;
    }
    memset(*bucket, 0, size);
    /* Store a self reference */
    (*bucket)->manager = manager;
    return 0;
}


int cf_bucket_manager_release(cf_bucket_t bucket)
{
    if (!bucket) {
        return -1;
    }
    if (!bucket->manager) {
        return -2;
    }
    bucket->manager->arena->free(bucket->manager->arena, bucket);
    return 0;
}
