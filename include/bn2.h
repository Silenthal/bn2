#ifndef BN2_H
#define BN2_H

typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned int    uint;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;

typedef struct _interruptHandler _interruptHandler, *P_interruptHandler;

struct _interruptHandler {
    void (*vblank)(void);
    void (*hblank)(void);
    void (*vcount)(void);
    void (*timer0)(void);
    void (*timer1)(void);
    void (*timer2)(void);
    void (*timer3)(void);
    void (*serial)(void);
    void (*dma0)(void);
    void (*dma1)(void);
    void (*dma2)(void);
    void (*dma3)(void);
    void (*keypad)(void);
    void (*extirq)(void);
};

typedef struct Actor Actor, *PActor;

typedef struct EntityHeader EntityHeader, *PEntityHeader;

typedef struct FamilyDetail FamilyDetail, *PFamilyDetail;

typedef struct FunctionState FunctionState, *PFunctionState;

typedef struct CellPosition CellPosition, *PCellPosition;

typedef enum ElementId {
    EL_None=0,
    EL_Elec=1,
    EL_Fire=2,
    EL_Water=3,
    EL_Wood=4
} ElementId;

typedef struct MapOffsetStruct MapOffsetStruct, *PMapOffsetStruct;

typedef struct PositionXYZ PositionXYZ, *PPositionXYZ;

typedef union ActorAttribUnion ActorAttribUnion, *PActorAttribUnion;

typedef struct BattleSpawnAnimation BattleSpawnAnimation, *PBattleSpawnAnimation;

typedef struct Sprite Sprite, *PSprite;

typedef enum GeneralEntityFlag {
    GF_None=0,
    GF_Active=1,
    GF_CanLoadSprite=2,
    GF_IgnoreTimeStop=4,
    GF_SpriteNotLoaded=8
} GeneralEntityFlag;

typedef enum EntityTag {
    EF_None=0,
    ET_PlayerLocation=128,
    ET_Attack=130,
    ET_Effect=131,
    ET_Actor=145,
    ET_NPC=148
} EntityTag;

typedef enum FuncState {
    FS_0=0,
    FS_1=4,
    FS_2=8,
    FS_3=12,
    FS_4=16,
    FS_5=20,
    FS_6=24,
    FS_7=28,
    FS_8=32,
    FS_9=36,
    FS_10=40,
    FS_11=44,
    FS_12=48,
    FS_13=52,
    FS_14=56,
    FS_15=60,
    FS_16=64,
    FS_17=68,
    FS_18=72,
    FS_19=76,
    FS_20=80,
    FS_21=84,
    FS_22=88,
    FS_23=92,
    FS_24=96,
    FS_25=100,
    FS_26=104,
    FS_27=108
} FuncState;

typedef struct ActorAttributes_Default ActorAttributes_Default, *PActorAttributes_Default;

typedef enum SpriteFlag {
    SF_NoMiniAnimation=1,
    SF_TilesetLoaded=2,
    SF_ZClip=4,
    SF_NoZClip=8,
    SF_MultipleParts=16,
    SF_TilesNotInVram=32
} SpriteFlag;

typedef struct SpriteFrame SpriteFrame, *PSpriteFrame;

typedef struct SpriteSubFrame SpriteSubFrame, *PSpriteSubFrame;

typedef struct SpriteTilesetHeader SpriteTilesetHeader, *PSpriteTilesetHeader;

typedef union EntityParam EntityParam, *PEntityParam;

typedef struct Tile Tile, *PTile;

struct SpriteSubFrame {
    byte objectListIndex;
    byte delay;
    byte flag;
};

struct EntityHeader {
    enum GeneralEntityFlag entityFlags;
    byte routineType;
    enum EntityTag tag;
    byte listIndex;
};

struct FamilyDetail {
    byte family;
    byte b1;
    byte b2;
    byte b3;
};

struct Sprite {
    byte indexFrame;
    byte frameDelay;
    enum SpriteFlag frameFlags;
    enum SpriteFlag spriteFlags;
    byte srcPalIndex;
    byte palIndexSubFrame;
    byte _indexSubFrame;
    byte indexOamList;
    short dstTileOffset;
    short spriteNum;
    short screenX;
    byte portraitScreenY;
    byte screenY;
    byte xyattributes_0;
    byte xyattributes_1;
    byte xyattributes_2;
    byte xyAttributes_3;
    byte tileAttributes_0;
    byte tileAttributes_1;
    short _pad;
    byte *spriteStart;
    struct SpriteFrame *curFrame;
    struct SpriteSubFrame *curSubFrame;
    struct SpriteTilesetHeader *curTilesetHeader;
    int objectDrawBitset;
    uint objectExcludeFlags;
};

struct FunctionState {
    enum FuncState s0;
    enum FuncState s1;
    enum FuncState s2;
    enum FuncState s3;
};

struct PositionXYZ {
    int x;
    int y;
    int z;
};

union EntityParam {
    struct Actor *actor;
    int iVal;
};

struct ActorAttributes_Default {
    union EntityParam obj_5C;
    union EntityParam obj_60;
    byte b_64;
    byte b_65;
    byte b_66;
    byte b_67;
    union EntityParam obj_68;
    union EntityParam obj_6C;
    union EntityParam obj_70;
    struct Actor *obj_74;
    union EntityParam obj_78;
    union EntityParam obj_7C;
};

union ActorAttribUnion {
    struct ActorAttributes_Default def;
};

struct Tile {
    byte field0_0x0[32];
};

struct CellPosition {
    byte x;
    byte y;
};

struct SpriteFrame {
    int tilesetOffset;
    int palettes;
    int subFrames;
    int objectLists;
    byte delay;
    byte _pad0;
    byte flags;
    byte _pad1;
};

struct MapOffsetStruct {
    struct PositionXYZ curr;
    struct PositionXYZ last;
};

struct BattleSpawnAnimation {
    byte m_state0;
    byte _pad0;
    short m_timer0;
    short s1;
    short s2;
};

struct Actor {
    struct EntityHeader header;
    struct FamilyDetail family;
    struct FunctionState state;
    byte m_bx0c_familyRelated;
    byte m_bx0d;
    byte m_bx0e;
    bool field6_0xf;
    byte m_direction;
    byte m_bx11;
    byte m_indexNumber;
    byte m_enemyId;
    byte frameIndexCurr;
    byte frameIndexLast;
    byte owner;
    byte isInvulnerable;
    struct CellPosition cPos;
    enum ElementId element;
    byte delayCounter1;
    ushort delayCounter2;
    short routineCounter;
    ushort hpCurrent;
    ushort hpMax;
    ushort damage;
    ushort field23_0x26;
    struct MapOffsetStruct pos;
    int _pad40;
    struct PositionXYZ delta;
    struct PositionXYZ initial;
    union ActorAttribUnion attrib;
    struct BattleSpawnAnimation m_appearState;
    int field30_0x88;
    int field31_0x8c;
    struct Sprite m_sprite;
};

struct SpriteTilesetHeader {
    int m_tilesetSize;
    struct Tile m_tiles;
};

typedef enum AreaId {
    Area_0=0
} AreaId;

typedef struct AreaStruct AreaStruct, *PAreaStruct;

struct AreaStruct {
    enum AreaId area;
    byte subArea;
};

typedef union AreaUnion AreaUnion, *PAreaUnion;

typedef enum MapId {
    Map_1=0
} MapId;

union AreaUnion {
    enum MapId mapId;
    struct AreaStruct areaId;
};

typedef struct Attack Attack, *PAttack;

struct Attack {
    struct EntityHeader header;
    struct FamilyDetail family;
    struct FunctionState state;
    byte m_bx0c_familyRelated;
    byte targetX;
    byte targetY;
    byte field6_0xf;
    byte angle;
    byte b11;
    byte b12;
    byte b13;
    byte frameIndexCurr;
    byte frameIndexLast;
    byte owner;
    byte m_bx17;
    struct CellPosition cPos;
    byte element;
    byte delayCounter1;
    short delayCounter2;
    short initialCounterValue;
    ushort hpCurrent;
    ushort hpMax;
    ushort damage;
    ushort field23_0x26;
    struct MapOffsetStruct pos;
    int field25_0x40;
    struct PositionXYZ diff;
    union EntityParam obj_50;
    union EntityParam obj_54;
    union EntityParam obj_58;
    union EntityParam obj_5C;
    union EntityParam obj_60;
    union EntityParam obj_64;
    union EntityParam obj_68;
    union EntityParam obj_6C;
    union EntityParam obj_70;
    union EntityParam obj_74;
    union EntityParam obj_78;
    union EntityParam obj_7C;
    struct Sprite m_sprite;
};

typedef struct BackgroundDataManager BackgroundDataManager, *PBackgroundDataManager;

typedef struct TilemapEntry TilemapEntry, *PTilemapEntry;

typedef struct BGArchive BGArchive, *PBGArchive;

typedef struct BGTilemapArchive BGTilemapArchive, *PBGTilemapArchive;

typedef struct BGPaletteArchive BGPaletteArchive, *PBGPaletteArchive;

typedef struct BGTilesetArchive BGTilesetArchive, *PBGTilesetArchive;

typedef struct Color Color, *PColor;

typedef struct BGTilesetHeader BGTilesetHeader, *PBGTilesetHeader;

struct BGArchive {
    struct BGTilesetArchive *tilesetData;
    struct BGPaletteArchive *paletteData;
    struct BGTilemapArchive *tilemapData;
};

struct TilemapEntry {
    short tileIndex:10;
    short flipFlags:2;
    short paletteBank:4;
};

struct BGTilemapArchive {
    byte mapSizeX;
    byte mapSizeY;
    int offsetBg1;
    int offsetBg2;
    int offsetBg3;
    struct TilemapEntry tilemapData[1];
};

struct Color {
    byte R:5;
    byte G:5;
    byte B:5;
    byte fill:1;
};

struct BackgroundDataManager {
    byte mapGridSizeX;
    byte mapGridSizeY;
    undefined1 field2_0x2;
    undefined1 field3_0x3;
    short playerX;
    short playerY;
    struct BGArchive *archivePack;
    struct BGTilemapArchive *tilemapArchive;
    struct BGPaletteArchive *paletteArchive;
    struct BGTilesetArchive *tilesetArchive;
    void (*funcSingleCopy)(struct TilemapEntry, struct TilemapEntry, struct TilemapEntry, int, int);
    void *funcFullCopy;
    void (*funcSpecificCopy)(uint, uint);
};

struct BGPaletteArchive {
    int size;
    struct Color data[1];
};

struct BGTilesetHeader {
    int m_tilesetWordCount;
    int m_offsetLzData;
    int m_offsetVram;
};

struct BGTilesetArchive {
    struct BGTilesetHeader vramData[3];
};

typedef enum BackgroundId {
    BG_0man=0
} BackgroundId;

typedef struct Battle Battle, *PBattle;

typedef enum BattleEntryState {
    BES_Battle=0,
    BES_NonBattle=1,
    BES_Spawn=8
} BattleEntryState;

typedef enum BattleState {
    BS_EnemySpawned=1,
    BS_InBattle=2,
    BS_BattleStarted=4
} BattleState;

typedef struct EnemySpawn EnemySpawn, *PEnemySpawn;

typedef enum EnemyId {
    ED_Megaman=0,
    ED_Invalid=255
} EnemyId;

struct EnemySpawn {
    enum EnemyId id;
    byte x;
    byte y;
};

struct Battle {
    struct FunctionState state;
    byte initialActorCount[2];
    byte initialActorsSpawned[2];
    enum BattleEntryState battleEntryState;
    enum BattleState battleState;
    byte m_bx0a;
    byte m_maxEnemyCount;
    byte m_bx0c;
    byte randomCellSeed;
    bool isGaugeFull;
    enum BackgroundId backgroundId;
    byte m_customScreenChipCount;
    byte m_customScreenSelectedChipCount;
    byte customGaugeSpeed;
    bool isInputLocked;
    byte startPressState;
    byte multiDeleteBufferTimer;
    byte multiDeleteTempCounter;
    byte multiDeleteCount;
    bool isScreenDimChipActive;
    byte srcBattleHandCount;
    byte sioOtherMpId;
    byte sioMultiplayerId;
    byte bx1c;
    byte bx1d;
    byte bx1e_MPState;
    bool isBattleActive;
    ushort m_possibleBattleTime;
    ushort curPlayerCount;
    ushort curEnemyCount;
    int field30_0x28;
    ushort field31_0x2c;
    ushort generalCounter;
    short sx30_counter;
    short field34_0x32;
    int field35_0x34;
    int field36_0x38;
    ushort field37_0x3c;
    ushort m_customGaugeMeter;
    struct Actor *actorListPlayer[2];
    int field40_0x48;
    byte enemyPriorityQueue[8];
    struct Actor *actorListEnemy[4];
    byte enemyIdList[4];
    uint battleFlag_buffer;
    uint battleFlag;
    uint bf02;
    struct EnemySpawn *enemyList;
    byte srcBattleHandIndexList[6];
    byte m_srcBattleHandCodeList[6];
};

typedef struct BattleChip BattleChip, *PBattleChip;

typedef enum ChipId {
    CD_Buster=0
} ChipId;

typedef enum ChipCode {
    CC_A=0,
    CC_B=1,
    CC_C=2,
    CC_D=3,
    CC_E=4,
    CC_F=5,
    CC_G=6,
    CC_H=7,
    CC_I=8,
    CC_J=9,
    CC_K=10,
    CC_L=11,
    CC_M=12,
    CC_N=13,
    CC_O=14,
    CC_P=15,
    CC_Q=16,
    CC_R=17,
    CC_S=18,
    CC_T=19,
    CC_U=20,
    CC_V=21,
    CC_W=22,
    CC_X=23,
    CC_Y=24,
    CC_Z=25
} ChipCode;

struct BattleChip {
    enum ChipId chipId;
    enum ChipCode chipCode;
};

typedef enum BattleResultState {
    BRS_Winner=0,
    BRS_Loser=1,
    BRS_2=2,
    BRS_MPError=3
} BattleResultState;

typedef enum BattleType {
    BattleType_0_Regular=0,
    BattleType_1_Tutorial1=1,
    BattleType_2_Tutorial2=2,
    BattleType_3_RegularNoResult=3,
    BattleType_4_Tutorial3=4,
    BattleType_5_Boss=5,
    BattleType_6_FinalBoss=6,
    BattleType_7=7,
    BattleType_8_NetworkReal=8,
    BattleType_9_NetworkTest=9
} BattleType;

typedef struct BgAnimationTask BgAnimationTask, *PBgAnimationTask;

typedef struct BgAnimParam BgAnimParam, *PBgAnimParam;

struct BgAnimParam {
    void *address;
    int type;
};

struct BgAnimationTask {
    byte enabled;
    byte _bgIndex;
    ushort updateTimer;
    struct BgAnimParam *dataArgStart;
    struct BgAnimParam *dataArgCurr;
    void *param2_endAddr;
    void *param3_vramDest;
    byte funcIndex;
    byte bgIndex;
    byte tileCount;
    byte tileBufferIndex;
};

typedef enum BgAnimType {
    BGT_Direct=0,
    BGT_Tileset=1,
    BGT_Tilemap=2,
    BGT_Tint=3,
    BGT_Song=4
} BgAnimType;

typedef struct BgControl BgControl, *PBgControl;

struct BgControl {
    int bgPriority:2;
    int charBaseBlock:2;
    bool isMosaic:1;
    bool is256Color:1;
    int screenBaseBlock:5;
    bool isWraparound:1;
    int screenSize:2;
};

typedef struct BgDataArg BgDataArg, *PBgDataArg;

struct BgDataArg {
    int data;
    int waitFrames;
};

typedef enum BGMoveControlType {
    BMT_Offline=0,
    BMT_Online=1,
    BMT_Battle=2
} BGMoveControlType;

typedef struct BgTask BgTask, *PBgTask;

struct BgTask {
    void *dataSrc;
    void *vramDest;
    enum BgAnimType dataTransferType;
    byte bgIndex;
    byte tileCount;
    byte tileBufferIndex;
    struct BgAnimParam argList[1];
};

typedef struct BlendSettings BlendSettings, *PBlendSettings;

struct BlendSettings {
    byte m_bldCnt_Target1;
    byte _bldCnt_Target2;
    byte m_bldAlpha_EVA;
    byte _bldAlpha_EVB;
    byte _bldY_EVA;
    byte _pad0;
    ushort m_blendControl;
};

typedef struct Camera Camera, *PCamera;

struct Camera {
    short field0_0x0;
    enum BGMoveControlType bgMovementControl;
    byte isActive;
    short cameraX; /* +right, center is middle of map */
    short cameraY; /* +down, center is middle of map */
    short lastCameraX;
    short lastCameraY;
    short shakeCounter;
    short shakeStrength;
    struct PositionXYZ *playerRealPos;
    int xLowerBound;
    int xUpperBound;
    int yUpperBound;
    int yLowerBound;
    int zUpperBound;
    int zLowerBound;
    struct PositionXYZ posMapNext;
    struct PositionXYZ posMap; /* x +up-right, y +down-right */
    int field18_0x44;
};

typedef struct CameraShakeArg CameraShakeArg, *PCameraShakeArg;

struct CameraShakeArg {
    uint mask;
    uint adjust;
};

typedef struct CellPosition4 CellPosition4, *PCellPosition4;

struct CellPosition4 {
    int x;
    int y;
};

typedef struct CgbChannel CgbChannel, *PCgbChannel;

typedef struct MusicPlayerTrack MusicPlayerTrack, *PMusicPlayerTrack;

typedef enum MptFlag {
    MPT_FLAG_VOLSET=1,
    MPT_FLAG_VOLCHG=3,
    MPT_FLAG_PITSET=4,
    MPT_FLAG_PITCHG=12,
    MPT_FLAG_START=64,
    MPT_FLAG_EXIST=128
} MptFlag;

typedef struct SoundChannel SoundChannel, *PSoundChannel;

typedef struct ToneData ToneData, *PToneData;

typedef struct WaveData WaveData, *PWaveData;

typedef enum InstrumentType {
    Sample=0,
    PsgSquare1=1,
    PsgSquare2=2,
    PsgWave=3,
    PsgNoise=4,
    SampleNonResampled=8,
    KeySplit=64,
    KeySplit2=128
} InstrumentType;

struct SoundChannel {
    byte status;
    byte type;
    byte rightVolume;
    byte leftVolume;
    byte attack;
    byte delay;
    byte sustain;
    byte release;
    byte key;
    byte envelopeVolume;
    byte envelopeVolumeRight;
    byte envelopeVolumeLeft;
    byte pseudoEchoVolume;
    byte pseudoEchoLength;
    byte dummy1;
    byte dummy2;
    byte gateTime;
    byte midiKey;
    byte velocity;
    byte prpriority;
    byte rhythmPan;
    byte dummy3[3];
    uint count;
    uint fw;
    uint frequency;
    struct WaveData *wav;
    byte *currentPointer;
    struct MusicPlayerTrack *track;
    struct SoundChannel *prevChannelPointer;
    struct SoundChannel *nextChannelPointer;
    uint dummy4;
    ushort xpi;
    ushort xpc;
};

struct ToneData {
    enum InstrumentType type;
    byte key;
    byte length;
    byte pan_sweep;
    struct WaveData *wav;
    byte attack;
    byte decay;
    byte sustain;
    byte release;
};

struct WaveData {
    ushort type;
    ushort status;
    uint freq;
    uint loopStart;
    uint size;
    byte data[1];
};

struct MusicPlayerTrack {
    enum MptFlag flags;
    byte wait;
    byte patternLevel;
    byte repN;
    byte gateTime;
    byte key;
    byte velocity;
    byte runningStatus;
    byte keyM;
    byte pitM;
    byte keyShift;
    byte keyShiftX;
    byte tune;
    byte pitX;
    byte bend;
    byte bendRange;
    byte volMR;
    byte volML;
    byte vol;
    byte volX;
    byte pan;
    byte panX;
    byte modM;
    byte mod;
    byte modT;
    byte lfoSpeed;
    byte lfoSpeedCounter;
    byte lfoDelay;
    byte lfoDelayCounter;
    byte priority;
    byte pseudoEchoVolume;
    byte pseudoEchoLength;
    struct SoundChannel *chan;
    struct ToneData tone;
    byte gap[10];
    short unk_3A;
    int unk_3C;
    byte *cmdPtr;
    byte *patternStack[3];
};

struct CgbChannel {
    byte statusFlags;
    byte type;
    byte rightVolume;
    byte leftVolume;
    byte attack;
    byte decay;
    byte sustain;
    byte release;
    byte key;
    byte envelopeVolume;
    byte envelopeGoal;
    byte envelopeCounter;
    byte pseudoEchoVolume;
    byte pseudoEchoLength;
    byte dummy1;
    byte dummy2;
    byte gateTime;
    byte midiKey;
    byte velocity;
    byte priority;
    byte rhythmPan;
    byte dummy3[3];
    byte dummy5;
    byte sustainGoal;
    byte n4;
    byte pan;
    byte panMask;
    byte modify;
    byte length;
    byte sweep;
    int frequency;
    int *wavePointer;
    int *currentPointer;
    struct MusicPlayerTrack *track;
    void *prevChannelPointer;
    void *nextChannelPointer;
    byte dummy4[4];
    int unkPad;
};

typedef struct ChipTrader ChipTrader, *PChipTrader;

struct ChipTrader {
    enum FuncState state;
    enum FuncState lastState;
    byte b2;
    byte arrowAnimationTimer;
    short exchangeAmount;
    ushort lastPageOffsetInsert;
    ushort curPageOffsetInsert;
    ushort curPageIndexInsert;
    ushort lastPageIndexInsert;
    ushort chipsSelected;
    ushort curPageOffsetSack;
    ushort lastPageOffsetSack;
    ushort curPageIndexSack;
    ushort lastPageIndexSack;
    ushort sackCount;
    byte b24;
    byte b25;
    byte b26;
    byte b27;
    byte b28;
    byte b29;
    struct TilemapEntry chipsInsertedBuffer[8];
    ushort curPageOffsetSort;
    ushort lastPageOffsetSort;
    ushort curPageIndexSort;
    ushort lastPageIndexSort;
    ushort m_b56;
    ushort drawnChipId;
    ushort drawnChipCode;
    byte b62;
    byte b63;
    int field31_0x40;
};

typedef enum DispCnt {
    DISPCNT_MODE0=0,
    DISPCNT_MODE1=1,
    DISPCNT_MODE2=2,
    DISPCNT_MODE3=3,
    DISPCNT_MODE4=4,
    DISPCNT_MODE5=5,
    DISPCNT_FRMSEL=16,
    DISPCNT_HFREE=32,
    DISPCNT_OMAP1D=64,
    DISPCNT_FORCEBLANK=128,
    DISPCNT_BG0=256,
    DISPCNT_BG1=512,
    DISPCNT_BG2=1024,
    DISPCNT_BG3=2048,
    DISPCNT_BGALL=3840,
    DISPCNT_OBJ=4096,
    DISPCNT_WIN0=8192,
    DISPCNT_WIN1=16384,
    DISPCNT_OBJWIN=32768
} DispCnt;

typedef struct DisplaySettings DisplaySettings, *PDisplaySettings;

struct DisplaySettings {
    enum DispCnt dispcnt;
    ushort mosaic;
    struct BgControl bg0Cnt;
    struct BgControl bg1Cnt;
    struct BgControl bg2Cnt;
    struct BgControl bg3Cnt;
    ushort bg0Hofs;
    ushort bg0Vofs;
    ushort bg1Hofs;
    ushort bg1Vofs;
    ushort bg2Hofs;
    ushort bg2Vofs;
    ushort bg3Hofs;
    ushort bg3Vofs;
};

typedef struct DivRes DivRes, *PDivRes;

struct DivRes {
    int quotient;
    int mod;
    int absmod;
};

typedef struct DmaChannel DmaChannel, *PDmaChannel;

typedef enum DmaCntFlag {
    DMA_DEST_DEC=2097152,
    DMA_DEST_FIXED=4194304,
    DMA_SRC_DEC=8388608,
    DMA_SRC_FIXED=16777216,
    DMA_REPEAT=33554432,
    DMA_32BIT=67108864,
    DMA_DREQ_ON=134217728,
    DMA_START_VBLANK=268435456,
    DMA_START_HBLANK=536870912,
    DMA_INTR_ENABLE=1073741824,
    DMA_ENABLE=2147483648
} DmaCntFlag;

struct DmaChannel {
    void *srcAddress;
    void *dstAddress;
    enum DmaCntFlag control;
};

typedef struct DmaTransferDetail DmaTransferDetail, *PDmaTransferDetail;

struct DmaTransferDetail {
    void *startAddress;
    void *endAddress;
    int wordCount;
};

typedef struct DmaTransferParams DmaTransferParams, *PDmaTransferParams;

struct DmaTransferParams {
    void *startAddress;
    void *endAddress;
    uint wordCount;
    enum DmaCntFlag control;
};

typedef struct Effect Effect, *PEffect;

struct Effect {
    struct EntityHeader header;
    struct FamilyDetail family;
    struct FunctionState state;
    byte option0;
    byte option1;
    byte option2;
    byte option3;
    int field7_0x10;
    byte frameIndexCurr;
    byte frameIndexLast;
    byte owner;
    byte bx17;
    struct CellPosition cPos;
    enum ElementId element;
    byte bx1b;
    ushort delayCounter;
    short field16_0x1e;
    int field17_0x20;
    ushort damage;
    ushort field19_0x26;
    struct MapOffsetStruct pos;
    int field21_0x40;
    struct PositionXYZ diff;
    struct PositionXYZ initial;
    union EntityParam obj_5C;
    union EntityParam obj_60;
    union EntityParam obj_64;
    union EntityParam obj_68;
    union EntityParam obj_6C;
    int m_unkX;
    int m_unkY;
    struct Actor *parent;
    int field32_0x7c;
    struct Sprite sprite;
};

typedef struct EntityBounds EntityBounds, *PEntityBounds;

struct EntityBounds {
    short X;
    short Y;
    short Z;
    byte radius;
    byte height;
    uint id;
    uint idMask;
    uint *collisionRef;
};

typedef struct EntityBoundsParams EntityBoundsParams, *PEntityBoundsParams;

struct EntityBoundsParams {
    int x;
    int y;
    int z;
    int bounds;
    int id;
    int mask;
};

typedef struct FadeSettings FadeSettings, *PFadeSettings;

typedef enum FadeType {
    FT_None=0,
    FT_FadeInFromWhite=1,
    FT_FadeOutToWhite=2,
    FT_FadeInFromBlack=3,
    FT_FadeOutToBlack=4,
    FT_FadeInFromBlackExceptSpritesBG0=5,
    FT_DarkenExceptSpritesBG0=6,
    FT_FadeInFromBlackExceptBG0=7,
    FT_FadeOutToBlackExceptBG0=8,
    FT_FadeInFromWhiteExceptBG0=9,
    FT_FadeOutToWhiteExceptBG0=10,
    FT_FadeInFromBlackExceptBG3=11,
    FT_DarkenExceptBG3=12,
    FT_FadeInAlphaBlendBG0=13,
    FT_FadeOutAlphaBlendBG0=14
} FadeType;

struct FadeSettings {
    bool isApplyFadeFunc;
    enum FadeType fadeType;
    byte fadeStep;
    bool isFadeActive;
    bool isFadeStarted;
    byte _pad[3];
};

typedef enum FlipType {
    FT_NoFlip=0,
    FT_FlipH=1,
    FT_FlipV=2,
    FT_FlipHV=3
} FlipType;

typedef struct FrameCounter FrameCounter, *PFrameCounter;

struct FrameCounter {
    ushort counter;
    ushort field1_0x2;
};

typedef struct GameStats GameStats, *PGameStats;

struct GameStats {
    byte sortOrderFolder;
    byte sortDirectionFolder;
    byte sortOrderSack;
    byte sortDirectionSack;
    byte m_b0;
    byte batteryCharge;
    ushort field6_0x6;
    ushort field7_0x8;
    byte field8_0xa;
    byte field9_0xb;
    byte field10_0xc;
    bool hasUsedEscape;
    byte totalAwardedChips;
    byte totalBattles8;
    short totalStepCounter;
    ushort totalBattles16;
    ushort field16_0x14;
    ushort field17_0x16;
    int field18_0x18;
    int field19_0x1c;
    short multiBattleTotal;
    short multiBattleWins;
    int gameTimer;
    int inBattleTimer;
    int checksum;
    int currStepCounter;
    int lastStepCounter;
    byte buildId[14];
};

typedef struct header header, *Pheader;

struct header {
    byte h_nintendo_logo[156]; /* Nintendo Logo */
    char h_game_title[12]; /* Game Title */
    char h_game_code[4]; /* Game Code */
    char h_maker_code[2]; /* Maker Code */
    byte h_fixed_value; /* Fixed Value */
    byte h_main_unit_code; /* Main Unit Code */
    byte h_device_type; /* Device Type */
    byte h_reserved[7]; /* Reserved area */
    byte h_software_vers; /* Software Version */
    byte h_complement_check; /* Complement Check */
    byte h_reserved2[2]; /* Reserved area */
};

typedef struct Input Input, *PInput;

typedef enum KeyInput {
    KEY_NONE=0,
    KEY_A=1,
    KEY_B=2,
    KEY_SELECT=4,
    KEY_START=8,
    KEY_RIGHT=16,
    KEY_LEFT=32,
    KEY_UP=64,
    KEY_DOWN=128,
    KEY_R=256,
    KEY_L=512
} KeyInput;

struct Input {
    enum KeyInput curKeyState;
    enum KeyInput toggleKeyState;
    enum KeyInput heldKeyState;
    enum KeyInput lastKeyState;
    byte framesHeldA;
    byte framesHeldB;
    byte framesHeldSelect;
    byte framesHeldStart;
    byte framesHeldRight;
    byte framesHeldLeft;
    byte framesHeldUp;
    byte framesHeldDown;
    byte framesHeldR;
    byte framesHeldL;
    byte unused;
    byte frameCounter;
};

typedef struct Main Main, *PMain;

typedef struct Manager Manager, *PManager;

typedef struct World World, *PWorld;

typedef struct Scene Scene, *PScene;

typedef struct MainMenu MainMenu, *PMainMenu;

typedef struct WindowSettings WindowSettings, *PWindowSettings;

typedef struct Text Text, *PText;

typedef struct ScreenTilemapContainer ScreenTilemapContainer, *PScreenTilemapContainer;

typedef struct TintList TintList, *PTintList;

typedef struct TextUI TextUI, *PTextUI;

typedef enum ManagerState {
    MS_0=0,
    MS_Battle=8
} ManagerState;

typedef enum StoryFlag {
    FS_00_NEW_GAME=0,
    FS_01_DEX_TALK=1,
    FS_02_TUTORIAL_DONE=2,
    FS_03_ZLICENSE_START=3,
    FS_04_ZLICENSE_END=4,
    FS_05_YAI_START=5,
    FS_06_VENT_CLEAR=6,
    FS_07_DELETE_AIRMAN=7,
    FS_08_BED_AIRMAN=8,
    FS_09_BLICENSE_START=9,
    FS_0A_BLICENSE_END=10,
    FS_0B_CAMP=11,
    FS_0C_CAMP_BEES=12,
    FS_0D_CAMP_BEAR=13,
    FS_0E_CAMP_COOKOUT=14,
    FS_0F_CAMP_SEARCH=15,
    FS_10_DELETE_QUICKMAN=16,
    FS_11_YUMLAND_REJECT=17,
    FS_12_REQUEST_MISSIONS=18,
    FS_13_ALICENSE_START=19,
    FS_14_ALICENSE_END=20,
    FS_15_YUMLAND_SQUARE=21,
    FS_16_DELETE_CUTMAN=22,
    FS_17_POST_CUTMAN=23,
    FS_18_BBS=24,
    FS_19_YUMLAND_TREASURE=25,
    FS_1A_YUMLAND_ESCAPE=26,
    FS_1B_GOOFBALL_ATTACK=27,
    FS_1C_SHADOWMAN_ATTACK=28,
    FS_1D_OFFICIAL_BEAM_CANNON=29,
    FS_1E_PROTOMAN_MEET=30,
    FS_1F_SHADOWMAN_FIGHT=31,
    FS_20_DELETE_SHADOWMAN=32,
    FS_21_AIRPORT=33,
    FS_22_PET_STOLEN=34,
    FS_23_MONEY_STOLEN=35,
    FS_24_NETOPIA=36,
    FS_24_CHIPS_STOLEN=37,
    FS_25_MEGAMAN_ARGUE=38,
    FS_26_PASSPORT_STOLEN=39,
    FS_27_PASSPORT_GET=40,
    FS_28_DELETE_SNAKEMAN=41,
    FS_29_BED=42,
    FS_2A_DUNGEON_CEILING=43,
    FS_2B_DUNGEON_FIRE=44,
    FS_2C_DUNGEON_RAOUL=45,
    FS_30_DELETE_KNIGHTMAN=48,
    FS_31_PLANE=49,
    FS_32_PLANE_FOOD=50,
    FS_33_PLANE_BATHROOM=51,
    FS_34_PLANE_SPIDER=52,
    FS_35_PLANE_SPIDER_CATCH=53,
    FS_36_PLANE_VIRUS=54,
    FS_37_DELETE_MAGNETMAN=55,
    FS_38_INTERNET_ICE=56,
    FS_39_REDCURE=57,
    FS_3A_UNDERNET_DOC=58,
    FS_3B_UNDERNET_3=59,
    FS_3C_NULL_VOID=60,
    FS_3D_DELETE_FREEZEMAN=61,
    FS_40_FINAL_DAY=64,
    FS_41_GOSPEL_HQ=65,
    FS_42_KOTOBUKI_MEETING=66,
    FS_43_RADIATION=67,
    FS_45_KOTOBUKI_APARTMENTS=69,
    FS_46_PENTHOUSE=70,
    FS_47_STORY_FINAL_1=71,
    FS_48_STORY_FINAL_2=72,
    FS_FF_NONE=255
} StoryFlag;

typedef enum SongId {
    T_Theme_Of_Mega_Man_Battle_Network_2=0,
    T_Secret_Maneuver=1,
    T_Home_Town=2,
    T_School=3,
    T_In_The_Room=4,
    T_Okuden_Valley=5,
    T_Marine_Harbour=6,
    T_Official_Center=7,
    T_Going_On_A_Journey=8,
    T_Foreign_Town=9,
    T_Netopia_Castle=10,
    T_Sky_Travel=11,
    T_Determination=12,
    T_Suspicious_Mood=13,
    T_Incident_Occurrence=14,
    T_Vicinity_Of_Sorrow=15,
    T_Proof_Of_Courage=16,
    T_Transmission=17,
    T_Smoky_Field=18,
    T_Time_Limit=19,
    T_A_Serious_Mission=20,
    T_Fear_In_The_Casstle=21,
    T_Magnetic_Airplane=22,
    T_You_Cant_Go_Back=23,
    T_Internet_World=24,
    T_Fearful=25,
    T_And_You_Will_Know_The_Truth=26,
    T_Virus_Busting=27,
    T_Battle_Spirit=28,
    T_Vs_Gospel=29,
    T_Winner=30,
    T_Style_Change=31,
    T_Loser=32,
    T_Game_Over=33,
    T_Pressure=34,
    T_Alley=35,
    T_Dungeon=36,
    T_Peace_Again=37,
    T_NoSong=255
} SongId;

typedef struct PlayerLocation PlayerLocation, *PPlayerLocation;

typedef struct WorldPosition WorldPosition, *PWorldPosition;

typedef union SceneArg SceneArg, *PSceneArg;

typedef struct PlayerAnimation PlayerAnimation, *PPlayerAnimation;

typedef enum TextStateDelayType {
    TSDT_NoDelay=0,
    TSDT_DelayCounter=1,
    TSDT_WaitForButtonPress=2
} TextStateDelayType;

typedef struct TintArgs TintArgs, *PTintArgs;

typedef enum MoveType {
    MT_Standing=0,
    MT_Walking=1,
    MT_Running=2
} MoveType;

typedef enum PlayerLocationKeyFlag {
    PK_Walk=16,
    PK_Run=32,
    PK_Commentary=256,
    PK_JackIn=512
} PlayerLocationKeyFlag;

typedef struct SceneArg_Actor SceneArg_Actor, *PSceneArg_Actor;

typedef struct SceneArg_Animate SceneArg_Animate, *PSceneArg_Animate;

typedef enum TintType {
    TT_Add=0,
    TT_Subtract=4
} TintType;

typedef struct MapEntranceOptions MapEntranceOptions, *PMapEntranceOptions;

typedef struct PlayerAnimateArgs PlayerAnimateArgs, *PPlayerAnimateArgs;

typedef enum PlayerAnimArgState {
    PlayerAnimArgState_Inactive=0,
    PlayerAnimArgState_Active=1,
    PlayerAnimArgState_Complete=2
} PlayerAnimArgState;

typedef struct MapEntrance MapEntrance, *PMapEntrance;

struct MapEntrance {
    enum MapId area;
    byte field1_0x2;
    byte direction;
    struct PositionXYZ pos;
};

struct SceneArg_Animate {
    int waitTimer;
    int filterAnimId;
    struct PlayerAnimateArgs *curArgPtr;
    enum PlayerAnimArgState state;
};

struct PlayerAnimation {
    byte animState;
    byte isTalking;
    byte curMoveIndex;
    byte field3_0x3[5];
    struct PositionXYZ position;
};

struct ScreenTilemapContainer {
    struct TilemapEntry screen0[1024];
    struct TilemapEntry screen1[1024];
    struct TilemapEntry screen2[1024];
    struct TilemapEntry screen3[1024];
};

struct Text {
    bool m_isWriteText;
    byte m_textBlockIndex;
    byte m_textBufferOffset;
    byte m_scriptOptions;
    enum TextStateDelayType m_dialogDelayType;
    byte m_isScriptJump;
    byte m_counter1;
    byte m_portraitPalIndex;
    byte m_nextDelay;
    byte m_commandParseDelay;
    byte m_nextAnimationIndex;
    byte m_currAnimationIndex;
    ushort m_dialogDelayCounter;
    byte m_textCol;
    byte m_textRow;
    byte m_layoutLineOffset;
    byte m_scriptParseDelay;
    byte m_dialogSkipDelay;
    byte m_charShade;
    byte m_b14;
    byte m_b15_optionFlag;
    byte m_b16;
    byte passcodeChoice;
    enum KeyInput m_curKeyState;
    enum KeyInput m_heldKeyState;
    enum KeyInput m_toggleKeyState;
    byte m_dialogArrowAnimCycle;
    byte m_arrowAnimFrame;
    byte *m_commandTextPointer;
    ushort *m_textBlockPointer;
    byte *m_layoutTextPointer;
    struct TilemapEntry *m_dialogLayout;
    uint m_itemIdList[4];
    void *m_textPointerAfterKeyPrint;
    void *m_otherTextPointerAfterKeyPrint;
    byte m_possibleBcdBuffer[12];
    byte m_tempPlayerDirection;
    byte b19;
    byte b20;
    byte b21;
    ushort m_textBufIndex;
    ushort m_otherTempTextBufIndex;
    struct Sprite m_portrait;
};

struct SceneArg_Actor {
    struct MapEntranceOptions *entranceOptions;
    struct Scene *m_px14;
    void *m_px18;
    struct Actor *m_px1c_actor;
};

union SceneArg {
    struct SceneArg_Actor actorArg;
    struct SceneArg_Animate animArg;
};

struct Manager {
    enum ManagerState state;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
};

struct WorldPosition {
    struct PositionXYZ pos;
    int direction;
    int fullArea;
};

struct World {
    struct FunctionState state;
    union AreaUnion currentArea;
    enum StoryFlag storyFlag;
    enum FadeType fadeType;
    byte field4_0x8;
    byte IsBattleTimePaused;
    byte m_bx0a;
    enum BackgroundId battleBackgroundId;
    union AreaUnion lastArea;
    byte curEventFlag;
    enum BattleType battleType;
    enum BattleResultState lastBattleResult;
    bool isShuffleFolder;
    byte m_bx12_commentaryTextIndex;
    byte fadeStep;
    byte statAttack;
    byte statSpeed;
    byte statCharge;
    byte m_armor;
    enum SongId currentSongId;
    byte bustingRank;
    bool isTalkingToNPC;
    byte pressedA;
    ushort hpCurrent;
    ushort hpMax;
    int field25_0x20;
    int mapChangeCount;
    struct PlayerLocation *playerLocation;
    struct EnemySpawn *enemyList;
    struct BattleChip *chipFolder;
    void *npcCommandList;
    struct PositionXYZ savedPos;
    int savedDirection;
    struct WorldPosition lastMapPosOffline;
    struct WorldPosition lastMapPosOnline;
    void *updatingEntity;
    int zenny;
};

struct Scene {
    struct FunctionState m_state0;
    byte dialogueIndex;
    byte areaDialogueIndex;
    byte field3_0x6;
    byte field4_0x7;
    ushort m_delayCounter;
    ushort flag1;
    void *scenePointer;
    union SceneArg sceneArg;
    int field9_0x20;
    struct PlayerAnimation *pAnim;
    int field11_0x28;
    int field12_0x2c;
};

struct PlayerLocation {
    struct EntityHeader header;
    struct FamilyDetail family;
    struct FunctionState state;
    byte isCheckBoundary;
    byte eventFlagQueue[3];
    byte direction;
    byte lastDirection;
    enum MoveType moveType;
    enum MoveType lastMoveType;
    byte currDirMoveIndex;
    byte lastDirMoveIndex;
    byte owner;
    byte isCheckElevation;
    int n18;
    ushort s1c;
    ushort s1e;
    int n20;
    struct MapOffsetStruct pos;
    int m_isMovementBlocked;
    int deltaX;
    int deltaY;
    int m_i11;
    int i12;
    int i13;
    int i14;
    int stepCounter;
    int collision_n5C;
    enum PlayerLocationKeyFlag moveKeyFlags;
    ushort m_s5;
    int collisionParamMoving;
    ushort field30_0x68;
    byte movingDist_Lo;
    byte movingDist_Hi;
    int i19;
    int i20;
    int i21;
    int i22;
    int i23;
    struct Sprite m_sprite;
};

struct MainMenu {
    struct FunctionState state;
    ushort timerCapcomLogo;
    byte arrowAnimationTimer;
    byte starAnimationTimer;
    byte selectedOption;
    byte unk9;
    byte hardModeCodeProgress;
    byte isSavePresent;
    byte unk12;
    byte unk13;
    byte unk14;
    byte unk15;
    ushort libraryCount;
    ushort secretChipCount;
    ushort programAdvanceCount;
    byte field15_0x16;
    byte field16_0x17;
};

struct PlayerAnimateArgs {
    byte animationId;
    byte dx;
    byte dy;
    byte time;
};

struct TintArgs {
    byte active;
    enum TintType tintType;
    byte paletteOffset;
    byte field3_0x3;
    int color;
    int paletteArg;
};

struct MapEntranceOptions {
    struct MapEntrance entrance;
    int options;
};

struct TintList {
    struct TintArgs data[18];
};

struct Main {
    struct Manager *manager;
    struct Input *input;
    struct World *world;
    struct Battle *battle;
    struct DisplaySettings *display;
    struct Camera *camera;
    struct FadeSettings *fade;
    void *field7_0x1c;
    void *field8_0x20;
    void *field9_0x24;
    struct Scene *scene;
    void *field11_0x2c;
    void *field12_0x30;
    struct MainMenu *mainMenu;
    struct WindowSettings *window;
    struct BlendSettings *blend;
    void *field16_0x40;
    struct BackgroundDataManager *bgDataManager;
    struct Text *textHandler;
    void *field19_0x4c;
    struct FrameCounter *frameCounter;
    void *field21_0x54;
    struct BgAnimationTask *bgAnimationTaskList;
    struct ScreenTilemapContainer *screens;
    void *field24_0x60;
    struct TintList *tintList;
    struct TextUI *textUi;
    void *field27_0x6c;
    void *field28_0x70;
    void *field29_0x74;
    struct GameStats *gameStats;
    void *field31_0x7c;
};

struct WindowSettings {
    uint winH01;
    uint winV01;
    uint winInOut;
};

struct TextUI {
    byte textWidth;
    byte totalTextLength;
    byte charShade;
    byte pad;
    uint numberBuffer[4];
};

typedef struct MusicPlayer MusicPlayer, *PMusicPlayer;

typedef struct MusicPlayerInfo MusicPlayerInfo, *PMusicPlayerInfo;

typedef struct SongHeader SongHeader, *PSongHeader;

typedef enum MusicPlayerStatus {
    MUSICPLAYER_STATUS_TRACK=65535,
    MUSICPLAYER_STATUS_PAUSE=2147483648
} MusicPlayerStatus;

struct MusicPlayer {
    struct MusicPlayerInfo *info;
    struct MusicPlayerTrack *track;
    byte trackCount;
    short unk_A;
};

struct MusicPlayerInfo {
    struct SongHeader *songHeader;
    enum MusicPlayerStatus status;
    byte trackCount;
    byte priority;
    byte cmd;
    byte unk_B;
    uint clock;
    byte gap[8];
    byte *memAccArea;
    short tempoD;
    short tempoU;
    short tempoI;
    short tempoC;
    short fadeOI;
    short fadeOC;
    short fadeOV;
    struct MusicPlayerTrack *tracks;
    struct ToneData *tone;
    uint ident;
    void (*MPlayMainNext)(struct MusicPlayerInfo *);
    struct MusicPlayerInfo *musicPlayerNext;
};

struct SongHeader {
    byte trackCount;
    byte blockCount;
    byte priority;
    byte reverb;
    struct ToneData *tone;
    byte *part[1];
};

typedef struct NPC NPC, *PNPC;

typedef struct PositionByteXYZ PositionByteXYZ, *PPositionByteXYZ;

struct PositionByteXYZ {
    byte x;
    byte y;
    byte z;
};

struct NPC {
    struct EntityHeader header;
    struct FamilyDetail family;
    struct FunctionState state;
    byte radius;
    byte height;
    byte currDirection;
    byte lastDirection;
    byte m_npcIndex;
    struct PositionByteXYZ posSub;
    byte currFrameIndex;
    byte lastFrameIndex;
    byte paletteIndex;
    byte isMovingZ;
    byte isTalking;
    byte scriptStatus;
    undefined1 field15_0x1a;
    undefined1 field16_0x1b;
    byte m_bx1b_areaDialogIndex;
    byte savedState1;
    byte savedState2;
    byte savedState3;
    short moveDeltaCount;
    short field22_0x22;
    struct PositionXYZ posCurr;
    struct PositionXYZ posNext;
    short currSpriteIndex;
    short lastSpriteIndex;
    struct PositionXYZ m_posDelta;
    int npcIdFlag;
    int m_currentCommand;
    int collisionInfo;
    int movementFlags;
    void *commandListStart;
    int spritePriority;
    int currObjExcludeFlags;
    int lastObjExcludeFlags;
    int m_nextX;
    int m_nextY;
    byte data1[28];
    struct Sprite sprite;
};

typedef enum NpcTalkState {
    NTS_None=0,
    NTS_TalkReadyNpc=1,
    NTS_TalkReadyPlayer=2,
    NTS_Talking=3
} NpcTalkState;

typedef struct OamAttributeListNode OamAttributeListNode, *POamAttributeListNode;

struct OamAttributeListNode {
    int xyDetails;
    short tileDetail;
    byte unused;
    byte next;
};

typedef struct ObjectAffineAttributes ObjectAffineAttributes, *PObjectAffineAttributes;

struct ObjectAffineAttributes {
    short pa;
    short pb;
    short pc;
    short pd;
    byte angle;
    byte scaleX;
    byte scaleY;
};

typedef struct ObjectControl ObjectControl, *PObjectControl;

struct ObjectControl {
    int xyDetails;
    short tileDetails;
    short affineDetails;
};

typedef struct SceneCamera SceneCamera, *PSceneCamera;

struct SceneCamera {
    ushort *commandList;
    ushort movementTimer;
    byte isTimerEnabled;
    byte field3_0x7;
};

typedef enum ScriptOption {
    TS_BreakLoop=1,
    TS_ShowPortrait=2,
    TS_Unskippable_Script=4,
    TS_08=8,
    TS_DrawArrow=16,
    TS_PasscodeEntry=32,
    TS_DisablePasscodeInput=64,
    TS_Skip_Text_Sound=128
} ScriptOption;

typedef struct Song Song, *PSong;

struct Song {
    struct SongHeader *header;
    ushort musicplayer;
    ushort me;
};

typedef struct SoundInfo SoundInfo, *PSoundInfo;

struct SoundInfo {
    uint ident;
    byte pcmDmaCounter;
    byte reverb;
    byte maxChans;
    byte masterVolume;
    byte freq;
    byte mode;
    byte c15;
    byte pcmDmaPeriod;
    byte maxLines;
    byte gap[3];
    int pcmSamplesPerVBlank;
    int pcmFreq;
    int divFreq;
    struct CgbChannel *cgbChans;
    void (*MPlayMainHead)(struct MusicPlayerInfo *);
    struct MusicPlayerInfo *musicPlayerHead;
    void (*CgbSound)(void);
    void (*CgbOscOff)(byte);
    int (*MidiKeyToCgbFreq)(byte, byte, byte);
    void (*MPlayJumpTable)(void);
    void (*plynote)(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
    void (*ExtVolPit)(void);
    byte gap2[16];
    struct SoundChannel chans[12];
    byte pcmBuffer[3168];
};

typedef struct SpriteList SpriteList, *PSpriteList;

struct SpriteList {
    byte *header;
    int length;
};

typedef struct SpriteTilesetDetail SpriteTilesetDetail, *PSpriteTilesetDetail;

struct SpriteTilesetDetail {
    struct SpriteTilesetHeader *spriteTilesetPointer;
    uint dstTileOffset;
};

typedef enum StartMenuState {
    SMS_Suspended=32,
    SMS_SubMenuOpen=64,
    SMS_StartMenuOpen=128
} StartMenuState;

typedef struct Struct_F79A4 Struct_F79A4, *PStruct_F79A4;

struct Struct_F79A4 {
    int *addr;
    ushort s4;
    ushort s6;
};

typedef enum TextOption {
    TF_AllOptions=15,
    TF_Unused=16,
    TF_Flag_20=32,
    TF_DisableInput=64,
    TF_ClearDialogBox=128
} TextOption;

typedef enum WaitDmaFlag {
    WF_DMA_0=1,
    WF_DMA_1=2,
    WF_DMA_2=4,
    WF_DMA_3=8
} WaitDmaFlag;

#endif
