#include "provider.h"

#include <stdlib.h>
#include <string.h>

#include <assert.h>

struct cf_attr {
	int id;
	char *str_value;
	int int_value;
};
static void attr_free(struct cf_attr *attr) {
	if(attr->str_value)
		free(attr->str_value);
}
static int attr_cmp(const void *a, const void *b) {
	return ((struct cf_attr*)a)->id - ((struct cf_attr*)b)->id;
}

struct cf_attrs {
	/** sorted collection of attributes */
	struct cf_attr *attributes;
	int attribute_count;
};

cf_rv_t cf_provider_attr_init(cf_attrs_t *attr) {
	assert(attr);
	cf_attrs_t ret = calloc(1, sizeof(*ret));
	if(!ret)
		return CF_E_MEM;
	*attr = ret;
	return CF_S_OK;
}

cf_rv_t cf_provider_attr_destroy(cf_attrs_t attr) {
	assert(attr);
	if(attr->attributes) {
		int i;
		for(i = 0; i < attr->attribute_count; i++) {
			attr_free(&attr->attributes[i]);
		}
		free(attr->attributes);
	}
	free(attr);
}

cf_rv_t set_attribute(cf_attrs_t attrs, struct cf_attr value) {
	struct cf_attr *res;
	res = !attrs->attributes ? NULL : bsearch(&value, attrs->attributes, attrs->attribute_count, sizeof(value), attr_cmp);
	if(!res) {
		struct cf_attr *new_list = realloc(attrs->attributes, sizeof(*new_list) * attrs->attribute_count + 1);
		if(!new_list)
			return CF_E_MEM;
		attrs->attributes = new_list;
		attrs->attributes[attrs->attribute_count] = value;
		attrs->attribute_count++;
		qsort(attrs->attributes, attrs->attribute_count, sizeof(value), attr_cmp);
	}
	return CF_S_OK;
}

cf_rv_t cf_provider_attr_set_string(cf_attrs_t attrs, cf_attr_id_t id, const char *value) {
	struct cf_attr attr;
	assert(attrs);
	assert(value);
	attr.id = id;
	attr.str_value = strdup(value);
	if(!attr.str_value)
		return CF_E_MEM;
	return set_attribute(attrs, attr);
}

cf_rv_t cf_provider_attr_set_integer(cf_attrs_t attrs, cf_attr_id_t id, int value) {
	struct cf_attr attr;
	assert(attrs);
	attr.id = id;
	attr.int_value = value;
	return set_attribute(attrs, attr);
}

cf_rv_t cf_provider_attr_find_id(cf_provider_t provider, const char *name, cf_attr_id_t *id) {
	return CF_E_NOT_IMPLEMENTED;
}

struct cf_named_attr_id *cf_provider_attr_get_ids(cf_provider_t provider) {
	return NULL;
}

void cf_provider_attr_destroy_ids(cf_provider_t provider, struct cf_named_attr_id *id_list) {
}


cf_rv_t cf_provider_init(cf_provider_t *provider, const cf_attrs_t attrs, const char *path) {
	return CF_E_NOT_IMPLEMENTED;
}

cf_rv_t cf_provider_destroy(cf_provider_t *provider) {
	return CF_E_NOT_IMPLEMENTED;
}
