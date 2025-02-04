#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

@ Start: 0x1890


_ts BgUpdate_Set
    push       {r5,lr}
    tst        r0,r0
    beq        LAB_080018a2
    ldr        r5,PTR_gFuncPtrBgUpdatePostLoop_08001968
    str        r0,[r5,#0x0]
    str        r1,[r5,#0x8]
    str        r2,[r5,#0x4]
    ldr        r0,PTR_interruptVectorHblank_0
    str        r2,[r0,#0x0]
LAB_080018a2:
    pop        {r5,pc}


_ts BgUpdate_Init
    push       {r5,lr}
    ldr        r5,PTR_gFuncPtrBgUpdatePostLoop_08001970
    ldr        r0,PTR_BgUpdate_NoMove_08001974
    str        r0,[r5,#0x0]
    str        r0,[r5,#0x8]
    ldr        r1,PTR_IRQ_Dummy_08001978
    ldr        r0,PTR_interruptVectorHblank_1
    str        r1,[r0,#0x0]
    str        r1,[r5,#0x4]
    pop        {r5,pc}


_ts BgUpdate_CallPostLoopFunction
    push       {lr}
    ldr        r5,PTR_gFuncPtrBgUpdatePostLoop_08001980
    ldr        r0,[r5,#0x0]
    mov        lr,pc
    bx         r0
    pop        {pc}


_ts BgUpdate_CallPreLoopFunction
    push       {lr}
    ldr        r5,PTR_gFuncPtrBgUpdatePostLoop_08001984
    ldr        r0,[r5,#0x8]
    mov        lr,pc
    bx         r0
    pop        {pc}


_ts FUN_080018d0
    push       {lr}
    mov        r1,#0x0
LAB_080018d4:
    push       {r1}
    bl         Rng_RandomUint
    mov        r2,#0x7
    and        r0,r2
    add        r2,r0,#0x1
    pop        {r1}
    ldr        r0,PTR_tempBg1Hofs_08001988
    strb       r2,[r0,r1]
    push       {r1}
    bl         Rng_RandomUint
    mov        r2,#0x3
    and        r0,r2
    add        r2,r0,#0x1
    pop        {r1}
    ldr        r0,PTR_tempBg1Vofs_0800198c
    strb       r2,[r0,r1]
    add        r1,#0x1
    cmp        r1,#0x20
    blt        LAB_080018d4
    pop        {pc}


_ts FUN_08001900
    mov        r0,#0x0
    ldr        r1,PTR_tempBg1Hofs_08001990
    ldr        r2,PTR_tempBg1Vofs_08001994
LAB_08001906:
    ldrb       r3,[r1,r0]
    ldrb       r4,[r2,r0]
    add        r3,r3,r4
    strb       r3,[r1,r0]
    add        r0,#0x1
    cmp        r0,#0x20
    blt        LAB_08001906
    mov        pc,lr


_ts FUN_08001918
    mov        pc,lr


_ts BgUpdate_MoveUpLeft
    ldr        r1,PTR_tempBg1Hofs_08001998
    ldr        r2,[r1,#0x0]
    sub        r2,#0x8
    str        r2,[r1,#0x0]
    lsr        r2,r2,#0x4
    ldr        r1,PTR_tempBg1Vofs_0800199c
    ldr        r3,[r1,#0x0]
    sub        r3,#0x4
    str        r3,[r1,#0x0]
    lsr        r3,r3,#0x4
    mov        r7,r10
    ldr        r7,[r7,#0x10]
    strh       r2,[r7,#0x10]
    strh       r3,[r7,#0x12]
    mov        pc,lr


_ts BgUpdate_MoveUp
    ldr        r1,PTR_tempBg1Vofs_080019a0
    ldr        r3,[r1,#0x0]
    sub        r3,#0x4
    str        r3,[r1,#0x0]
    lsr        r3,r3,#0x4
    mov        r7,r10
    ldr        r7,[r7,#0x10]
    strh       r3,[r7,#0x12]
    mov        pc,lr


_ts BgUpdate_MoveRight
    ldr        r1,PTR_tempBg1Hofs_080019a4
    ldr        r2,[r1,#0x0]
    add        r2,#0x20
    str        r2,[r1,#0x0]
    lsr        r2,r2,#0x4
    mov        r7,r10
    ldr        r7,[r7,#0x10]
    strh       r2,[r7,#0x12]
    mov        pc,lr


_ts BgUpdate_NoMove
    mov        pc,lr

    .align 2, 0

PTR_gFuncPtrBgUpdatePostLoop_08001968:
    .word gFuncPtrBgUpdatePostLoop

PTR_interruptVectorHblank_0:
    .word interruptVectorHblank

PTR_gFuncPtrBgUpdatePostLoop_08001970:
    .word gFuncPtrBgUpdatePostLoop

PTR_BgUpdate_NoMove_08001974:
    .word BgUpdate_NoMove

PTR_IRQ_Dummy_08001978:
    .word IRQ_Dummy_far

PTR_interruptVectorHblank_1:
    .word interruptVectorHblank

PTR_gFuncPtrBgUpdatePostLoop_08001980:
    .word gFuncPtrBgUpdatePostLoop

PTR_gFuncPtrBgUpdatePostLoop_08001984:
    .word gFuncPtrBgUpdatePostLoop

PTR_tempBg1Hofs_08001988:
    .word tempBg1Hofs

PTR_tempBg1Vofs_0800198c:
    .word tempBg1Vofs

PTR_tempBg1Hofs_08001990:
    .word tempBg1Hofs

PTR_tempBg1Vofs_08001994:
    .word tempBg1Vofs

PTR_tempBg1Hofs_08001998:
    .word tempBg1Hofs

PTR_tempBg1Vofs_0800199c:
    .word tempBg1Vofs

PTR_tempBg1Vofs_080019a0:
    .word tempBg1Vofs

PTR_tempBg1Hofs_080019a4:
    .word tempBg1Hofs
