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

static int luak_register_readb(lua_State *L) {
    unsigned addr = (unsigned)luaL_checkint(L,-1);
	volatile unsigned long value;

	value = readb(addr);
    lua_pushinteger(L,value);

    return 1;
}

static int luak_register_writeb(lua_State *L) {
    unsigned addr = (unsigned)luaL_checkint(L,-1);

    int value = luaL_checkint(L,-1);
    writeb(addr,value);
    return 0;
}

static int luak_register_readw(lua_State *L) {
    unsigned addr = (unsigned)luaL_checkint(L,-1);
	volatile unsigned long value;

	value = readw(addr);
    lua_pushinteger(L,value);

    return 1;
}

static int luak_register_writew(lua_State *L) {
    unsigned addr = (unsigned)luaL_checkint(L,-1);
    int value = luaL_checkint(L,-1);
    
    writew(addr,value);

    return 0;
}

static int luak_register_readl(lua_State *L) {
    unsigned addr = (unsigned)luaL_checkint(L,-1);
	volatile unsigned long value;

	value = readl(addr);
    lua_pushinteger(L,value);
    return 1;
}

static int luak_register_writel(lua_State *L) {
    unsigned addr = (unsigned)luaL_checkint(L,-1);

    int value = luaL_checkint(L,-1);
    writel(addr,value);

    return 0;
}

int luak_reg_register(lua_State *L) {

    struct luaL_Reg lib_reg[] = {
    	{ "readb", &luak_register_readb},
    	{ "writeb", &luak_register_writeb},
    	{ "readw", &luak_register_readw},
    	{ "writew", &luak_register_writew},
    	{ "readl", &luak_register_readl},
    	{ "writel", &luak_register_writel},
    	{ NULL, NULL }
    };

	luaL_register(L, "reg", lib_reg);
	
	return 0;
}




