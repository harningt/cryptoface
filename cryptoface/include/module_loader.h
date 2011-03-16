/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#ifndef MODULE_LOADER_H
#define MODULE_LOADER_H

int cfp_module_load(const char *path, void **handle);

int cfp_module_get_symbol(void *handle, const char *name, void **symbol);

int cfp_module_unload(void *handle);

#endif /* MODULE_LOADER_H */
