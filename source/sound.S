#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

    .set Flag_Get, 0x801BF40+1
    .set m4aSoundVSync, 0x80E6AE0+1
    .set FUN_080e711c, 0x80E711C+1
    .set m4aSoundInit, 0x80E713C+1
    .set m4aSoundMain, 0x80E71B4+1
    .set m4aSongNumStart, 0x80E71C0+1
    .set m4aSongNumStop, 0x80E728C+1
    .set m4aMPlayAllStop, 0x80E72F4+1
    .set m4aSoundMode, 0x80E76D8+1
    .set IRQ_VCount, 0x3006444+1
@ Start: 0x540


_ts Sound_Init
    push       {lr}
    bl         m4aSoundInit
    ldr        r0,DAT_08000568
    bl         m4aSoundMode
    ldr        r0,PTR_interruptVector_08000570
    ldr        r1,PTR_IRQ_VCount_08000574
    str        r1,[r0,#0x8]
    ldr        r0,PTR_REG_DISPSTAT_0800056c
    ldrh       r1,[r0,#0x0]
    mov        r2,#0xff
    and        r1,r2
    mov        r2,#0x20
    orr        r1,r2
    mov        r2,#0x50
    lsl        r2,r2,#0x8
    orr        r1,r2
    strh       r1,[r0,#0x0]
    pop        {pc}

DAT_08000568:
    .word 0x93040D

PTR_REG_DISPSTAT_0800056c:
    .word REG_DISPSTAT

PTR_interruptVector_08000570:
    .word interruptVector

PTR_IRQ_VCount_08000574:
    .word IRQ_VCount


_ts Sound_Main
    push       {lr}
    bl         m4aSoundMain
    pop        {pc}
    .word 0x2003a80
    .word DAT_08000588

DAT_08000588:
    .byte 0x1C
    .byte 0x12
    .asciz "%D"

    .align 2, 0



_ts Sound_VSync
    push       {lr}
    bl         m4aSoundVSync
    pop        {pc}


_ts Sound_PlaySongImmediate
    push       {r1,r2,r3,r4,r5,r6,r7,lr}
LAB_0800059a:
    mov        r1,r10
    push       {r1}
    bl         m4aSongNumStart
    pop        {r1}
    mov        r10,r1
LAB_080005a6:
    pop        {r1,r2,r3,r4,r5,r6,r7,pc}


_ts Sound_ChangeSong
    push       {r1,r2,r3,r4,r5,r6,r7,lr}
    mov        r7,r10
    ldr        r7,[r7,#0x8]
    ldrb       r1,[r7,#0x18]
    cmp        r0,r1
    beq        LAB_080005a6
    strb       r0,[r7,#0x18]
    b          LAB_0800059a


_ts Sound_PlaySong
    push       {r1,r2,r3,r4,r5,r6,r7,lr}
    mov        r7,r10
    ldr        r7,[r7,#0x8]
    strb       r0,[r7,#0x18]
    b          LAB_0800059a


_nt Song_FadeOut
    push       {r5,lr}
    ldr        r7,DAT_080005d8
    lsl        r0,r0,#0x2
    ldr        r0,[r7,r0]
    mov        r2,r10
    push       {r2}
    bl         FUN_080e711c
    pop        {r2}
    mov        r10,r2
    pop        {r5,pc}

DAT_080005d8:
    .word 0x80005DC

musicPlayerList:
    .word musicPlayerInfo_00
    .word musicPlayerInfo_01
    .word musicPlayerInfo_02
    .word musicPlayerInfo_03
    .word musicPlayerInfo_04
    .word musicPlayerInfo_05
    .word musicPlayerInfo_06
    .word musicPlayerInfo_07
    .word musicPlayerInfo_08
    .word musicPlayerInfo_09
    .word musicPlayerInfo_0A
    .word musicPlayerInfo_0B
    .word musicPlayerInfo_0C
    .word musicPlayerInfo_0D
    .word musicPlayerInfo_0E
    .word musicPlayerInfo_0F
    .word musicPlayerInfo_10
    .word musicPlayerInfo_11
    .word musicPlayerInfo_12
    .word musicPlayerInfo_13
    .word musicPlayerInfo_14
    .word musicPlayerInfo_15
    .word musicPlayerInfo_16
    .word musicPlayerInfo_17
    .word musicPlayerInfo_18
    .word musicPlayerInfo_19
    .word musicPlayerInfo_1A
    .word musicPlayerInfo_1B
    .word musicPlayerInfo_1C
    .word musicPlayerInfo_1D
    .word musicPlayerInfo_1E
    .word musicPlayerInfo_1F


_ts Sound_StopAllMusic
    push       {lr}
    mov        r1,r10
    push       {r1}
    bl         m4aMPlayAllStop
    pop        {r1}
    mov        r10,r1
    mov        r7,r10
    ldr        r7,[r7,#0x8]
    mov        r0,#0xff
    strb       r0,[r7,#0x18]
    pop        {pc}


_ts Sound_AreaSongChange
    push       {lr}
    mov        r7,r10
    ldr        r7,[r7,#0x8]
    ldrb       r0,[r7,#0x4]
    cmp        r0,#0x80
    bpl        LAB_080006b4
    mov        r0,#0x0
    mov        r1,#0x4
    bl         Flag_Get
    beq        LAB_0800069a
    ldrb       r0,[r7,#0x6]
    cmp        r0,#0x46
    bls        LAB_0800069a
    ldrb       r0,[r7,#0x4]
    cmp        r0,#0x7
    beq        LAB_0800069a
    cmp        r0,#0x8
    bne        LAB_080006ce
LAB_0800069a:
    mov        r4,r10
    ldr        r4,[r4,#0x78]
    ldrb       r1,[r4,#0xc]
    tst        r1,r1
    beq        LAB_080006ce
    ldr        r6,PTR_PTR_SongId_080009b8
    ldrb       r0,[r7,#0x6]
    lsr        r0,r0,#0x4
    lsl        r0,r0,#0x2
    ldr        r6,[r6,r0]
    ldrb       r0,[r4,#0xe]
    ldrb       r0,[r6,r0]
    b          LAB_080006e2
LAB_080006b4:
    mov        r4,r10
    ldr        r4,[r4,#0x78]
    ldrb       r1,[r4,#0xd]
    tst        r1,r1
    beq        LAB_080006ce
    ldr        r6,PTR_PTR_SongId_080009bc
    ldrb       r0,[r7,#0x6]
    lsr        r0,r0,#0x4
    lsl        r0,r0,#0x2
    ldr        r6,[r6,r0]
    ldrb       r0,[r4,#0xf]
    ldrb       r0,[r6,r0]
    b          LAB_080006e2
LAB_080006ce:
    ldr        r6,DAT_08000734
    ldrb       r0,[r7,#0x4]
    cmp        r0,#0x80
    bmi        LAB_080006da
    ldr        r6,DAT_08000738
    sub        r0,#0x80
LAB_080006da:
    lsl        r0,r0,#0x2
    ldr        r6,[r6,r0]
    ldrb       r0,[r7,#0x5]
    ldrb       r0,[r6,r0]
LAB_080006e2:
    cmp        r0,#0xff
    beq        LAB_080006ec
    bl         Sound_ChangeSong
    b          LAB_080006ec
LAB_080006ec:
    pop        {pc}


_nt FUN_080006ee
    push       {lr}
    mov        r7,r10
    ldr        r7,[r7,#0x8]
    ldrb       r0,[r7,#0x6]
    cmp        r0,#0x50
    bmi        LAB_08000708
    mov        r4,r10
    ldr        r4,[r4,#0x78]
    mov        r0,#0x0
    strb       r0,[r4,#0xc]
    strb       r0,[r4,#0xd]
    strb       r0,[r4,#0xe]
    strb       r0,[r4,#0xf]
LAB_08000708:
    pop        {pc}


_nt FUN_0800070a
    push       {r4,r7,lr}
    push       {r7}
    mov        r7,r10
    ldr        r7,[r7,#0x8]
    ldrb       r0,[r7,#0x4]
    cmp        r0,#0x80
    bmi        LAB_08000724
    push       {r4}
    mov        r4,r10
    ldr        r4,[r4,#0x78]
    strb       r0,[r4,#0xc]
    strb       r1,[r4,#0xe]
    b          LAB_0800072e
LAB_08000724:
    push       {r4}
    mov        r4,r10
    ldr        r4,[r4,#0x78]
    strb       r0,[r4,#0xd]
    strb       r1,[r4,#0xf]
LAB_0800072e:
    pop        {r4}
    pop        {r7}
    pop        {r4,r7,pc}

DAT_08000734:
    .word 0x800073C

DAT_08000738:
    .word 0x8000760

SongGroup_Offline:
    .word SongGroup_ACDC
    .word SongGroup_Marine
    .word SongGroup_Okuden
    .word SongGroup_DenAir
    .word SongGroup_NetAir
    .word SongGroup_Netopia
    .word SongGroup_Plane
    .word SongGroup_Kotobuki
    .word SongGroup_Apartment

SongGroup_Online:
    .word SongGroup_GasComp
    .word SongGroup_BombComp
    .word SongGroup_MotherComp
    .word SongGroup_CastleComp
    .word SongGroup_AirComp
    .word SongGroup_ApartComp
    .word SongGroup_BombComp
    .word SongGroup_BombComp
    .word SongGroup_HP
    .word SongId_ARRAY_080008b4
    .word SongId_ARRAY_080008c4
    .word SongId_ARRAY_080008d4
    .word SongGroup_Other1
    .word SongGroup_Other2
    .word SongGroup_BombComp
    .word SongGroup_BombComp
    .word SongGroup_DenArea
    .word SongGroup_KotoArea
    .word SongGroup_YumArea
    .word SongGroup_NetNet
    .word SongGroup_Undernet

SongGroup_ACDC:
    .byte T_Home_Town
    .byte T_Home_Town
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_School
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room
    .byte T_In_The_Room

SongGroup_Marine:
    .byte T_Marine_Harbour
    .byte T_Marine_Harbour
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center
    .byte T_Official_Center

SongGroup_Okuden:
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley

SongGroup_DenAir:
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey

SongGroup_NetAir:
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey
    .byte T_Going_On_A_Journey

SongGroup_Netopia:
    .byte T_Netopia_Castle
    .byte T_Foreign_Town
    .byte T_Alley
    .byte T_Foreign_Town
    .byte T_Foreign_Town
    .byte T_Netopia_Castle
    .byte T_Netopia_Castle
    .byte T_Dungeon
    .byte T_Dungeon
    .byte T_Dungeon
    .byte T_Dungeon
    .byte T_Dungeon
    .byte T_Dungeon
    .byte T_Dungeon
    .byte T_Netopia_Castle
    .byte T_Dungeon

SongGroup_Plane:
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel
    .byte T_Sky_Travel

SongGroup_Kotobuki:
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination

SongGroup_Apartment:
    .byte T_NoSong
    .byte T_NoSong
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination
    .byte T_Determination

SongGroup_GasComp:
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field
    .byte T_Smoky_Field

SongGroup_BombComp:
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit
    .byte T_Time_Limit

SongGroup_MotherComp:
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission
    .byte T_A_Serious_Mission

SongGroup_CastleComp:
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle
    .byte T_Fear_In_The_Casstle

SongGroup_AirComp:
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane
    .byte T_Magnetic_Airplane

SongGroup_ApartComp:
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back
    .byte T_You_Cant_Go_Back

SongGroup_HP:
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World

SongId_ARRAY_080008b4:
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley

SongId_ARRAY_080008c4:
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley

SongId_ARRAY_080008d4:
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley

SongGroup_Other1:
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World

SongGroup_Other2:
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World

SongGroup_DenArea:
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World

SongGroup_KotoArea:
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Fearful
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World

SongGroup_YumArea:
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Vicinity_Of_Sorrow
    .byte T_Vicinity_Of_Sorrow
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley
    .byte T_Okuden_Valley

SongGroup_NetNet:
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World
    .byte T_Internet_World

SongGroup_Undernet:
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful
    .byte T_And_You_Will_Know_The_Truth
    .byte T_And_You_Will_Know_The_Truth
    .byte T_And_You_Will_Know_The_Truth
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful
    .byte T_Fearful

PTR_SongId_08000954:
    .word SongId_0800097c
    .word SongId_08000980
    .word SongId_08000984
    .word SongId_08000988
    .word 0x800098D

PTR_SongId_08000968:
    .word SongId_08000992
    .word SongId_08000996
    .word SongId_0800099a
    .word SongId_0800099e
    .word SongId_080009a2

SongId_0800097c:
    .byte T_NoSong
    .byte T_Suspicious_Mood
    .byte T_Incident_Occurrence
    .byte T_Secret_Maneuver

SongId_08000980:
    .byte T_NoSong
    .byte T_Suspicious_Mood
    .byte T_Incident_Occurrence
    .byte T_Secret_Maneuver

SongId_08000984:
    .byte T_NoSong
    .byte T_Suspicious_Mood
    .byte T_Incident_Occurrence
    .byte T_Secret_Maneuver

SongId_08000988:
    .byte T_NoSong
    .byte T_Suspicious_Mood
    .byte T_Incident_Occurrence
    .byte T_Secret_Maneuver
    .byte T_Home_Town

SongId_0800098d:
    .byte T_NoSong
    .byte T_Suspicious_Mood
    .byte T_Incident_Occurrence
    .byte T_Secret_Maneuver
    .byte T_Proof_Of_Courage

SongId_08000992:
    .byte T_NoSong
    .byte T_Incident_Occurrence
    .byte T_Pressure
    .byte T_Okuden_Valley

SongId_08000996:
    .byte T_NoSong
    .byte T_Incident_Occurrence
    .byte T_Pressure
    .byte T_Okuden_Valley

SongId_0800099a:
    .byte T_NoSong
    .byte T_Incident_Occurrence
    .byte T_Pressure
    .byte T_Okuden_Valley

SongId_0800099e:
    .byte T_NoSong
    .byte T_Incident_Occurrence
    .byte T_Pressure
    .byte T_Okuden_Valley

SongId_080009a2:
    .byte T_NoSong
    .byte T_Incident_Occurrence
    .byte T_Pressure
    .byte T_Okuden_Valley

    .align 2, 0



_ts Sound_StopSong
    push       {r1,r2,r3,r4,r5,r6,r7,lr}
    mov        r1,r10
    push       {r1}
    bl         m4aSongNumStop
    pop        {r1}
    mov        r10,r1
    pop        {r1,r2,r3,r4,r5,r6,r7,pc}

PTR_PTR_SongId_080009b8:
    .word PTR_SongId_08000954

PTR_PTR_SongId_080009bc:
    .word PTR_SongId_08000968
