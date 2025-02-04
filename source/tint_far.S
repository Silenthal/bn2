#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

@ Start: 0x1E5A64


_fts Tint_ApplyToPalette
    push       {r5,lr}
    cmp        r6,#0x0
    ble        LAB_0300658a
    mov        r12,r0
    ldr        r1,PTR_PTR_Tint_ColorAdd_0300658c
    ldr        r2,[r1,r2]
    mov        r9,r2
    ldr        r2,INT_03006598
    ldr        r3,INT_0300659c
    ldr        r1,INT_030065a0
    mov        r8,r1
LAB_0300657a:
    mov        r0,r12
    ldrh       r1,[r7,r6]
    mov        r4,r9
    mov        lr,pc
    bx         r4
    strh       r0,[r7,r6]
    sub        r6,#0x2
    bge        LAB_0300657a
LAB_0300658a:
    pop        {r5,pc}

PTR_PTR_Tint_ColorAdd_0300658c:
    .word PTR_Tint_ColorAdd_03006590_far

far_global_label PTR_Tint_ColorAdd_03006590
    .word Tint_ColorAdd_far
    .word Tint_ColorSubtract_far

INT_03006598:
    .word 0x7BDE

INT_0300659c:
    .word 0x8420

INT_030065a0:
    .word 0x3DEF


_fts Tint_ColorAdd
    add        r4,r0,#0x0
    and        r4,r1
    lsl        r4,r4,#0x1
    add        r5,r0,#0x0
    eor        r5,r1
    and        r5,r2
    add        r4,r4,r5
    and        r4,r3
    lsl        r4,r4,#0x10
    lsr        r4,r4,#0x15
    add        r4,r8
    add        r0,r0,r1
    mov        r1,r8
    eor        r4,r1
    sub        r0,r0,r4
    orr        r0,r4
    mov        pc,lr


_fts Tint_ColorSubtract
    mvn        r5,r1
    add        r4,r0,#0x0
    and        r4,r5
    lsl        r4,r4,#0x1
    eor        r5,r0
    and        r5,r2
    add        r4,r4,r5
    and        r4,r3
    lsl        r4,r4,#0x10
    lsr        r4,r4,#0x15
    add        r4,r8
    mov        r5,r8
    eor        r4,r5
    orr        r1,r4
    orr        r0,r4
    sub        r0,r1,r0
    mov        pc,lr

    .byte 0, 0 @ TODO: Till following file is set
