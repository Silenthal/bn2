#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

    .set CpuFastSet, 0x80E8630+1
    .set tilesetKeyboardNumberChars, 0x8695DF0
    .set paletteKeyboardNumberChars, 0x869E5F0
@ Start: 0x14C0


@@ Initializes all screens, and loads text and palettes for debug printing.
_ts Video_Init
    push       {lr}
    ldr        r0,PTR_gFillValue_0
    ldr        r1,PTR_BG_VRAM_SCREEN0
    ldr        r2,PTR_screenTotalSize
    mov        r3,#0x3
    ldr        r4,PTR_dmaFlags_0
    bl         Dma_SetDirect
    mov        r0,#0x8
    bl         Dma_WaitForEnd
    bl         Video_ClearScreen
    ldr        r0,PTR_tilesetDebugText
    ldr        r1,PTR_BG_VRAM_BASE3
    ldr        r2,PTR_size200
    mov        r3,#0x3
    ldr        r4,PTR_dmaFlags_1
    bl         Dma_SetDirect
    mov        r0,#0x8
    bl         Dma_WaitForEnd
    ldr        r0,PTR_paletteDebugText
    ldr        r1,PTR_gBgPaletteBufferF
    mov        r2,#0x20
    bl         memcpy_32
    pop        {pc}


@@ Flushes screen buffer contents to the screen.
_ts Video_BlitScreens
    push       {lr}
    LoadMain screens, r0, r0
    ldr        r1,PTR_BG_VRAM_SCREEN0
    ldr        r2,PTR_screenTotalSize
    bl         CpuFastSet
    ldr        r0,PTR_gFillValue_1
    ldr        r1,PTR_tilemapBlankTile
    str        r1,[r0,#0x0]
    LoadMain screens, r1, r1
    ldr        r2,PTR_controlScreenCopy
    bl         CpuFastSet
    ldr        r0,PTR_gFillValue_2
    mov        r1,#0x0
    str        r1,[r0,#0x0]
    pop        {pc}


@@ Sets the BG control for all backgrounds.
@@ In:
@@ r0: index - Index to indicate which group of controls to set.
_ts Video_SetBgControl
    ldr        r1,PTR_listBgControl
    lsl        r0,r0,#0x3
    add        r1,r1,r0
    LoadMain display, r2, r7
    add        r2,#0x4
    ldr        r0,[r1,#0x0]
    str        r0,[r2,#0x0]
    ldr        r0,[r1,#0x4]
    str        r0,[r2,#0x4]
    mov        pc,lr

    .align 2, 0

listBgControl:
    @ 0
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=3, base=0, use256=1, screen=29, wrap=1
    bgcnt priority=3, base=1, use256=1, screen=30, wrap=1
    bgcnt priority=3, base=2, use256=1, screen=31, wrap=1
    @ 1
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=0, base=0, use256=0, screen=0, wrap=0
    bgcnt priority=0, base=0, use256=0, screen=0, wrap=0
    bgcnt priority=0, base=0, use256=0, screen=0, wrap=0
    @ 2
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=1, base=0, use256=0, screen=29, wrap=1
    bgcnt priority=0, base=0, use256=0, screen=0, wrap=0
    bgcnt priority=0, base=0, use256=0, screen=0, wrap=0
    @ 3
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=3, base=0, use256=0, screen=29, wrap=1
    bgcnt priority=2, base=0, use256=0, screen=30, wrap=1
    bgcnt priority=1, base=1, use256=0, screen=31, wrap=1
    @ 4
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=3, base=0, use256=0, screen=29, wrap=1
    bgcnt priority=2, base=0, use256=0, screen=30, wrap=1
    bgcnt priority=1, base=1, use256=0, screen=31, wrap=1
    @ 5
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=3, base=2, use256=1, screen=29, wrap=1
    bgcnt priority=2, base=2, use256=1, screen=30, wrap=1
    bgcnt priority=1, base=0, use256=1, screen=31, wrap=1
    @ 6
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=3, base=0, use256=0, screen=29, wrap=1
    bgcnt priority=2, base=0, use256=0, screen=30, wrap=1
    bgcnt priority=1, base=1, use256=0, screen=31, wrap=1
    @ 7
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=3, base=0, use256=0, screen=29, wrap=1
    bgcnt priority=2, base=0, use256=0, screen=30, wrap=1
    bgcnt priority=1, base=2, use256=0, screen=31, wrap=1
    @ 8
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=3, base=0, use256=0, screen=29, wrap=1
    bgcnt priority=2, base=0, use256=0, screen=30, wrap=1
    bgcnt priority=1, base=2, use256=0, screen=31, wrap=1
    @ 9
    bgcnt priority=0, base=2, use256=0, screen=28, wrap=1
    bgcnt priority=3, base=0, use256=0, screen=29, wrap=1
    bgcnt priority=2, base=0, use256=0, screen=30, wrap=1
    bgcnt priority=1, base=1, use256=1, screen=31, wrap=1


@@ Apply all background and window settings.
_ts Video_ApplySettings
    push       {lr}
    LoadMain display, r5, r7
    ldr        r1,PTR_REG_DISPCNT
    ldrh       r2,[r5,#0x0]
    strh       r2,[r1,#0x0]
    ldr        r1,PTR_REG_MOSAIC
    ldrh       r2,[r5,#0x2]
    strh       r2,[r1,#0x0]
    ldr        r1,PTR_REG_BG0CNT
    ldr        r2,[r5,#0x4]
    str        r2,[r1,#0x0]
    ldr        r1,PTR_REG_BG2CNT
    ldr        r2,[r5,#0x8]
    str        r2,[r1,#0x0]
    ldr        r1,PTR_REG_BG0HOFS
    ldr        r2,[r5,#0xc]
    str        r2,[r1,#0x0]
    ldr        r1,PTR_REG_BG1HOFS
    ldr        r2,[r5,#0x10]
    str        r2,[r1,#0x0]
    ldr        r1,PTR_REG_BG2HOFS
    ldr        r2,[r5,#0x14]
    str        r2,[r1,#0x0]
    ldr        r1,PTR_REG_BG3HOFS
    ldr        r2,[r5,#0x18]
    str        r2,[r1,#0x0]
    ldr        r5,[r7,#0x38]
    ldr        r1,PTR_REG_WIN0H
    ldr        r2,[r5,#0x0]
    str        r2,[r1,#0x0]
    ldr        r1,PTR_REG_WIN0V
    ldr        r2,[r5,#0x4]
    str        r2,[r1,#0x0]
    ldr        r1,PTR_REG_WININ
    ldr        r2,[r5,#0x8]
    str        r2,[r1,#0x0]
    ldr        r5,[r7,#0x3c]
    ldr        r2,PTR_listBlendTargetHandler
    ldrb       r1,[r5,#0x0]
    lsr        r1,r1,#0x6
    lsl        r1,r1,#0x2
    ldr        r2,[r2,r1]
    mov        lr,pc
    bx         r2
    ldr        r1,PTR_REG_BLDCNT
    ldrh       r2,[r5,#0x0]
    strh       r2,[r1,#0x0]
    ldr        r1,PTR_REG_BLDALPHA
    ldrh       r2,[r5,#0x2]
    strh       r2,[r1,#0x0]
    ldr        r1,PTR_REG_BLDY
    ldrh       r2,[r5,#0x4]
    strh       r2,[r1,#0x0]
    pop        {pc}

    .align 2, 0

listBlendTargetHandler:
    .word handlerNone
    .word handlerAlphaBlend
    .word handlerBrightnessIncrease
    .word handlerBrightnessDecrease


_ts handlerNone
    push       {lr}
    @ EVB = 1 - EVA
    ldrb       r1,[r5,#0x2]
    sub        r1,#0x10
    neg        r1,r1
    strb       r1,[r5,#0x3]
    @ Set 0 for all 1st targets
    mov        r1,#0x0
    strb       r1,[r5,#0x0]
    @ Set 1 for all 2nd targets
    mov        r1,#0x3f
    strb       r1,[r5,#0x1]
    @ EVY = 0
    mov        r1,#0x0
    strb       r1,[r5,#0x4]
    pop        {pc}


_ts handlerAlphaBlend
    push       {lr}
    @ EVB = special val
    ldrh       r1,[r5,#0x6]
    lsr        r1,r1,#0x4
    strb       r1,[r5,#0x3]
    @ EVA = 1 - EVB
    sub        r1,#0x10
    neg        r1,r1
    strb       r1,[r5,#0x2]
    @ EVY = 0
    mov        r1,#0x0
    strb       r1,[r5,#0x4]
    @ Set 1 for all 2nd targets except BG0
    mov        r1,#0x3e
    strb       r1,[r5,#0x1]
    pop        {pc}


_ts handlerBrightnessIncrease
    push       {lr}
    @ EVA = 0
    mov        r1,#0x0
    strb       r1,[r5,#0x2]
    @ EVB = 0
    mov        r1,#0x0
    strb       r1,[r5,#0x3]
    @ Set all 2nd targets to 0
    mov        r1,#0x0
    strb       r1,[r5,#0x1]
    @ EVY = special val
    ldrh       r1,[r5,#0x6]
    lsr        r1,r1,#0x4
    strb       r1,[r5,#0x4]
    pop        {pc}


_ts handlerBrightnessDecrease
    push       {lr}
    @ EVA = 0
    mov        r1,#0x0
    strb       r1,[r5,#0x2]
    @ EVB = 0
    mov        r1,#0x0
    strb       r1,[r5,#0x3]
    @ Set all 2nd targets to 0
    mov        r1,#0x0
    strb       r1,[r5,#0x1]
    @ EVY = special val
    ldrh       r1,[r5,#0x6]
    lsr        r1,r1,#0x4
    strb       r1,[r5,#0x4]
    pop        {pc}


@@ Initializes the first tile on all backgrounds to the clear color. 
_ts Video_ClearAllTile0Maps
    push       {r5,lr}
    ldr        r0,PTR_BG_VRAM_BASE0
    mov        r1,#0x40
    bl         memset0_32
    ldr        r0,PTR_BG_VRAM_BASE1
    mov        r1,#0x40
    bl         memset0_32
    ldr        r0,PTR_BG_VRAM_BASE2
    mov        r1,#0x40
    bl         memset0_32
    ldr        r0,PTR_BG_VRAM_BASE3
    mov        r1,#0x20
    bl         memset0_32
    pop        {r5,pc}


@@ Initializes the palette color that is used for clearing the screen.
_ts Video_InitPaletteColor0
    push       {r5,lr}
    ldr        r0,PTR_gBgPaletteBuffer0
    mov        r1,#0x2
    bl         memset0_16
    ldr        r0,PTR_PAL_BG
    mov        r1,#0x2
    bl         memset0_16
    pop        {r5,pc}


@@ Initializes the blend settings.
_ts Video_InitBlendSettings
    push       {lr}
    mov        r7,r10
    ldr        r0,[r7,#0x3c]
    mov        r1,#0x8
    bl         memset0_32
    pop        {pc}


@@ Transfers all background palettes to VRAM.
_ts Video_QueueBgPalTransfer
    push       {lr}
    ldr        r0,PTR_gBgPalette0
    ldr        r1,PTR_PAL_BG
    mov        r2,#0x20
    lsl        r2,r2,#0x4
    bl         memcpy_32
    pop        {pc}


@@ Clears the screen.
_ts Video_ClearScreen
    push       {r5,lr}
    ldr        r0,PTR_gFillValue_3
    mov        r1,r10
    ldr        r1,[r1,#0x5c]
    ldr        r2,PTR_screenTotalSize
    mov        r3,#0x3
    ldr        r4,PTR_dmaFlags_0
    bl         Dma_SetDirect
    mov        r0,#0x8
    bl         Dma_WaitForEnd
    pop        {r5,pc}

    .align 2, 0

PTR_gFillValue_0:               .word gFillValue
PTR_BG_VRAM_SCREEN0:            .word BG_VRAM_SCREEN0
PTR_screenTotalSize:            .word 0x2000 >> 2
PTR_dmaFlags_0:                 .word DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED
PTR_tilesetDebugText:           .word tilesetKeyboardNumberChars
PTR_BG_VRAM_BASE3:              .word BG_VRAM_BASE3
PTR_size200:                    .word 0x200
PTR_dmaFlags_1:                 .word DMA_32BIT | DMA_ENABLE
PTR_paletteDebugText:           .word paletteKeyboardNumberChars
PTR_gBgPaletteBufferF:          .word gBgPaletteBufferF
PTR_gFillValue_1:               .word gFillValue
PTR_tilemapBlankTile:
    tilemap_entry 0x200, 0, 0
    tilemap_entry 0x200, 0, 0
PTR_controlScreenCopy:          .word 0x1000200
PTR_gFillValue_2:               .word gFillValue
PTR_listBgControl:              .word listBgControl
PTR_REG_DISPCNT:                .word REG_DISPCNT
PTR_REG_MOSAIC:                 .word REG_MOSAIC
PTR_REG_BG0CNT:                 .word REG_BG0CNT
PTR_REG_BG2CNT:                 .word REG_BG2CNT
PTR_REG_BG0HOFS:                .word REG_BG0HOFS
PTR_REG_BG1HOFS:                .word REG_BG1HOFS
PTR_REG_BG2HOFS:                .word REG_BG2HOFS
PTR_REG_BG3HOFS:                .word REG_BG3HOFS
PTR_REG_WIN0H:                  .word REG_WIN0H
PTR_REG_WIN0V:                  .word REG_WIN0V
PTR_REG_WININ:                  .word REG_WININ
PTR_listBlendTargetHandler:     .word listBlendTargetHandler
PTR_REG_BLDCNT:                 .word REG_BLDCNT
PTR_REG_BLDALPHA:               .word REG_BLDALPHA
PTR_REG_BLDY:                   .word REG_BLDY
PTR_BG_VRAM_BASE0:              .word BG_VRAM_BASE0
PTR_BG_VRAM_BASE1:              .word BG_VRAM_BASE1
PTR_BG_VRAM_BASE2:              .word BG_VRAM_BASE2
PTR_gBgPaletteBuffer0:          .word gBgPaletteBuffer0
PTR_PAL_BG:                     .word PAL_BG
PTR_gBgPalette0:                .word gBgPalette0
PTR_gFillValue_3:               .word gFillValue
