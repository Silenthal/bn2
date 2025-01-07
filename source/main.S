#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

    .set Oam_TransferData, 0x3006c74+1
    .set Sound_Init, 0x8000540+1
    .set Dma_TransferListClear, 0x8000A20+1
    .set Dma_TransferListStartAll, 0x8000A64+1
    .set memset0_32, 0x8000AFC+1
    .set IncrementGameTimer, 0x8000D20+1
    .set Rng_Init, 0x8001478+1
    .set Video_Init, 0x80014C0+1
    .set Video_BlitScreens, 0x80014FC+1
    .set Video_ApplySettings, 0x800158C+1
    .set Video_InitPaletteColor0, 0x8001690+1
    .set Video_InitBlendSettings, 0x80016A4+1
    .set Video_QueueBgPalTransfer, 0x80016B4+1
    .set BgUpdate_Init, 0x80018A4+1
    .set BgUpdate_CallPostLoopFunction, 0x80018B8+1
    .set BgUpdate_CallPreLoopFunction, 0x80018C4+1
    .set InitBgTask, 0x8001A5C+1
    .set BgTask_Update, 0x8001AB0+1
    .set InitTint, 0x8001F0C+1
    .set Tint_UpdateAll, 0x8001F34+1
    .set Oam_Init, 0x8001FA4+1
    .set Sprite_TransferPalettes, 0x8001FFC+1
    .set SpriteTilesetDetail_Init, 0x8002624+1
    .set InitWorld_LoadGame, 0x8003C70+1
    .set InitWorld_NewGame, 0x8003CDC+1
    .set FUN_08003e08, 0x8003E08+1
    .set Fade_Apply, 0x8004964+1
    .set InitFadeSettings, 0x8004A4C+1
    .set Fade_IsFadeActive, 0x8004A54+1
    .set FUN_080063f2, 0x80063F2+1
    .set InitMainMenu, 0x801C108+1
    .set MainMenu_Main, 0x801C118+1
    .set Oam_InitTransferData, 0x801C9A8+1
    .set Oam_InitAffineData, 0x801CB0C+1
    .set Text_Init, 0x8020AC4+1
    .set FUN_08020c10, 0x8020C10+1
    .set FUN_08023848, 0x8023848+1
    .set Scene_UnloadAndResetStepCounter, 0x802425C+1
    .set Scene_UnloadIfMarked, 0x802427C+1
    .set FUN_080244a0, 0x80244A0+1
    .set InitMainMenu_Opt1, 0x8024A34+1
    .set FUN_08024a54, 0x8024A54+1
    .set FUN_08026c88, 0x8026C88+1
    .set FUN_08026dfc, 0x8026DFC+1
    .set FUN_0802cf48, 0x802CF48+1
    .set FUN_08030dbc, 0x8030DBC+1
    .set FUN_08030f18, 0x8030F18+1
    .set FUN_08033850, 0x8033850+1
    .set Sio_SetReady, 0x80E62C8+1


_ts AgbMain
    bl         Main_Init
    mov        r7,r10
    ldr        r0,[r7,#0x0]
    mov        r1,#0x14
    strb       r1,[r0,#0x0]
    bl         InitMainMenu_Opt1
LAB_080002a4:
    bl         Main_SoftResetCheck
    bl         Main_WaitFrames
    bl         BgUpdate_CallPreLoopFunction
    bl         Video_ApplySettings
    ldr        r0,PTR_Oam_TransferData_08000310
    mov        lr,pc
    bx         r0
    bl         Dma_TransferListStartAll
    bl         Tint_UpdateAll
    bl         Video_QueueBgPalTransfer
    bl         Sprite_TransferPalettes
    bl         SpriteTilesetDetail_Init
    bl         Video_BlitScreens
    bl         Main_ReadInput
    mov        r0,r10
    ldr        r0,[r0,#0x50]
    ldrh       r1,[r0,#0x0]
    add        r1,#0x1
    strh       r1,[r0,#0x0]
    bl         IncrementGameTimer
    ldr        r0,PTR_PTR_ARRAY_08000314
    mov        r7,r10
    ldr        r1,[r7,#0x0]
    ldrb       r1,[r1,#0x0]
    ldr        r0,[r0,r1]
    mov        lr,pc
    bx         r0
    bl         FUN_080063f2
    tst        r0,r0
    beq        LAB_080002fe
    bl         Fade_Apply
LAB_080002fe:
    bl         FUN_08026c88
    bl         FUN_08020c10
    bl         BgUpdate_CallPostLoopFunction
    bl         BgTask_Update
    b          LAB_080002a4

PTR_Oam_TransferData_08000310:
    .word Oam_TransferData

PTR_PTR_ARRAY_08000314:
    .word PTR_ARRAY_08000318

PTR_ARRAY_08000318:
    .word MainMenu_Main
    .word FUN_08003e08
    .word 0x8005821
    .word FUN_08023848
    .word FUN_080244a0
    .word FUN_08024a54
    .word 0x80253D1
    .word 0x802F831
    .word FUN_08030dbc
    .word FUN_0802cf48
    .word 0x802F0E5
    .word FUN_08030f18
    .word FUN_08033850


_ts Main_WaitFrames
    push       {lr}
LAB_0800034e:
    ldr        r0,PTR_gVBlankFrameCounter_0800052c
    ldr        r2,[r0,#0x0]
    ldr        r1,PTR_gFrameWaitValue_08000530
    ldr        r1,[r1,#0x0]
    cmp        r2,r1
    blt        LAB_0800034e
    mov        r1,#0x0
    str        r1,[r0,#0x0]
    pop        {pc}


_ts Main_ReadInput
    mov        r7,r10
    ldr        r0,[r7,#0x4]
    ldrb       r7,[r0,#0x13]
    add        r7,#0x1
    cmp        r7,#0x3
    ble        LAB_0800036e
    mov        r7,#0x0
LAB_0800036e:
    strb       r7,[r0,#0x13]
    ldr        r4,PTR_REG_KEYINPUT_08000534
    ldrh       r4,[r4,#0x0]
    mvn        r4,r4
    ldrh       r5,[r0,#0x0]
    strh       r5,[r0,#0x6]
    strh       r4,[r0,#0x0]
    add        r6,r4,#0x0
    and        r6,r5
    mov        r1,#0x8
    mov        r3,#0x0
LAB_08000384:
    mov        r2,#0x1
    lsl        r2,r3
    and        r2,r6
    beq        LAB_080003a4
    ldrb       r2,[r0,r1]
    cmp        r2,#0x10
    bge        LAB_080003aa
    add        r2,#0x1
    strb       r2,[r0,r1]
    cmp        r2,#0x1
    beq        LAB_080003b2
LAB_0800039a:
    mov        r2,#0x1
    lsl        r2,r3
    mvn        r2,r2
    and        r6,r2
    b          LAB_080003b2
LAB_080003a4:
    mov        r2,#0x0
    strb       r2,[r0,r1]
    b          LAB_080003b2
LAB_080003aa:
    ldrb       r7,[r0,#0x13]
    cmp        r7,#0x0
    beq        LAB_080003b2
    b          LAB_0800039a
LAB_080003b2:
    add        r3,#0x1
    add        r1,#0x1
    cmp        r1,#0x12
    blt        LAB_08000384
    strh       r6,[r0,#0x4]
    mvn        r5,r5
    and        r4,r5
    strh       r4,[r0,#0x2]
    mov        pc,lr


_ts Main_SoftResetCheck
    push       {lr}
    bl         Fade_IsFadeActive
    beq        LAB_08000400
    mov        r7,r10
    ldr        r0,[r7,#0x4]
    ldrh       r2,[r0,#0x2]
    ldrh       r0,[r0,#0x0]
    ldr        r1,[r7,#0x0]
    add        r1,#0x4
    ldrb       r4,[r1,#0x0]
    sub        r4,#0x1
    cmp        r4,#0x0
    bgt        LAB_080003fe
    mov        r4,#0x0
    mov        r3,#0xf
    and        r0,r3
    cmp        r0,r3
    bne        LAB_080003fe
    and        r2,r3
    tst        r2,r2
    beq        LAB_080003fe
    push       {r1}
    bl         InitializeInterruptVectors
    bl         Main_InitFromReset
    pop        {r1}
    mov        r4,#0xa
LAB_080003fe:
    strb       r4,[r1,#0x0]
LAB_08000400:
    pop        {pc}
    .byte 0x00
    .byte 0x00
    .word PTR_DAT_08000408

PTR_DAT_08000408:
    .word 0x200d570


_ts Main_Init
    mov        r0,#0x1
    b          LAB_08000412


_ts Main_InitFromReset
    mov        r0,#0x0
LAB_08000412:
    push       {lr}
    ldr        r7,PTR_MainState_08000498
    mov        r10,r7
    mov        r1,#0x40
    tst        r0,r0
    beq        LAB_08000420
    mov        r1,#0xc0
LAB_08000420:
    mov        r7,r10
    ldr        r0,[r7,#0x10]
    strh       r1,[r0,#0x0]
    bl         Video_InitPaletteColor0
    bl         Video_ApplySettings
    bl         Sound_Init
    bl         BgUpdate_Init
    bl         Video_Init
    bl         Oam_Init
    bl         InitMainMenu
    bl         Oam_InitTransferData
    bl         Dma_TransferListClear
    bl         Rng_Init
    bl         Text_Init
    bl         Oam_InitAffineData
    bl         InitWorld_LoadGame
    bl         InitWorld_NewGame
    bl         Scene_UnloadAndResetStepCounter
    bl         Scene_UnloadIfMarked
    bl         InitBgTask
    bl         InitTint
    bl         Video_InitBlendSettings
    bl         InitFadeSettings
    bl         FUN_08026dfc
    mov        r0,r10
    push       {r0}
    bl         Sio_SetReady
    pop        {r0}
    mov        r10,r0
    ldr        r0,PTR_gFrameWaitValue_08000538
    mov        r1,#0x1
    strh       r1,[r0,#0x0]
    mov        r7,r10
    ldr        r0,[r7,#0x0]
    mov        r1,#0x8
    bl         memset0_32
    pop        {pc}

PTR_MainState_08000498:
    .word MainState

MainState:
    .word gManager
    .word gInput
    .word gWorld
    .word gBattle
    .word gDisplaySettings
    .word gCamera
    .word gFadeSettings
    .word 0x20067d0
    .word 0x2009bf0
    .word 0x2006350
    .word gScene
    .word 0x2006880
    .word 0x2006140
    .word gMainMenu
    .word gWindowSettings
    .word gBlendSettings
    .word 0x2009a88
    .word gBgDataManager
    .word gTextHandler
    .word 0x2007f20
    .word gFrameCounter
    .word 0x200a180
    .word gBgAnimationTaskList
    .word gScreens
    .word 0x2009a70
    .word gTintList
    .word gTextUi
    .word 0x200d580
    .word 0
    .word 0x2007ea0
    .word gGameStats
    .word 0x2009490


_ts Main_WaitForVBlank
    push       {lr}
    ldr        r0,PTR_REG_DISPSTAT_0800053c
    mov        r2,#0x1
LAB_08000522:
    ldrh       r1,[r0,#0x0]
    tst        r1,r2
    beq        LAB_08000522
    pop        {pc}

    .align 2, 0


PTR_gVBlankFrameCounter_0800052c:
    .word gVBlankFrameCounter

PTR_gFrameWaitValue_08000530:
    .word gFrameWaitValue

PTR_REG_KEYINPUT_08000534:
    .word REG_KEYINPUT

PTR_gFrameWaitValue_08000538:
    .word gFrameWaitValue

PTR_REG_DISPSTAT_0800053c:
    .word REG_DISPSTAT
