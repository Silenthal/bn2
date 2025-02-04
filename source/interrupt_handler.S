#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

@ Start: 0x1E5800

    .syntax unified

    .arm

    .global srcInterruptHandlerStart
srcInterruptHandlerStart:
    mov        r3,#REG_BASE
    add        r3,r3,#OFFSET_REG_IE
    ldr        r2,[r3,#0x0]
    ldrh       r1,[r3,#0x8]
    mrs        r0,spsr
    stmdb      sp!,{r0,r1,r2,r3,lr}
    mov        r0,#0x1
    strh       r0,[r3,#0x8]
    and        r1,r2,r2, lsr #0x10
    mov        r12,#0x0
    ands       r0,r1,#0x1
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x2
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x4
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x8
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x10
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x20
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0xc0
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x100
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x200
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x400
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x800
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x1000
    bne        handleInterrupt
    add        r12,r12,#0x4
    ands       r0,r1,#0x2000
    strbne     r0,[r3,#-0x17c]

    bne        .

handleInterrupt:
    strh       r0,[r3,#0x2]
    mov        r1,#0x20c0
    bic        r2,r2,r0
    and        r1,r1,r2
    strh       r1,[r3,#0x0]
    mrs        r3,cpsr
    bic        r3,r3,#0xdf
    orr        r3,r3,#0x1f
    msr        cpsr_cf,r3
    ldr        r1,=interruptVector
    add        r1,r1,r12
    ldr        r0,[r1,#0x0]
    stmdb      sp!,{lr}
    adr        lr,afterBranch
    bx         r0
afterBranch:
    ldmia      sp!,{lr}
    mrs        r3,cpsr
    bic        r3,r3,#0xdf
    orr        r3,r3,#0x92
    msr        cpsr_cf,r3
    ldmia      sp!,{r0,r1,r2,r3,lr}
    strh       r2,[r3,#0x0]
    strh       r1,[r3,#0x8]
    msr        spsr_cf,r0
    bx         lr

    .pool


_fts IRQ_Dummy
    bx         lr


_fts IRQ_VBlank
    ldr        r0,=gVBlankFrameCounter
    ldr        r1,[r0,#0x0]
    adds       r1,#0x1
    str        r1,[r0,#0x0]
    push       {lr}
    ldr        r0,=Sound_VSync
    mov        lr,pc
    bx         r0
    pop        {r0}
    bx         r0


_fts IRQ_VCount
    push       {lr}
    ldr        r0,PTR_Sound_Main
    mov        lr,pc
    bx         r0
    pop        {r0}
    bx         r0

PTR_Sound_Main:
    .word Sound_Main
    .word 0x2008720


_fts IRQ_VCountBG1
    ldr        r0,=REG_VCOUNT
    ldrh       r0,[r0,#0x0]
    lsrs       r0,r0,#0x3
    ldr        r1,=tempBg1Hofs
    ldrb       r1,[r1,r0]
    ldr        r0,=REG_BG1HOFS
    strh       r1,[r0,#0x0]
    bx         lr

    .pool
