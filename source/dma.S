#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

@ Start: 0x9C0


@@ Sets the settings for a particular DMA channel.
@@ In:
@@ r0: startAddress - The address to read data from.
@@ r1: endAddress - The address to write data to.
@@ r2: wordCount - The amount of 16-bit or 32-bit words to write.
@@ r3: channel - The channel to write to.
@@ r4: control - The control settings of the channel.
_ts Dma_SetDirect
    lsl        r3,r3,#0x2
    ldr        r5,PTR_listDmaChannel
    ldr        r5,[r5,r3]
    mov        r3,#0x8
    ldr        r7,PTR_dmaEnableMask
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

listDmaChannel:
    .word REG_DMA0
    .word REG_DMA1
    .word REG_DMA2
    .word REG_DMA3


@@ Waits for any active DMA transfers to end.
@@ In:
@@ r0: flags - The DMA registers to check. Bit 1 set checks DMA1, Bit 2 DMA2, and so on.
_ts Dma_WaitForEnd
    ldr        r3,PTR_REG_DMA0
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
    ldr        r2,PTR_dmaEnableMask
    and        r1,r2
    bne        LAB_080009ee
    mov        pc,lr


@@ Clears the list of pending DMA transfers.
_ts Dma_TransferListClear
    ldr        r0,PTR_dmaListSz_0
    mov        r1,#0x0
    str        r1,[r0,#0x0]
    mov        pc,lr


@@ Adds params for channel 3 DMA transfer to the transfer queue.
@@ In:
@@ r0: startAddress - The address to read data from.
@@ r1: endAddress - The address to write data to.
@@ r2: wordCount - The amount of words being transferred.
_ts Dma_TransferListAdd
    mov        r3,#0x0
    push       {r5}
    add        r7,r3,#0x0
    ldr        r3,PTR_dmaListSz_1
    ldr        r4,[r3,#0x0]
    cmp        r4,#0x60
    bge        LAB_08000a52
    add        r5,r4,#0x0
    add        r4,#0x1
    str        r4,[r3,#0x0]
    ldr        r4,PTR_gDmaParamList_0
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
    .word 0x84000000
    .word 0x85000000


@@ Performs all queued DMA channel 3 transfers.
_ts Dma_TransferListStartAll
    push       {lr}
    ldr        r0,PTR_dmaListSz_2
    ldr        r1,[r0,#0x0]
    ldr        r2,PTR_gDmaParamList_1
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


@@ Adds a list of DMA transfers to process.
@@ In:
@@ r0: transferList - A list of DmaTransferDetail objects, each with a start/end address and word count.
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

    .align 2, 0

PTR_listDmaChannel:     .word listDmaChannel
PTR_dmaEnableMask:      .word DMA_ENABLE
PTR_REG_DMA0:           .word REG_DMA0
PTR_dmaListSz_0:        .word gDmaParamListSize
PTR_dmaListSz_1:        .word gDmaParamListSize
PTR_gDmaParamList_0:    .word gDmaParamList
PTR_dmaListSz_2:        .word gDmaParamListSize
PTR_gDmaParamList_1:    .word gDmaParamList
