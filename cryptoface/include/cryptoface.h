/*
 * Copyright (c) 2008-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef CRYPTOFACE_H
#define CRYPTOFACE_H

#include <stdlib.h>

typedef enum {
	/* CF_S_* == status result */
	CF_S_OK,
	CF_S_IN_USE,
	CF_S_COMPLETE,
	/* CF_E_* == error result */
	CF_E_UNKNOWN = 0x10000000,
	CF_E_NOT_IMPLEMENTED,
	CF_E_MEM,
	CF_E_INSUFFICIENT_BUFFER,
	CF_E_INVALID_ARGUMENTS
} cf_rv_t;

typedef struct cf_attrs *cf_attrs_t;

typedef int cf_attr_id_t;

struct cf_named_attr_id {
	const char *name;
	cf_attr_id_t id;
};
typedef struct cf_provider *cf_provider_t;

#ifdef WIN32
#ifdef cryptoface_EXPORTS
#define CF_API __declspec(dllexport)
#else
#define CF_API __declspec(dllimport)
#endif
#else
#define CF_API __attribute__((visibility("default"))) extern
#endif

#endif
