#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

    .set Rng_RandomInt, 0x8001494+1
    .set SWI_Div, 0x80E8638+1
@ Start: 0xAD4


_ts memset0_8
    push       {r0,r1,r2,lr}
    mov        r2,#0x0
LAB_08000ad8:
    sub        r1,#0x1
    strb       r2,[r0,r1]
    bne        LAB_08000ad8
    pop        {r0,r1,r2,pc}


_ts memset0_16
    push       {r0,r1,r2,r3,lr}
    ldr        r2,=0x1000000
    lsr        r1,r1,#0x1
    orr        r2,r1
    add        r1,r0,#0x0
    sub        sp,#0x4
    mov        r0,#0x0
    str        r0,[sp,#0x0]
    mov        r0,sp
    svc        #0xb
    add        sp,#0x4
    pop        {r0,r1,r2,r3,pc}

    .align 2, 0

    .pool


_ts memset0_32
    push       {r0,r1,r2,r3,lr}
    ldr        r2,=0x5000000
    lsr        r1,r1,#0x2
    orr        r2,r1
    add        r1,r0,#0x0
    sub        sp,#0x4
    mov        r0,#0x0
    str        r0,[sp,#0x0]
    mov        r0,sp
    svc        #0xb
    add        sp,#0x4
    pop        {r0,r1,r2,r3,pc}

    .align 2, 0

    .pool


_ts memset0_256
    push       {r0,r1,r2,r3,lr}
    ldr        r2,=0x1000000
    lsr        r1,r1,#0x2
    orr        r2,r1
    add        r1,r0,#0x0
    sub        sp,#0x4
    mov        r0,#0x0
    str        r0,[sp,#0x0]
    mov        r0,sp
    svc        #0xc
    add        sp,#0x4
    pop        {r0,r1,r2,r3,pc}

    .align 2, 0

    .pool


_ts memcpy_8
    sub        r2,#0x1
    ldrb       r3,[r0,r2]
    strb       r3,[r1,r2]
    bne        memcpy_8
    mov        pc,lr


_ts memcpy_16
    push       {r0,r1,r2,r3,lr}
    ldr        r3,=0x0
    lsr        r2,r2,#0x1
    orr        r2,r3
    svc        #0xb
    pop        {r0,r1,r2,r3,pc}

    .align 2, 0

    .pool


_ts memcpy_32
    push       {r0,r1,r2,r3,lr}
    ldr        r3,=0x4000000
    lsr        r2,r2,#0x2
    orr        r2,r3
    svc        #0xb
    pop        {r0,r1,r2,r3,pc}

    .align 2, 0

    .pool


_ts memset_8
    sub        r1,#0x1
    strb       r2,[r0,r1]
    bne        memset_8
    mov        pc,lr


_ts memset_16
    push       {r0,r1,r2,r3,lr}
    add        r3,r2,#0x0
    ldr        r2,=0x1000000
    lsr        r1,r1,#0x1
    orr        r2,r1
    add        r1,r0,#0x0
    sub        sp,#0x4
    str        r3,[sp,#0x0]
    mov        r0,sp
    svc        #0xb
    add        sp,#0x4
    pop        {r0,r1,r2,r3,pc}

    .align 2, 0

    .pool


_ts memset_32
    push       {r0,r1,r2,r3,lr}
    add        r3,r2,#0x0
    ldr        r2,=0x5000000
    lsr        r1,r1,#0x2
    orr        r2,r1
    add        r1,r0,#0x0
    sub        sp,#0x4
    str        r3,[sp,#0x0]
    mov        r0,sp
    svc        #0xb
    add        sp,#0x4
    pop        {r0,r1,r2,r3,pc}

    .align 2, 0

    .pool


_ts GetVcountPlusVal
    ldr        r0,DAT_08000d94
    ldrh       r0,[r0,#0x0]
    ldr        r1,DAT_08000d98
    ldr        r1,[r1,#0x0]
    add        r0,r0,r1
    mov        pc,lr


_ts Divide
    mov        r2,#0x0
    ldr        r3,DAT_08000d9c
    mov        r4,#0x20
    mov        r5,#0x0
    mov        r6,#0x0
LAB_08000bb6:
    lsl        r0,r0,#0x1
    adc        r2,r6
    cmp        r2,r1
    bmi        LAB_08000bc2
    orr        r5,r3
    sub        r2,r2,r1
LAB_08000bc2:
    lsl        r2,r2,#0x1
    lsr        r3,r3,#0x1
    sub        r4,#0x1
    bne        LAB_08000bb6
    add        r0,r5,#0x0
    lsr        r2,r2,#0x1
    add        r1,r2,#0x0
    mov        pc,lr


_nt ConvertNumToBCD
    ldr        r1,=99999999
    cmp        r0,r1
    bmi        LAB_08000bdc
    ldr        r0,=0x99999999
    mov        pc,lr
LAB_08000bdc:
    ldr        r7,PTR_powersOf10_08000c20
    mov        r2,#0x0
    mov        r3,#0x8
LAB_08000be2:
    lsl        r2,r2,#0x4
    ldr        r1,[r7,#0x0]
    mov        r4,#0x0
LAB_08000be8:
    cmp        r0,r1
    bmi        LAB_08000bf2
    sub        r0,r0,r1
    add        r4,#0x1
    b          LAB_08000be8
LAB_08000bf2:
    orr        r2,r4
    add        r7,#0x4
    sub        r3,#0x1
    bne        LAB_08000be2
    add        r0,r2,#0x0
    mov        pc,lr

    .align 2, 0

powersOf10:
    .word 10000000
    .word 1000000
    .word 100000
    .word 10000
    .word 1000
    .word 100
    .word 10
    .word 1

PTR_powersOf10_08000c20:
    .word powersOf10

    .pool


_ts GetWidthOfBcdNumber
    push       {lr}
    mov        r1,#0x1
    tst        r0,r0
    beq        LAB_08000c40
    mov        r1,#0x0
LAB_08000c36:
    tst        r0,r0
    beq        LAB_08000c40
    add        r1,#0x1
    lsr        r0,r0,#0x4
    b          LAB_08000c36
LAB_08000c40:
    add        r0,r1,#0x0
    pop        {pc}


@@ Shuffles a given array by randomly exchanging elements.
@@ In:
@@ r0: array
@@ r1: arraySz
@@ r2: shuffleCount
_ts ArrayShuffle
    push       {r5,lr}
LAB_08000c46:
    push       {r0,r2}
    push       {r1}
    bl         Rng_RandomInt
    pop        {r1}
    push       {r1}
    svc        #0x6
    add        r3,r1,#0x0
    pop        {r1}
    push       {r1,r3}
    bl         Rng_RandomInt
    pop        {r1}
    push       {r1}
    svc        #0x6
    add        r4,r1,#0x0
    pop        {r1,r3}
    pop        {r0,r2}
    ldrb       r5,[r0,r3]
    ldrb       r6,[r0,r4]
    strb       r6,[r0,r3]
    strb       r5,[r0,r4]
    sub        r2,#0x1
    bne        LAB_08000c46
    pop        {r5,pc}


_ts GetRandomElementOfArray
    push       {lr}
    add        r7,r0,#0x0
    push       {r1,r7}
    bl         Rng_RandomInt
    pop        {r1,r7}
    bl         SWI_Div
    ldrb       r0,[r7,r1]
    pop        {pc}


_ts ArraySort
    push       {lr}
    cmp        r1,#0x2
    bmi        LAB_08000cb0
    mov        r3,#0x1
LAB_08000c94:
    ldrb       r2,[r0,r3]
    mov        r4,#0x0
LAB_08000c98:
    ldrb       r6,[r0,r4]
    cmp        r2,r6
    bhi        LAB_08000ca2
    strb       r2,[r0,r4]
    add        r2,r6,#0x0
LAB_08000ca2:
    add        r4,#0x1
    cmp        r4,r3
    bmi        LAB_08000c98
    strb       r2,[r0,r3]
    add        r3,#0x1
    cmp        r3,r1
    bmi        LAB_08000c94
LAB_08000cb0:
    pop        {pc}


@@ Converts an input value which represents 1/60ths of a second to the same
@@ value in the format hh:MM:ss.ff
_nt FrameTimeToBcdRealTime
    push       { lr }
    @ return early if a time greater than 100 hours is passed
    ldr        r1,=(100 * 60 * 60 * 60)
    cmp        r0,r1
    bmi        1f
    ldr        r0,=0x99595999
    pop        { pc }
1:
    ldr        r7,ptrTimeConsts
    mov        r2,#0x0
    mov        r3,#0x6
2:
    lsl        r2,r2,#0x4
    ldr        r1,[r7,#0x0]
    mov        r4,#0x0
3:
    cmp        r0,r1
    bmi        4f
    sub        r0,r0,r1
    add        r4,#0x1
    b          3b
4:
    orr        r2,r4
    add        r7,#0x4
    sub        r3,#0x1
    bne        2b
    lsl        r2,r2,#0x8
    push       { r2 }
    @ Next, converting remaining frame time (60ths of a second) to real time
    @ (100ths of a second) by doing (f * 0x1AAAA) >> 16 and then converting
    @ the result into BCD
    ldr        r1,=0x1AAAA
    mul        r0,r1
    lsr        r0,r0,#0x10
    bl         ConvertNumToBCD
    pop        { r2 }
    orr        r0,r2
    pop        { pc }

    .align 2, 0

timeConsts:
    .word 2160000
    .word 216000
    .word 36000
    .word 3600
    .word 600
    .word 60
    .word 10
    .word 1

ptrTimeConsts:
    .word timeConsts

    .pool

@@ Increments a timer, capping it at 99 hours and 59 minutes
_ts IncrementGameTimer
    mov        r7,r10
    ldr        r7,[r7,#0x78]
    ldr        r0,[r7,#0x24]
    add        r0,#0x1
    @ 99 hours and 50 minutes = 5999 minutes
    @ Multiply by 60 to get seconds, then by 60 again to get frames
    ldr        r1,=(5999 * 60 * 60)
    cmp        r0,r1
    ble        .setTime
    add        r0,r1,#0x0
.setTime:
    str        r0,[r7,#0x24]
    mov        pc,lr

    .align 2, 0

    .pool


_ts IncrementMPCounters
    mov        r7,r10
    ldr        r7,[r7,#0x78]
    ldr        r2,=999
    ldrh       r1,[r7,#0x22]
    add        r1,r1,r0
    cmp        r1,r2
    ble        LAB_08000d48
    add        r1,r2,#0x0
LAB_08000d48:
    strh       r1,[r7,#0x22]
    ldrh       r1,[r7,#0x20]
    add        r1,#0x1
    cmp        r1,r2
    ble        LAB_08000d54
    add        r1,r2,#0x0
LAB_08000d54:
    strh       r1,[r7,#0x20]
    mov        pc,lr

    .align 2, 0

    .pool


@@ Converts frame time to real time.
@@ r1 = hours, r2 = minutes, r3 = seconds, r4 = frames
_ts FrameTimeToRealTime_Reg
    push       { lr }
    sub        sp,#0x8
    @ hours
    ldr        r1,=(60 * 60 * 60)
    bl         SWI_Div
    str        r0,[sp,#0x0]
    add        r0,r1,#0x0
    @ minutes
    ldr        r1,=(60 * 60)
    bl         SWI_Div
    str        r0,[sp,#0x4]
    add        r0,r1,#0x0
    @ seconds
    ldr        r1,=60
    bl         SWI_Div
    add        r3,r0,#0x0
    add        r4,r1,#0x0
    ldr        r1,[sp,#0x0]
    ldr        r2,[sp,#0x4]
    add        sp,#0x8
    pop        { pc }

    .align 2, 0

    .pool

DAT_08000d94:
    .word REG_VCOUNT

DAT_08000d98:
    .word 0x2008720

DAT_08000d9c:
    .word 0x80000000
