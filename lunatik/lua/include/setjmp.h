/*
 * arch/um/include/sysdep-i386/archsetjmp.h
 */

#ifndef _LUNATIK_SETJMP_H
#define _LUNATIK_SETJMP_H
/* FIXME: HACK ALERT! */
//#include "../../../../arch/x86/um/shared/sysdep/archsetjmp.h"

struct __jmp_buf {
	unsigned long __s0;
	unsigned long __s1;
	unsigned long __s2;
	unsigned long __s3;
	unsigned long __s4;
	unsigned long __s5;
	unsigned long __fp;
	unsigned long __ra;
	unsigned long __gp;
	unsigned long __sp;

	unsigned long __f2;
	unsigned long __f3;
	unsigned long __f4;
	unsigned long __f5;
	unsigned long __f6;
	unsigned long __f7;
	unsigned long __f8;
	unsigned long __f9;
};

/* Must be an array so it will decay to a pointer when a function is called */
typedef struct __jmp_buf jmp_buf[1];

extern int setjmp(jmp_buf);
extern void longjmp(jmp_buf, int);


#endif




/*
#ifndef _KLIBC_ARCHSETJMP_H
#define _KLIBC_ARCHSETJMP_H

struct __jmp_buf {
	unsigned int __ebx;
	unsigned int __esp;
	unsigned int __ebp;
	unsigned int __esi;
	unsigned int __edi;
	unsigned int __eip;
};

typedef struct __jmp_buf jmp_buf[1];

#define JB_IP __eip
#define JB_SP __esp

#endif		*/		/* _SETJMP_H */
