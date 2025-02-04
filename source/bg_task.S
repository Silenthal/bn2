#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

    .set FUN_0801d2d8, 0x801D2D8+1
@ Start: 0x19A8

bgTileBufferList:
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer1
    .word gBgTileDataBuffer2
    .word gBgTileDataBuffer3
    .word gBgTileDataBuffer4
    .word gBgTileDataBuffer5
    .word gBgTileDataBuffer6
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer7
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer7
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer7
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer7
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer7
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer8
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer9
    .word gBgTileDataBufferA
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBufferB
    .word gBgTileDataBufferC
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBufferD
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer0
    .word gBgTileDataBuffer9


_ts InitBgTask
    push       {lr}
    mov        r0,r10
    ldr        r0,[r0,#0x58]
    ldr        r1,DAT_08001a6c
    bl         memset0_32
    pop        {pc}

    .align 2, 0

DAT_08001a6c:
    .word 0x1B0


_ts BgTask_AddNew
    push       {r5,lr}
    mov        r7,r10
    ldr        r7,[r7,#0x58]
    ldrb       r1,[r0,#0x9]
    mov        r2,#0x18
    mul        r2,r1
    add        r7,r7,r2
    strb       r1,[r7,#0x1]
    ldr        r1,[r0,#0x0]
    str        r1,[r7,#0xc]
    ldr        r2,[r0,#0x4]
    str        r2,[r7,#0x10]
    ldr        r3,[r0,#0x8]
    str        r3,[r7,#0x14]
    add        r0,#0xc
    mov        r6,#0x1
    cmp        r3,#0x8
    beq        LAB_08001a96
    ldr        r6,[r0,#0x4]
LAB_08001a96:
    strh       r6,[r7,#0x2]
    mov        r6,#0x1
    strb       r6,[r7,#0x0]
    str        r0,[r7,#0x4]
    str        r0,[r7,#0x8]
    ldr        r6,PTR_PTR_BgTask_TransferDirect_08001aac
    ldrb       r1,[r7,#0x14]
    ldr        r6,[r6,r1]
    mov        lr,pc
    bx         r6
    pop        {r5,pc}

PTR_PTR_BgTask_TransferDirect_08001aac:
    .word PTR_BgTask_TransferDirect_08001b0c


_ts BgTask_Update
    push       {lr}
    mov        r7,r10
    ldr        r7,[r7,#0x58]
    mov        r4,#0x0
LAB_08001ab8:
    ldrb       r1,[r7,#0x0]
    tst        r1,r1
    bne        LAB_08001ac8
LAB_08001abe:
    add        r7,#0x18
    add        r4,#0x1
    cmp        r4,#0x12
    bge        LAB_08001b08
    b          LAB_08001ab8
LAB_08001ac8:
    ldrh       r1,[r7,#0x2]
    sub        r1,#0x1
    strh       r1,[r7,#0x2]
    cmp        r1,#0x0
    bgt        LAB_08001abe
    ldr        r0,[r7,#0x8]
    ldr        r1,PTR_INT_ARRAY_08001b34
    ldrb       r2,[r7,#0x14]
    ldr        r1,[r1,r2]
    add        r0,r0,r1
    ldr        r1,[r0,#0x0]
    cmp        r1,#0x0
    beq        LAB_08001b04
    cmp        r1,#0x2
    beq        LAB_08001aee
    cmp        r1,#0x1
    bne        LAB_08001af2
    ldr        r0,[r7,#0x4]
    b          LAB_08001af2
LAB_08001aee:
    ldr        r0,[r0,#0x4]
    str        r0,[r7,#0x4]
LAB_08001af2:
    str        r0,[r7,#0x8]
    ldr        r1,[r0,#0x4]
    strh       r1,[r7,#0x2]
    ldr        r6,PTR_PTR_BgTask_TransferDirect_08001b38
    ldrb       r1,[r7,#0x14]
    ldr        r6,[r6,r1]
    mov        lr,pc
    bx         r6
    b          LAB_08001abe
LAB_08001b04:
    mov        r1,#0x0
    strb       r1,[r7,#0x0]
LAB_08001b08:
    pop        {pc}

    .align 2, 0


PTR_BgTask_TransferDirect_08001b0c:
    .word BgTask_TransferDirect
    .word BgTask_TransferTilemap
    .word BgTask_TransferTileset
    .word BgTask_AddTint
    .word BgTask_PlaySE

INT_ARRAY_08001b20:
    .word 0x8
    .word 0x8
    .word 0x8
    .word 0x8
    .word 0x8

PTR_INT_ARRAY_08001b34:
    .word INT_ARRAY_08001b20

PTR_PTR_BgTask_TransferDirect_08001b38:
    .word PTR_BgTask_TransferDirect_08001b0c


_ts BgTask_TransferDirect
    push       {lr}
    push       {r4,r7}
    ldr        r0,[r0,#0x0]
    ldr        r1,[r7,#0xc]
    ldr        r2,[r7,#0x10]
    bl         Dma_TransferListAdd
    pop        {r4,r7}
    pop        {pc}


_ts BgTask_TransferTileset
    push       {lr}
    mov        r5,r10
    ldr        r5,[r5,#0x44]
    ldr        r5,[r5,#0xc]
    ldrb       r2,[r7,#0x17]
    lsl        r2,r2,#0x2
    add        r2,#0x4
    ldr        r2,[r5,r2]
    add        r5,r5,r2
    mov        r6,#0xf0
    lsl        r6,r6,#0x8
    ldrb       r2,[r7,#0x16]
    mov        r8,r7
LAB_08001b6a:
    ldr        r1,[r0,#0x0]
    ldr        r7,[r0,#0x4]
    ldrh       r3,[r5,r1]
    and        r3,r6
    orr        r3,r7
    strh       r3,[r5,r1]
    add        r0,#0x8
    sub        r2,#0x1
    bgt        LAB_08001b6a
    mov        r7,r8
    push       {r4,r7}
    mov        r7,r10
    ldr        r5,[r7,#0x44]
    bl         FUN_0801d2d8
    pop        {r4,r7}
    mov        r0,#0x0
    strb       r0,[r7,#0x0]
    pop        {pc}


_ts BgTask_TransferTilemap
    push       {r4,r7,lr}
    ldr        r6,[r0,#0x0]
    ldr        r5,PTR_PTR_ARRAY_08001be4
    ldrb       r4,[r7,#0x17]
    lsl        r4,r4,#0x2
    ldr        r5,[r5,r4]
    ldr        r4,[r7,#0xc]
    mov        r1,#0x0
    push       {r0}
LAB_08001ba2:
    ldrh       r2,[r6,r1]
    lsl        r3,r2,#0x16
    lsr        r3,r3,#0x16
    lsl        r3,r3,#0x5
    push       {r4,r6}
    add        r4,r4,r3
    ldr        r0,PTR_PTR_CopyTile_08001be0
    lsr        r2,r2,#0xa
    lsl        r2,r2,#0x2
    ldr        r0,[r0,r2]
    mov        lr,pc
    bx         r0
    pop        {r4,r6}
    add        r5,#0x20
    add        r1,#0x2
    ldrb       r2,[r7,#0x16]
    lsl        r2,r2,#0x1
    cmp        r1,r2
    blt        LAB_08001ba2
    pop        {r0}
    ldr        r0,PTR_PTR_ARRAY_08001be4
    ldrb       r1,[r7,#0x17]
    lsl        r1,r1,#0x2
    ldr        r0,[r0,r1]
    ldr        r1,[r7,#0x10]
    ldrb       r2,[r7,#0x16]
    lsl        r2,r2,#0x5
    lsr        r2,r2,#0x2
    bl         Dma_TransferListAdd
    pop        {r4,r7,pc}

PTR_PTR_CopyTile_08001be0:
    .word PTR_CopyTile_08001be8

PTR_PTR_ARRAY_08001be4:
    .word bgTileBufferList

PTR_CopyTile_08001be8:
    .word CopyTile
    .word CopyTile_HFlip
    .word CopyTile_VFlip
    .word CopyTile_HVFlip


_ts CopyTile
    ldr        r0,[r4,#0x0]
    str        r0,[r5,#0x0]
    ldr        r0,[r4,#0x4]
    str        r0,[r5,#0x4]
    ldr        r0,[r4,#0x8]
    str        r0,[r5,#0x8]
    ldr        r0,[r4,#0xc]
    str        r0,[r5,#0xc]
    ldr        r0,[r4,#0x10]
    str        r0,[r5,#0x10]
    ldr        r0,[r4,#0x14]
    str        r0,[r5,#0x14]
    ldr        r0,[r4,#0x18]
    str        r0,[r5,#0x18]
    ldr        r0,[r4,#0x1c]
    str        r0,[r5,#0x1c]
    mov        pc,lr


_ts CopyTile_HFlip
    ldr        r2,DAT_08001e94
    mov        r9,r2
    ldr        r2,DAT_08001e90
    mov        r8,r2
    ldr        r0,[r4,#0x0]
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x0]
    ldr        r0,[r4,#0x4]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x4]
    ldr        r0,[r4,#0x8]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x8]
    ldr        r0,[r4,#0xc]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0xc]
    ldr        r0,[r4,#0x10]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x10]
    ldr        r0,[r4,#0x14]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x14]
    ldr        r0,[r4,#0x18]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x18]
    ldr        r0,[r4,#0x1c]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x1c]
    mov        pc,lr


_ts CopyTile_VFlip
    ldr        r0,[r4,#0x0]
    str        r0,[r5,#0x1c]
    ldr        r0,[r4,#0x4]
    str        r0,[r5,#0x18]
    ldr        r0,[r4,#0x8]
    str        r0,[r5,#0x14]
    ldr        r0,[r4,#0xc]
    str        r0,[r5,#0x10]
    ldr        r0,[r4,#0x10]
    str        r0,[r5,#0xc]
    ldr        r0,[r4,#0x14]
    str        r0,[r5,#0x8]
    ldr        r0,[r4,#0x18]
    str        r0,[r5,#0x4]
    ldr        r0,[r4,#0x1c]
    str        r0,[r5,#0x0]
    mov        pc,lr


_ts CopyTile_HVFlip
    ldr        r2,DAT_08001e94
    mov        r9,r2
    ldr        r2,DAT_08001e90
    mov        r8,r2
    ldr        r0,[r4,#0x0]
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x1c]
    ldr        r0,[r4,#0x4]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8


_ts FUN_08001da0
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x18]
    ldr        r0,[r4,#0x8]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x14]
    ldr        r0,[r4,#0xc]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x10]
    ldr        r0,[r4,#0x10]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0xc]
    ldr        r0,[r4,#0x14]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x8]
    ldr        r0,[r4,#0x18]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x4]
    ldr        r0,[r4,#0x1c]
    mov        r2,r8
    lsr        r3,r2,#0x8
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x8
    lsl        r3,r3,#0x8
    orr        r0,r3
    mov        r2,#0x10
    ror        r0,r2
    mov        r2,r9
    lsr        r3,r2,#0x4
    and        r2,r0
    and        r3,r0
    lsr        r0,r2,#0x4
    lsl        r3,r3,#0x4
    orr        r0,r3
    str        r0,[r5,#0x0]
    mov        pc,lr

DAT_08001e90:
    .word 0xFF00FF00

DAT_08001e94:
    .word 0xF0F0F0F0


_ts BgTask_AddTint
    push       {lr}
    push       {r4,r7}
    ldr        r1,[r0,#0x0]
    lsl        r1,r1,#0x1
    lsr        r1,r1,#0x1
    ldrb       r0,[r7,#0xc]
    ldrb       r2,[r7,#0x16]
    ldrb       r3,[r7,#0x1]
    ldr        r4,[r7,#0x10]
    bl         Tint_Add
    pop        {r4,r7}
    pop        {pc}


_ts BgTask_PlaySE
    push       {lr}
    push       {r4,r7}
    ldr        r0,[r0,#0x0]
    cmp        r0,#0x0
    blt        LAB_08001ec2
    bl         Sound_PlaySE
LAB_08001ec2:
    pop        {r4,r7}
    pop        {pc}


_ts BgTask_AddTaskList
    push       {r5,lr}
    add        r5,r0,#0x0
LAB_08001ecc:
    ldr        r0,[r5,#0x0]
    cmp        r0,#0x0
    blt        LAB_08001eda
    bl         BgTask_AddNew
    add        r5,#0x4
    b          LAB_08001ecc
LAB_08001eda:
    pop        {r5,pc}


_ts Tint_Add
    mov        r7,r10
    ldr        r7,[r7,#0x64]
    mov        r6,#0xc
    mul        r3,r6
    add        r7,r7,r3
    mov        r3,#0x0
    tst        r1,r1
    beq        LAB_08001ef6
    strb       r0,[r7,#0x1]
    str        r1,[r7,#0x4]
    strb       r2,[r7,#0x2]
    mov        r3,#0x1
    str        r4,[r7,#0x8]
LAB_08001ef6:
    strb       r3,[r7,#0x0]
    mov        pc,lr


_ts Tint_Free
    mov        r7,r10
    ldr        r7,[r7,#0x64]
    mov        r1,#0xc
    mul        r0,r1
    add        r7,r7,r0
    mov        r0,#0x0
    strb       r0,[r7,#0x0]
    mov        pc,lr


_ts InitTint
    push       {lr}
    mov        r0,r10
    ldr        r0,[r0,#0x64]
    ldr        r1,DAT_08001f1c
    bl         memset0_32
    pop        {pc}

    .align 2, 0

DAT_08001f1c:
    .word 0xD8


_ts Tint_IsAnyActive
    mov        r7,r10
    ldr        r7,[r7,#0x64]
LAB_08001f24:
    ldrb       r0,[r7,#0x0]
    tst        r0,r0
    bne        LAB_08001f32
    add        r7,#0xc
    cmp        r7,#0xd8
    blt        LAB_08001f24
    mov        r0,#0x0
LAB_08001f32:
    mov        pc,lr


_ts Tint_UpdateAll
    push       {r5,lr}
    ldr        r0,PTR_gBgPaletteBuffer0_08001f94
    ldr        r1,PTR_gBgPalette0_08001f98
    mov        r2,#0x20
    lsl        r2,r2,#0x4
    bl         memcpy_32
    ldr        r0,PTR_gObjPaletteBuffer0_08001f9c
    ldr        r1,PTR_gObjPalette0_08001fa0
    mov        r2,#0x20
    lsl        r2,r2,#0x4
    bl         memcpy_32
    mov        r5,r10
    ldr        r5,[r5,#0x64]
LAB_08001f52:
    ldrb       r0,[r5,#0x0]
    tst        r0,r0
    beq        LAB_08001f7e
    ldr        r0,[r5,#0x4]
    ldrb       r2,[r5,#0x1]
    ldrb       r6,[r5,#0x2]
    ldr        r7,[r5,#0x8]
    cmp        r7,#0x5
    bge        LAB_08001f74
    ldr        r6,PTR_DAT_08001f8c
    add        r7,r7,r6
    ldrb       r1,[r7,#0x0]
    ldrb       r6,[r7,#0x1]
    sub        r6,r6,r1
    ldr        r7,PTR_gObjPalette0_08001fa0
    lsl        r1,r1,#0x5
    add        r7,r7,r1
LAB_08001f74:
    lsl        r6,r6,#0x5
    sub        r6,#0x2
    ldr        r3,PTR_Tint_ApplyToPalette_08001f90
    mov        lr,pc
    bx         r3
LAB_08001f7e:
    add        r5,#0xc
    mov        r6,r10
    ldr        r6,[r6,#0x64]
    add        r6,#0xd8
    cmp        r5,r6
    blt        LAB_08001f52
    pop        {r5,pc}

    .align 2, 0

PTR_DAT_08001f8c:
    .word 0x200ea60

PTR_Tint_ApplyToPalette_08001f90:
    .word Tint_ApplyToPalette_far

PTR_gBgPaletteBuffer0_08001f94:
    .word gBgPaletteBuffer0

PTR_gBgPalette0_08001f98:
    .word gBgPalette0

PTR_gObjPaletteBuffer0_08001f9c:
    .word gObjPaletteBuffer0

PTR_gObjPalette0_08001fa0:
    .word gObjPalette0
