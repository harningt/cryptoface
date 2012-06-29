/*
 * Copyright (c) 2012 Thomas Harning Jr. <harningt@gmail.com>
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef CF_BUCKET_INTERNAL_H
#define CF_BUCKET_INTERNAL_H

#include "cf_bucket.h"
#include "cf_bucket_manager.h"

/**
 * @see cf_bucket_release
 */
typedef int (* cf_bucket_release_op)(cf_bucket_t);

struct cf_bucket_ops {
    cf_bucket_release_op release;
};

struct cf_bucket {
    /* BEGIN cf_bucket_manager_t MANAGED DATA */
    cf_bucket_manager_t manager;
    /* END cf_bucket_manager_t MANAGED DATA */
    const struct cf_bucket_ops *ops;
};

#endif
