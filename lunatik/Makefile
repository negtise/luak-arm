obj-$(CONFIG_LUNATIK) += luak.o

EXTRA_CFLAGS += -Ilib/lunatik/lua/include 

luak-objs := lunatik.o lkworkqueue.o lsyscall.o setjmp.o \
            lua/lapi.o lua/lcode.o lua/ldebug.o lua/ldo.o lua/ldump.o lua/lfunc.o lua/lgc.o lua/llex.o lua/lmem.o \
            lua/lobject.o lua/lopcodes.o lua/lparser.o lua/lstate.o lua/lstring.o lua/ltable.o lua/ltm.o  \
            lua/lundump.o lua/lvm.o lua/lzio.o lua/lauxlib.o  \
            bindings/printk.o bindings/misc.o bindings/crypto.o bindings/buffer.o \
            bindings/gpio.o bindings/register.o

