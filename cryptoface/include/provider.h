#ifndef CF_PROVIDER_H
#define CF_PROVIDER_H

#include "cryptoface.h"

/** Initializes an attribute collection for provider construction
 * @param attr Attribute collection to point to an initialized one
 */
cf_rv_t cf_provider_attr_init(cf_attrs_t *attr);
/** Destroys an attribute collection for provider construction
 * @param attr Attribute collection to destroy
 */
cf_rv_t cf_provider_attr_destroy(cf_attrs_t attr);

/** Sets a C-string value in the attribute collection
 * @param attr Attribute collection to alter
 * @param id Attribute identifier to set the value for
 * @param value C-string value to set (copied)
 */
cf_rv_t cf_provider_attr_set_string(cf_attrs_t attr, cf_attr_id_t id, const char *value);

/** Sets an integer value in the attribute collection
 * @param attr Attribute collection to alter
 * @param id Attribute identifier to set the value for
 * @param value integer value ot set
 */
cf_rv_t cf_provider_attr_set_integer(cf_attrs_t attr, cf_attr_id_t id, int value);

/** Locates the identifier for attribute setting
 * @param name Name of the identifier to resolve
 * @param id Attribute identifier to load
 */
cf_rv_t cf_provider_attr_find_id(cf_provider_t provider, const char *name, cf_attr_id_t *id);

/** Returns a NULL-name terminated array of named attribute identifiers */
struct cf_named_attr_id *cf_provider_attr_get_ids(cf_provider_t provider);
/** Release resources allocated for listing named attribute identifiers
 * @param id_list List of identifiers to release
 */
void cf_provider_attr_destroy_ids(cf_provider_t provider, struct cf_named_attr_id *id_list);


/** Initializes a provider with the given attributes and provider path
 * @param provider Pointer to location of provider to initialize
 * @param attr Attribute collection to parameterize provider instantiation
 * @param path Path to the provider to initialize, generally a pointer to a DLL
 * @return Status of provider initialization.  On any error, no provider is initialized.
 */
cf_rv_t cf_provider_init(cf_provider_t *provider, const cf_attrs_t attrs, const char *path);

/** Marks the provider's resources for collection when no references exist.
 * @param provider Pointer to the location of the provider to release
 * @return Status of provider destruction.
 *   CF_S_IN_USE : Provider is currently in use and will be released when those uses are eliminated.
 */
cf_rv_t cf_provider_destroy(cf_provider_t provider);

#endif
