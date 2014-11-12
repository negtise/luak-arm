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

static int get_port_number(char port_type,int index) {
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
        return -1;
    }
    return port;
}

static int luak_get_port_index(lua_State *L) {
    unsigned port;
    const char *port_type = luaL_checkstring(L,-2);
    int index = luaL_checkint(L,-1);

    if (port_type == NULL) {
        return 0;
    }

    if (strlen(port_type) != 1) {
        return 0;
    }

    port = get_port_number(port_type[0],index);

    if (port == -1) {
		lua_pushstring(L, "invalide port type");
		lua_error(L);
		return 0;
    }
    
    lua_pushinteger(L,port);
    
    return 1;
}


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

static int luak_gpio_setcfg(lua_State *L) {
    int index = luaL_checkint(L,-2);
    int value = luaL_checkint(L,-1);
    int ret = sw_gpio_setcfg(index,value);
    lua_pushinteger(L,ret);
    return 1;
}

static int luak_gpio_getcfg(lua_State *L) {
    int index = luaL_checkint(L,-1);
    int ret = sw_gpio_getcfg(index);
    lua_pushinteger(L,ret);
    return 1;
}

static int luak_gpio_setpull(lua_State *L) {
    int index = luaL_checkint(L,-2);
    int value = luaL_checkint(L,-1);
    int ret = sw_gpio_setpull(index,value);
    lua_pushinteger(L,ret);
    return 1;
    return 0;
}

static int luak_gpio_getpull(lua_State *L) {
    int index = luaL_checkint(L,-1);
    int ret = sw_gpio_getpull(index);
    lua_pushinteger(L,ret);
    return 1;
}

static int luak_gpio_setdrvlevel(lua_State *L) {
    int index = luaL_checkint(L,-2);
    int value = luaL_checkint(L,-1);
    int ret = sw_gpio_setdrvlevel(index,value);
    lua_pushinteger(L,ret);
    return 1;
}

static int luak_gpio_getdrvlevel(lua_State *L) {
    int index = luaL_checkint(L,-1);
    int ret = sw_gpio_getdrvlevel(index);
    lua_pushinteger(L,ret);
    return 1;
}

static int luak_gpio_setallrange(lua_State *L) {
    int i;
    int len;
    struct gpio_config configs[30];
    if  (!lua_istable(L, -1)) {
        luaL_error(L, "setallrange expects first parameter to be a table");
        return 0;
    }
    len = lua_objlen(L,-1);
    if (len <= 0) {
        return 0;
    }
    
    memset(&configs,0,sizeof(configs));
    
    for (i=1;i<=len;i++) {
        lua_pushinteger(L,i);
        lua_gettable(L,-2);
        if (lua_istable(L, -1)) {
            int gpio;
            int mul_sel;
            int pull;
            int drv_level;
            int data;
            
            lua_getfield(L,-1,"gpio");
            gpio = luaL_checkint(L,-1);

            lua_getfield(L,-1,"mul_sel");
            mul_sel = luaL_checkint(L,-1);

            lua_getfield(L,-1,"pull");
            pull = luaL_checkint(L,-1);
            
            lua_getfield(L,-1,"drv_level");
            drv_level = luaL_checkint(L,-1);
            
            lua_getfield(L,-1,"data");
            data = luaL_checkint(L,-1);

            configs[i].gpio = gpio;            
            configs[i].mul_sel = mul_sel;            
            configs[i].pull = pull;
            configs[i].drv_level = drv_level;            
            configs[i].data = data;
            lua_remove(L,-1);
        }
        lua_remove(L,-1);
    }
    return 0;
}

static int luak_gpio_getallrange(lua_State *L) {
    return 0;
}

int luak_gpio_register(lua_State *L) {
    struct luaL_Reg lib_gpio[] = {
    	{ "get_port_index", &luak_get_port_index },
    	{ "direction_input", &luak_direction_input },
    	{ "direction_output", &luak_direction_output },
    	{ "request", &luak_gpio_request },
    	{ "free", &luak_gpio_free },
        {"setcfg",&luak_gpio_setcfg},
        {"getcfg",&luak_gpio_getcfg},
        {"setpull",&luak_gpio_setpull},
        {"getpull",&luak_gpio_getpull},
        {"setdrvlevel",&luak_gpio_setdrvlevel},
        {"getdrvlevel",&luak_gpio_getdrvlevel},
        {"setallrange",&luak_gpio_setallrange},
        {"getallrange",&luak_gpio_getallrange},
    	{ NULL, NULL }
    };

	luaL_register(L, "gpio", lib_gpio);
	return 0;
}




