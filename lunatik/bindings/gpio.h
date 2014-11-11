#ifndef __LUNATIK_BINDINGS_GPIO
#define __LUNATIK_BINDINGS_GPIO
#include "../lunatik.h"

int luak_direction_input(lua_State *L);
int luak_direction_output(lua_State *L);

int luak_gpio_request(lua_State *L);
int luak_gpio_free(lua_State *L);


#endif
