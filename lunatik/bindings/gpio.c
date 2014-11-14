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
#include "../lua/lauxlib.h"

static int luak_direction_input(lua_State *L) {
    int ret;
    int port = luaL_checkint(L,-1);
    
    ret = gpio_direction_input(port);
    
    lua_pushinteger(L,ret);

	return 1;
}


static int luak_direction_output(lua_State *L) {
    int ret;
    int port = luaL_checkint(L,-2);
    int value = luaL_checkint(L,-1);
    
    ret = gpio_direction_output(port,value);
    
    lua_pushinteger(L,ret);

	return 1;
}

static int luak_gpio_request(lua_State *L) {
    unsigned port;
    int ret;

    port = luaL_checkint(L,-1);
    
    printk(KERN_ERR"gpio request %d \n",port);
    
    ret = gpio_request(port,NULL);
    
    lua_pushinteger(L,ret);
	
	return 1;
}


static int luak_gpio_free(lua_State *L) {
    unsigned port;

    port = luaL_checkint(L,-1);

    gpio_free(port);
   
	return 0;
}


int luak_gpio_register(lua_State *L) {
    struct luaL_Reg lib_gpio[] = {
    	{ "request", &luak_gpio_request },
    	{ "free", &luak_gpio_free },
    	{ "direction_input", &luak_direction_input },
    	{ "direction_output", &luak_direction_output },
    	{ NULL, NULL }
    };

	luaL_register(L, "gpio", lib_gpio);
	return 0;
}




