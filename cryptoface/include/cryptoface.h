#ifndef CRYPTOFACE_H
#define CRYPTOFACE_H

typedef enum {
	/* CF_S_* == status result */
	CF_S_OK,
	CF_S_IN_USE,
	/* CF_E_* == error result */
	CF_E_UNKNOWN = 0x10000000
} cf_rv_t;

typedef struct cf_attr *cf_attr_t;

typedef int cf_attr_id_t;

struct cf_named_attr_id {
	const char *name;
	cf_attr_id_t id;
};
typedef struct cf_provider *cf_provider_t;

#endif
