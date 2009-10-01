#ifndef LUACF_H
#define LUACF_H

#include <lua.h>

#ifdef WIN32
#ifdef luacf_EXPORTS
#define LUACF_API __declspec(dllexport)
#else
#define LUACF_API __declspec(dllimport)
#endif
#else
#define LUACF_API __attribute__((visibility("default"))) extern
#endif

int LUACF_API luaopen_luacf(lua_State *L);

#endif /* LUACF_H */
