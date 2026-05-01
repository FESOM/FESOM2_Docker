/*
 * src/x86.c
 *
 * This work was supported by the Director, Office of Science, Division
 * of Mathematical, Information, and Computational Sciences of the
 * U.S. Department of Energy under contract number DE-AC03-76SF00098.
 *
 * Copyright (c) 2000-2001
 *
 * Contains functions to set and restore the round-to-double flag in the
 * control word of a x86 FPU.
 */

#ifdef x86
#ifndef _FPU_GETCW
#define _FPU_GETCW(x) asm volatile ("fnstcw %0":"=m" (x));
#endif

#ifndef _FPU_SETCW
#define _FPU_SETCW(x) asm volatile ("fldcw %0": :"m" (x));
#endif

#ifndef _FPU_EXTENDED
#define _FPU_EXTENDED 0x0300
#endif

#ifndef _FPU_DOUBLE
#define _FPU_DOUBLE 0x0200
#endif
#endif  /* x86 */

void shr_reprosumx86_fix_start(unsigned short *old_cw) {
#ifdef x86
  unsigned short new_cw;

  _FPU_GETCW(*old_cw);
  new_cw = (*old_cw & ~_FPU_EXTENDED) | _FPU_DOUBLE;
  _FPU_SETCW(new_cw);
#endif
}

void shr_reprosumx86_fix_end(unsigned short *old_cw) {
#ifdef x86
  _FPU_SETCW(*old_cw);
#endif
}

