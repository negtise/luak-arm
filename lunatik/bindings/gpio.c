#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <mach/sys_config.h>
#include <mach/clock.h>
#include <mach/gpio.h>
#include <mach/system.h>


#include "../lunatik.h"


unsigned get_port_number(char port_type,int index) {
    unsigned port = 0;

    if (port_type == 'A'){
        port = GPIOA(index);
    }
    else if (port_type == 'B') {
        port = GPIOB(index);
    }
    else if (port_type == 'C') {
        port = GPIOC(index);
    }
    else if (port_type == 'D') {
        port = GPIOD(index);
    }
    else if (port_type == 'E') {
        port = GPIOE(index);
    }
    else if (port_type == 'F') {
        port = GPIOF(index);
    }
    else if (port_type == 'G') {
        port = GPIOG(index);
    }
    else if (port_type == 'H') {
        port = GPIOH(index);
    }
    else if (port_type == 'L') {
        port = GPIOL(index);
    }
    else if (port_type == 'M') {
        port = GPIOM(index);
    }
    else {
        return 0;
    }
    return port;
}

int luak_get_port_index(lua_State *L) {
    unsigned port;
    int ret;
    const char *port_type = luaL_checkstring(L,-2);
    int index = luaL_checkint(L,-1);

    if (port_type == NULL) {
        return 0;
    }

    if (strlen(port_type) != 1) {
        return 0;
    }

    port = get_port_number(port_type[0],index);
    
    lua_pushinteger(L,port);
    
    return 1;
}


int luak_direction_input(lua_State *L) {
    unsigned port;
    int ret;
    const char *port_type = luaL_checkstring(L,-2);
    int index = luaL_checkint(L,-1);
    
    if (port_type == NULL) {
        return 0;
    }

    if (strlen(port_type) != 1) {
        return 0;
    }

    port = get_port_number(port_type[0],index);

    if (port == 0) {
		lua_pushstring(L, "invalide port type");
		lua_error(L);
		return 0;
    }
    
    ret = gpio_direction_input(port);
    
    lua_pushinteger(L,ret);

	return 1;
}


int luak_direction_output(lua_State *L) {
    unsigned port = 0;
    int ret;
    const char *port_type = luaL_checkstring(L,-3);
    int index = luaL_checkint(L,-2);
    int value = luaL_checkint(L,-1);

    if (port_type == NULL) {
        return 0;
    }

    if (strlen(port_type) != 1) {
        return 0;
    }


    port = get_port_number(port_type[0],index);

    if (port == 0) {
		lua_pushstring(L, "invalide port type");
		lua_error(L);
		return 0;
    }
    
    ret = gpio_direction_output(port,value);
    
    lua_pushinteger(L,ret);

	return 1;
}


int luak_gpio_request(lua_State *L) {
    unsigned port = 0;
    int ret;

    const char *port_type = luaL_checkstring(L,-2);
    int index = luaL_checkint(L,-1);

    if (port_type == NULL) {
        return 0;
    }

    if (strlen(port_type) != 1) {
        return 0;
    }

    port = get_port_number(port_type[0],index);

    ret = gpio_request(port,NULL);
    
    lua_pushinteger(L,ret);

	return 1;
}


int luak_gpio_free(lua_State *L) {
    unsigned port = 0;

    const char *port_type = luaL_checkstring(L,-2);
    int index = luaL_checkint(L,-1);

    if (port_type == NULL) {
        return 0;
    }

    if (strlen(port_type) != 1) {
        return 0;
    }

    port = get_port_number(port_type[0],index);

    gpio_free(port);
   
	return 0;
}


