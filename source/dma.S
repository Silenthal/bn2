#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

@ Start: 0x9C0


_ts Dma_SetDirect
    lsl        r3,r3,#0x2
    ldr        r5,PTR_PTR_REG_DMA0_08000ab4
    ldr        r5,[r5,r3]
    mov        r3,#0x8
    ldr        r7,DAT_08000ab8
LAB_080009ca:
    ldr        r6,[r5,r3]
    and        r6,r7
    bne        LAB_080009ca
    str        r0,[r5,#0x0]
    str        r1,[r5,#0x4]
    orr        r4,r2
    str        r4,[r5,#0x8]
    mov        pc,lr

    .align 2, 0


PTR_REG_DMA0_080009dc:
    .word REG_DMA0
    .word REG_DMA1
    .word REG_DMA2
    .word REG_DMA3


_ts Dma_WaitForEnd
    ldr        r3,PTR_REG_DMA0_08000abc
LAB_080009ee:
    mov        r1,#0x0
    mov        r4,#0x1
    tst        r0,r4
    beq        LAB_080009fa
    ldr        r2,[r3,#0x8]
    orr        r1,r2
LAB_080009fa:
    mov        r4,#0x2
    tst        r0,r4
    beq        LAB_08000a04
    ldr        r2,[r3,#0x14]
    orr        r1,r2
LAB_08000a04:
    mov        r4,#0x4
    tst        r0,r4
    beq        LAB_08000a0e
    ldr        r2,[r3,#0x20]
    orr        r1,r2
LAB_08000a0e:
    mov        r4,#0x8
    tst        r0,r4
    beq        LAB_08000a18
    ldr        r2,[r3,#0x2c]
    orr        r1,r2
LAB_08000a18:
    ldr        r2,DAT_08000ab8
    and        r1,r2
    bne        LAB_080009ee
    mov        pc,lr


_ts Dma_TransferListClear
    ldr        r0,PTR_eDmaTransferQueueSize_08000ac0
    mov        r1,#0x0
    str        r1,[r0,#0x0]
    mov        pc,lr


_ts Dma_TransferListAdd
    mov        r3,#0x0
    push       {r5}
    add        r7,r3,#0x0
    ldr        r3,PTR_eDmaTransferQueueSize_08000ac4
    ldr        r4,[r3,#0x0]
    cmp        r4,#0x60
    bge        LAB_08000a52
    add        r5,r4,#0x0
    add        r4,#0x1
    str        r4,[r3,#0x0]
    ldr        r4,PTR_eDmaParamList_08000ac8
    mov        r6,#0x10
    mul        r5,r6
    add        r4,r4,r5
    str        r0,[r4,#0x0]
    str        r1,[r4,#0x4]
    str        r2,[r4,#0x8]
    ldr        r3,PTR_DmaCntFlag_ARRAY_08000a58
    lsl        r7,r7,#0x2
    ldr        r3,[r3,r7]
    str        r3,[r4,#0xc]
LAB_08000a52:
    pop        {r5}
    mov        pc,lr

    .align 2, 0


PTR_DmaCntFlag_ARRAY_08000a58:
    .word DmaCntFlag_ARRAY_08000a5c

DmaCntFlag_ARRAY_08000a5c:
    .byte 0x00, 0x00, 0x00, 0x84
    .byte 0x00, 0x00, 0x00, 0x85


_ts Dma_TransferListStartAll
    push       {lr}
    ldr        r0,PTR_eDmaTransferQueueSize_08000acc
    ldr        r1,[r0,#0x0]
    ldr        r2,PTR_eDmaParamList_08000ad0
LAB_08000a6c:
    cmp        r1,#0x0
    beq        LAB_08000a92
    mov        r8,r1
    mov        r9,r2
    ldr        r4,[r2,#0xc]
    ldr        r0,[r2,#0x0]
    ldr        r1,[r2,#0x4]
    ldr        r2,[r2,#0x8]
    mov        r3,#0x3
    bl         Dma_SetDirect
    mov        r0,#0x8
    bl         Dma_WaitForEnd
    mov        r1,r8
    mov        r2,r9
    sub        r1,#0x1
    add        r2,#0x10
    b          LAB_08000a6c
LAB_08000a92:
    bl         Dma_TransferListClear
    pop        {pc}


_ts Dma_TransferListAddList
    push       {r5,lr}
    add        r7,r0,#0x0
LAB_08000a9c:
    ldr        r0,[r7,#0x0]
    tst        r0,r0
    beq        LAB_08000ab2
    ldr        r1,[r7,#0x4]
    ldr        r2,[r7,#0x8]
    push       {r7}
    bl         Dma_TransferListAdd
    pop        {r7}
    add        r7,#0xc
    b          LAB_08000a9c
LAB_08000ab2:
    pop        {r5,pc}

PTR_PTR_REG_DMA0_08000ab4:
    .word PTR_REG_DMA0_080009dc

DAT_08000ab8:
    .word 0x80000000

PTR_REG_DMA0_08000abc:
    .word REG_DMA0

PTR_eDmaTransferQueueSize_08000ac0:
    .word eDmaTransferQueueSize

PTR_eDmaTransferQueueSize_08000ac4:
    .word eDmaTransferQueueSize

PTR_eDmaParamList_08000ac8:
    .word eDmaParamList

PTR_eDmaTransferQueueSize_08000acc:
    .word eDmaTransferQueueSize

PTR_eDmaParamList_08000ad0:
    .word eDmaParamList
