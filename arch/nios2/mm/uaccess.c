/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2009, Wind River Systems Inc
 * Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 */

#include <linux/export.h>
#include <linux/uaccess.h>

asm(".global	__copy_from_user\n"
    "   .type __copy_from_user, @function\n"
    "__copy_from_user:\n"
    "   movi  r2,7\n"
    "   mov   r3,r4\n"
    "   bge   r2,r6,1f\n"
    "   xor   r2,r4,r5\n"
    "   andi  r2,r2,3\n"
    "   movi  r7,3\n"
    "   beq   r2,zero,4f\n"
    "1: addi  r6,r6,-1\n"
    "   movi  r2,-1\n"
    "   beq   r6,r2,3f\n"
    "   mov   r7,r2\n"
    "2: ldbu  r2,0(r5)\n"
    "   addi  r6,r6,-1\n"
    "   addi  r5,r5,1\n"
    "   stb   r2,0(r3)\n"
    "   addi  r3,r3,1\n"
    "   bne   r6,r7,2b\n"
    "3:\n"
    "   addi  r2,r6,1\n"
    "   ret\n"
    "13:mov   r2,r6\n"
    "   ret\n"
    "4: andi  r2,r4,1\n"
    "   cmpeq r2,r2,zero\n"
    "   beq   r2,zero,7f\n"
    "5: andi  r2,r3,2\n"
    "   beq   r2,zero,6f\n"
    "9: ldhu  r2,0(r5)\n"
    "   addi  r6,r6,-2\n"
    "   addi  r5,r5,2\n"
    "   sth   r2,0(r3)\n"
    "   addi  r3,r3,2\n"
    "6: bge   r7,r6,1b\n"
    "10:ldw   r2,0(r5)\n"
    "   addi  r6,r6,-4\n"
    "   addi  r5,r5,4\n"
    "   stw   r2,0(r3)\n"
    "   addi  r3,r3,4\n"
    "   br    6b\n"
    "7: ldbu  r2,0(r5)\n"
    "   addi  r6,r6,-1\n"
    "   addi  r5,r5,1\n"
    "   addi  r3,r4,1\n"
    "   stb   r2,0(r4)\n"
    "   br    5b\n"
    ".section __ex_table,\"a\"\n"
    ".word 2b,3b\n"
    ".word 9b,13b\n"
    ".word 10b,13b\n"
    ".word 7b,13b\n"
    ".previous\n"
   );
EXPORT_SYMBOL(__copy_from_user);

asm(
    "   .global __copy_to_user\n"
    "   .type __copy_to_user, @function\n"
    "__copy_to_user:\n"
    "   movi  r2,7\n"
    "   mov   r3,r4\n"
    "   bge   r2,r6,1f\n"
    "   xor   r2,r4,r5\n"
    "   andi  r2,r2,3\n"
    "   movi  r7,3\n"
    "   beq   r2,zero,4f\n"
    /* Bail if we try to copy zero bytes  */
    "1: addi  r6,r6,-1\n"
    "   movi  r2,-1\n"
    "   beq   r6,r2,3f\n"
    /* Copy byte by byte for small copies and if src^dst != 0 */
    "   mov   r7,r2\n"
    "2: ldbu  r2,0(r5)\n"
    "   addi  r5,r5,1\n"
    "9: stb   r2,0(r3)\n"
    "   addi  r6,r6,-1\n"
    "   addi  r3,r3,1\n"
    "   bne   r6,r7,2b\n"
    "3: addi  r2,r6,1\n"
    "   ret\n"
    "13:mov   r2,r6\n"
    "   ret\n"
    /*  If 'to' is an odd address byte copy */
    "4: andi  r2,r4,1\n"
    "   cmpeq r2,r2,zero\n"
    "   beq   r2,zero,7f\n"
    /* If 'to' is not divideable by four copy halfwords */
    "5: andi  r2,r3,2\n"
    "   beq   r2,zero,6f\n"
    "   ldhu  r2,0(r5)\n"
    "   addi  r5,r5,2\n"
    "10:sth   r2,0(r3)\n"
    "   addi  r6,r6,-2\n"
    "   addi  r3,r3,2\n"
    /* Copy words */
    "6: bge   r7,r6,1b\n"
    "   ldw   r2,0(r5)\n"
    "   addi  r5,r5,4\n"
    "11:stw   r2,0(r3)\n"
    "   addi  r6,r6,-4\n"
    "   addi  r3,r3,4\n"
    "   br    6b\n"
    /* Copy remaining bytes */
    "7: ldbu  r2,0(r5)\n"
    "   addi  r5,r5,1\n"
    "   addi  r3,r4,1\n"
    "12: stb  r2,0(r4)\n"
    "   addi  r6,r6,-1\n"
    "   br    5b\n"
    ".section __ex_table,\"a\"\n"
    ".word 9b,3b\n"
    ".word 10b,13b\n"
    ".word 11b,13b\n"
    ".word 12b,13b\n"
    ".previous\n");
EXPORT_SYMBOL(__copy_to_user);

long strncpy_from_user(char *__to, const char __user *__from, long __len)
{
    int l = strnlen_user(__from, __len);
    int is_zt = 1;

    if (l > __len) {
        is_zt = 0;
        l = __len;
    }

    if (l == 0 || copy_from_user(__to, __from, l)) {
        return -EFAULT;
    }

    if (is_zt) {
        l--;
    }
    return l;
}

long strnlen_user(const char __user *s, long n)
{
    long i;

    for (i = 0; i < n; i++) {
        char c;

        if (get_user(c, s + i) == -EFAULT) {
            return 0;
        }
        if (c == 0) {
            return i + 1;
        }
    }
    return n + 1;
}
