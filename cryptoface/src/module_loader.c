/*
 * Copyright (c) 2009-2011 Thomas Harning Jr.
 * Released under the MIT license.  See included LICENSE details.
 */
#include "module_loader.h"
#include "cryptoface.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#ifdef WIN32

int cfp_module_load(const char *path, void **handle) {
	if (!handle)
		return CF_E_INVALID_ARGUMENTS;
	*handle = (void*)LoadLibraryA(path);
	return (*handle) ? CF_S_OK : CF_E_UNKNOWN;
}

int cfp_module_get_symbol(void *handle, const char *name, void **symbol) {
	if (!symbol)
		return CF_E_INVALID_ARGUMENTS;
	*symbol = GetProcAddress((HMODULE)handle, name);
	return (*symbol) ? CF_S_OK : CF_E_UNKNOWN;
}

int cfp_module_unload(void *handle) {
	FreeLibrary((HMODULE)handle);
	return CF_S_OK;
}

#else

int cfp_module_load(const char *path, void **handle) {
	if (!handle)
		return CF_E_INVALID_ARGUMENTS;
	*handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
	return (*handle) ? CF_S_OK : CF_E_UNKNOWN;
}

int cfp_module_get_symbol(void *handle, const char *name, void **symbol) {
	if (!symbol)
		return CF_E_INVALID_ARGUMENTS;
	*symbol = dlsym(handle, name);
	return (*symbol) ? CF_S_OK : CF_E_UNKNOWN;
}

int cfp_module_unload(void *handle) {
	dlclose(handle);
	return CF_S_OK;
}

#endif
