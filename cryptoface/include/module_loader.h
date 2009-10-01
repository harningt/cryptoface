#ifndef MODULE_LOADER_H
#define MODULE_LOADER_H

int cfp_module_load(const char *path, void **handle);

int cfp_module_get_symbol(void *handle, const char *name, void **symbol);

int cfp_module_unload(void *handle);

#endif /* MODULE_LOADER_H */
