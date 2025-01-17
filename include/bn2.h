#ifndef BN2_H
#define BN2_H

typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef char    sbyte;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef enum ItemId {
    Item_PET=0,
    Item_HeroData=1,
    Item_HopeData=2,
    Item_Fan=3,
    Item_ExamCard=4,
    Item_WalkProg=5,
    Item_NiceData=6,
    Item_Paper=7,
    Item_Lighter=8,
    Item_Stick=9,
    Item_Binocs=10,
    Item_Knife=11,
    Item_Firewood=12,
    Item_Fish=13,
    Item_Balloon=14,
    Item_OddProg=15,
    Item_BadDataA=16,
    Item_BadDataB=17,
    Item_Battery=18,
    Item_YumKey=19,
    Item_NoteData=20,
    Item_Chng_bat=21,
    Item_Ticket=22,
    Item_Passport=23,
    Item_Wireless=24,
    Item_MiniPET=25,
    Item_CyberKey=26,
    Item_Broach=27,
    Item_RoboX=28,
    Item_GoldRing=29,
    Item_PilotCap=30,
    Item_Chopstck=31,
    Item_Whiskey=32,
    Item_Thread=33,
    Item_RedFrag=34,
    Item_RedCure=35,
    Item_HeatData=36,
    Item_YeloCure=37,
    Item_BluFragA=38,
    Item_BluFragB=39,
    Item_GospelID=40,
    Item_KotoPass=41,
    Item_MagSuit=42,
    Item_ElBit042=43,
    Item_ElBit082=44,
    Item_ElBit093=45,
    Item_ElBit201=46,
    Item_ElBit232=47,
    Item_ElBit243=48,
    Item_ElBit253=49,
    Item_ElBit271=50,
    Item_ElBitEV=51,
    Item_LoveLetr=52,
    Item_Beetle=53,
    Item_YumTear=54,
    Item_KngStone=55,
    Item_Twilight=56,
    Item_ArmyData=57,
    Item_ZLicense=58,
    Item_BLicense=59,
    Item_ALicense=60,
    Item_SLicense=61,
    Item_SS_Lic=62,
    Item_SSS_Lic=63,
    Item_FreePass=64,
    Item_GateKeyA=65,
    Item_GateKeyB=66,
    Item_GateKeyC=67,
    Item_GateKeyD=68,
    Item_BugFrag=69,
    Item_MaylCode=80,
    Item_DexCode=81,
    Item_YaiCode=82,
    Item_RibiCode=83,
    Item_RaulCode=84,
    Item_MiliCode=85,
    Item_ONBACode=86,
    Item_GospCode=87,
    Item_ACDCPass=88,
    Item_MariPass=89,
    Item_OkuPass=90,
    Item_AirPass=91,
    Item_HPMemory=96,
    Item_PowerUP=97,
    Item_RegUP1=98,
    Item_RegUP2=99,
    Item_RegUP3=100,
    Item_SubMem=101,
    Item_MiniEnrg=112,
    Item_FullEnrg=113,
    Item_SneakRun=114,
    Item_Untrap=115,
    Item_LocEnemy=116,
    Item_Unlocker=117,
    Item_ITEM7F=127,
    Item_NormStyl=128,
    Item_ElecGuts=134,
    Item_HeatGuts=135,
    Item_AquaGuts=136,
    Item_WoodGuts=137,
    Item_ElecCust=139,
    Item_HeatCust=140,
    Item_AquaCust=141,
    Item_WoodCust=142,
    Item_ElecTeam=144,
    Item_HeatTeam=145,
    Item_AquaTeam=146,
    Item_WoodTeam=147,
    Item_ElecShld=149,
    Item_HeatShld=150,
    Item_AquaShld=151,
    Item_WoodShld=152,
    Item_HubStyl=153
} ItemId;

typedef enum ProgAdvId {
    ProgAdv_FtrSword=0,
    ProgAdv_KngtSwrd=1,
    ProgAdv_HeroSwrd=2,
    ProgAdv_Meteors=3,
    ProgAdv_Poltrgst=4,
    ProgAdv_FireGspl=5,
    ProgAdv_AquaGspl=6,
    ProgAdv_ElecGspl=7,
    ProgAdv_WoodGspl=8,
    ProgAdv_GateSP=9,
    ProgAdv_Snctuary=14,
    ProgAdv_Z_Canon1=16,
    ProgAdv_Z_Canon2=17,
    ProgAdv_Z_Canon3=18,
    ProgAdv_H_Burst=19,
    ProgAdv_Z_Ball=20,
    ProgAdv_Z_Raton1=21,
    ProgAdv_Z_Raton2=22,
    ProgAdv_Z_Raton3=23,
    ProgAdv_O_Canon1=24,
    ProgAdv_O_Canon2=25,
    ProgAdv_O_Canon3=26,
    ProgAdv_M_Burst=27,
    ProgAdv_O_Ball=28,
    ProgAdv_O_Raton1=29,
    ProgAdv_O_Raton2=30,
    ProgAdv_O_Raton3=31,
    ProgAdv_Arrows=32,
    ProgAdv_UltraBmb=33,
    ProgAdv_LifeSrd1=34,
    ProgAdv_LifeSrd2=35,
    ProgAdv_LifeSrd3=36,
    ProgAdv_Punch=37,
    ProgAdv_Curse=38,
    ProgAdv_TimeBom_=39,
    ProgAdv_HvyStamp=40,
    ProgAdv_PoisPhar=41,
    ProgAdv_Gater=42,
    ProgAdv_GtsShoot=43,
    ProgAdv_BigHeart=44,
    ProgAdv_BodyGrd=45,
    ProgAdv_2xHero=46,
    ProgAdv_Darkness=47,
    ProgAdv_Punisher=51,
    ProgAdv_PharTrap=52,
    ProgAdv_2xPlanet=53,
    ProgAdv_RemoGate=57
} ProgAdvId;

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
    ushort tintColor;
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
    byte frameIndexCurr;
    byte frameIndexLast;
    struct CellPosition cPos;
    byte m_direction;
    byte m_bx11;
    byte m_indexNumber;
    byte m_enemyId;
    byte owner;
    byte isInvulnerable;
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

typedef enum AllocParamEntityType {
    APT_PlayerLocation=0,
    APT_Actor=1,
    APT_Attack=2,
    APT_Effect=3,
    APT_NPC=4
} AllocParamEntityType;

typedef enum AreaId {
    Area_ACDC=0,
    Area_Marine=1,
    Area_Okuden=2,
    Area_DenAir=3,
    Area_NetAir=4,
    Area_Netopia=5,
    Area_Plane=6,
    Area_Kotobuki=7,
    Area_Apartment=8,
    Area_GasComp=128,
    Area_BombComp=129,
    Area_MotherComp=130,
    Area_CastleComp=131,
    Area_AirComp=132,
    Area_ApartComp=133,
    Area_HomePage=136,
    Area_OtherComp1=140,
    Area_OtherComp2=141,
    Area_DenArea=142,
    Area_KotobukiArea=145,
    Area_YumlandArea=146,
    Area_NetopiaArea=147,
    Area_Undernet=148
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
    int field39_0x80;
    int field40_0x84;
    int field41_0x88;
    int field42_0x8c;
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
    BG_DenArea=0,
    BG_GasComp=1,
    BG_BombComp=2,
    BG_MotherComp1=3,
    BG_MotherComp2=4,
    BG_CastleComp1=5,
    BG_CastleComp2=6,
    BG_CastleComp3=7,
    BG_PlaneComp=8,
    BG_LanHP=9,
    BG_MaylHP=10,
    BG_DexHP=11,
    BG_YaiHP=12,
    BG_RibittaHP=13,
    BG_RaoulHP=14,
    BG_MillionsHP=15,
    BG_OtherComp=16,
    BG_OfficialArea=17,
    BG_KotobukiArea=18,
    BG_KotobukiSquare1=19,
    BG_KotobukiSquare2=20,
    BG_YumlandArea=21,
    BG_YumlandSquare=22,
    BG_YumlandTreasureRoom=23,
    BG_NetopiaArea=24,
    BG_NetopiaSquare=25,
    BG_Undernet=26,
    BG_ApartComp=27,
    BG_GospelComp=28,
    BG_GospelHQ=29,
    BG_UnderSquare=30,
    BG_WWW=31,
    BG_None=255
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
    ED_MegaMan=0,
    ED_Mettaur1=1,
    ED_Mettaur2=2,
    ED_Mettaur3=3,
    ED_Canodumb1=4,
    ED_Canodumb2=5,
    ED_Canodumb3=6,
    ED_Beetank1=7,
    ED_Beetank2=8,
    ED_Beetank3=9,
    ED_Fishy1=10,
    ED_Fishy2=11,
    ED_Cloudy1=12,
    ED_Cloudy2=13,
    ED_Cloudy3=14,
    ED_Spooky1=15,
    ED_Spooky2=16,
    ED_Spooky3=17,
    ED_Handy1=18,
    ED_Handy2=19,
    ED_Handy3=20,
    ED_Bunny=21,
    ED_TuffBunny=22,
    ED_MegaBunny=23,
    ED_MettFire=24,
    ED_FullFire=25,
    ED_DeathFire=26,
    ED_Puffy=27,
    ED_Buffy=28,
    ED_HardHead1=29,
    ED_HardHead2=30,
    ED_HardHead3=31,
    ED_CanDevil1=32,
    ED_CanDevil2=33,
    ED_CanDevil3=34,
    ED_Mushy=35,
    ED_Mashy=36,
    ED_Moshy=37,
    ED_Swordy1=38,
    ED_Swordy2=39,
    ED_Swordy3=40,
    ED_Mole1=41,
    ED_Mole2=42,
    ED_Poofy=43,
    ED_Fishy3=44,
    ED_Flappy1=45,
    ED_Flappy2=46,
    ED_Flappy3=47,
    ED_Ratty1=48,
    ED_Ratty2=49,
    ED_Ratty3=50,
    ED_Twisty1=51,
    ED_Twisty2=52,
    ED_Twisty3=53,
    ED_Popper1=54,
    ED_Popper2=55,
    ED_Popper3=56,
    ED_Spikey1=57,
    ED_Spikey2=58,
    ED_Spikey3=59,
    ED_Flamey1=60,
    ED_Flamey2=61,
    ED_Flamey3=62,
    ED_Shrimpy1=63,
    ED_Shrimpy2=64,
    ED_Shrimpy3=65,
    ED_PuffBall=66,
    ED_PoofBall=67,
    ED_GoofBall=68,
    ED_Sparky=69,
    ED_Sparkler=70,
    ED_Sparknoid=71,
    ED_Octon=72,
    ED_Octor=73,
    ED_Octovian=74,
    ED_Yort=75,
    ED_Yurt=76,
    ED_Yart=77,
    ED_Shellgeek=78,
    ED_Shellnerd=79,
    ED_Shellman=80,
    ED_KillPlant=81,
    ED_KillWeed=82,
    ED_KillFleur=83,
    ED_Dominerd1=84,
    ED_Dominerd2=85,
    ED_Dominerd3=86,
    ED_Protecto1=87,
    ED_Protecto2=88,
    ED_Protecto3=89,
    ED_Null=90,
    ED_Void=91,
    ED_NullVoid=92,
    ED_Magneaker=93,
    ED_Magmacker=94,
    ED_Magnoid=95,
    ED_Shadow=96,
    ED_RedDevil=97,
    ED_BlueDemon=98,
    ED_WindBox=99,
    ED_VacuumFan=100,
    ED_StormBox=101,
    ED_RedUFO=102,
    ED_BlueUFO=103,
    ED_GreenUFO=104,
    ED_Snapper1=105,
    ED_Snapper2=106,
    ED_Snapper3=107,
    ED_Brushman1=108,
    ED_Brushman2=109,
    ED_Brushman3=110,
    ED_Lavagon=111,
    ED_Bluegon=112,
    ED_Yellowgon=113,
    ED_Scutz=114,
    ED_Scuttle=115,
    ED_Scuttler=116,
    ED_Scuttzer=117,
    ED_Scuttlest=118,
    ED_MegalianA=119,
    ED_MegalianH=120,
    ED_MegalianW=121,
    ED_MegalianE=122,
    ED_AirManV1=128,
    ED_AirManV2=129,
    ED_AirManV3=130,
    ED_QuickManV1=131,
    ED_QuickManV2=132,
    ED_QuickManV3=133,
    ED_CutManV1=134,
    ED_CutManV2=135,
    ED_CutManV3=136,
    ED_ShadowManV1=137,
    ED_ShadowManV2=138,
    ED_ShadowManV3=139,
    ED_KnightManV1=140,
    ED_KnightManV2=141,
    ED_KnightManV3=142,
    ED_MagnetManV1=143,
    ED_MagnetManV2=144,
    ED_MagnetManV3=145,
    ED_FreezeManV1=146,
    ED_FreezeManV2=147,
    ED_FreezeManV3=148,
    ED_Gospel=149,
    ED_HeatManV1=152,
    ED_HeatManV2=153,
    ED_HeatManV3=154,
    ED_ToadManV1=155,
    ED_ToadManV2=156,
    ED_ToadManV3=157,
    ED_ThunderManV1=158,
    ED_ThunderManV2=159,
    ED_ThunderManV3=160,
    ED_SnakeManV1=161,
    ED_SnakeManV2=162,
    ED_SnakeManV3=163,
    ED_GutsManV1=164,
    ED_GutsManV2=165,
    ED_GutsManV3=166,
    ED_ProtoManV1=167,
    ED_ProtoManV2=168,
    ED_ProtoManV3=169,
    ED_GateManV1=170,
    ED_GateManV2=171,
    ED_GateManV3=172,
    ED_PlanetManV1=173,
    ED_PlanetManV2=174,
    ED_PlanetManV3=175,
    ED_NapalmManV1=176,
    ED_NapalmManV2=177,
    ED_NapalmManV3=178,
    ED_PharaohManV1=179,
    ED_PharaohManV2=180,
    ED_PharaohManV3=181,
    ED_Bass=182,
    ED_BassV2=183,
    ED_BassDeluxe=184,
    ED_Invalid=255
} EnemyId;

typedef enum BattleObjectType {
    BOT_MegaMan=0,
    BOT_Enemy=1,
    BOT_Rock=2,
    BOT_RockCube=3,
    BOT_MetalCube=4,
    BOT_IceCube=5,
    BOT_Guardian=6,
    BOT_BlackBomb=7
} BattleObjectType;

struct EnemySpawn {
    enum EnemyId id;
    byte x;
    byte y;
    enum BattleObjectType type;
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
    enum BackgroundId backgroundId;
    byte randomCellSeed;
    bool isGaugeFull;
    byte m_customScreenChipCount;
    byte m_customScreenSelectedChipCount;
    byte customGaugeSpeed;
    bool isInputLocked;
    byte startPressState;
    byte sioMultiplayerId;
    bool isScreenDimChipActive;
    byte sioOtherMpId;
    byte multiDeleteBufferTimer;
    byte multiDeleteTempCounter;
    byte multiDeleteCount;
    byte srcBattleHandCount;
    byte bx1c;
    byte bx1d;
    byte bx1e_MPState;
    bool isBattleActive;
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
    ushort battleTime;
    int field40_0x48;
    struct Actor *actorListPlayer[2];
    byte enemyPriorityQueue[8];
    byte enemyIdList[4];
    uint field43_0x58;
    int field44_0x5c;
    uint battleFlag_buffer;
    uint battleFlag;
    struct Actor *actorListEnemy[4];
    struct EnemySpawn *enemyList;
    byte srcBattleHandIndexList[6];
    byte m_srcBattleHandCodeList[6];
};

typedef struct BattleChip BattleChip, *PBattleChip;

typedef enum ChipId {
    CD_Buster=0,
    CD_Cannon=1,
    CD_HiCannon=2,
    CD_M_Cannon=3,
    CD_Shotgun=4,
    CD_V_Gun=5,
    CD_CrossGun=6,
    CD_Spreader=7,
    CD_Bubbler=8,
    CD_Bub_V=9,
    CD_BubCross=10,
    CD_BubSprd=11,
    CD_HeatShot=12,
    CD_Heat_V=13,
    CD_HeatCros=14,
    CD_HeatSprd=15,
    CD_MiniBomb=16,
    CD_LilBomb=17,
    CD_CrosBomb=18,
    CD_BigBomb=19,
    CD_TreeBom1=20,
    CD_TreeBom2=21,
    CD_TreeBom3=22,
    CD_Sword=23,
    CD_WideSwrd=24,
    CD_LongSwrd=25,
    CD_FireSwrd=26,
    CD_AquaSwrd=27,
    CD_ElecSwrd=28,
    CD_FireBlde=29,
    CD_AquaBlde=30,
    CD_ElecBlde=31,
    CD_StepSwrd=32,
    CD_Muramasa=33,
    CD_CustSwrd=34,
    CD_Kunai1=35,
    CD_Kunai2=36,
    CD_Kunai3=37,
    CD_Slasher=38,
    CD_Shockwav=39,
    CD_Sonicwav=40,
    CD_Dynawave=41,
    CD_Quake1=42,
    CD_Quake2=43,
    CD_Quake3=44,
    CD_GutPunch=45,
    CD_ColdPnch=46,
    CD_Atk20=47,
    CD_Atk30=48,
    CD_Navi40=49,
    CD_DashAtk=50,
    CD_Wrecker=51,
    CD_CannBall=52,
    CD_DoubNdl=53,
    CD_TripNdl=54,
    CD_QuadNdl=55,
    CD_Trident=56,
    CD_Ratton1=57,
    CD_Ratton2=58,
    CD_Ratton3=59,
    CD_FireRat=60,
    CD_Tornado=61,
    CD_Twister=62,
    CD_Blower=63,
    CD_Burner=64,
    CD_ZapRing1=65,
    CD_ZapRing2=66,
    CD_ZapRing3=67,
    CD_Spice1=68,
    CD_Spice2=69,
    CD_Spice3=70,
    CD_Satelit1=71,
    CD_Satelit2=72,
    CD_Satelit3=73,
    CD_Yo_Yo1=74,
    CD_Yo_Yo2=75,
    CD_Yo_Yo3=76,
    CD_MagBomb1=77,
    CD_MagBomb2=78,
    CD_MagBomb3=79,
    CD_Meteor9=80,
    CD_Meteor12=81,
    CD_Meteor15=82,
    CD_Meteor18=83,
    CD_Hammer=84,
    CD_CrsShld1=85,
    CD_CrsShld2=86,
    CD_CrsShld3=87,
    CD_TimeBom1=88,
    CD_TimeBom2=89,
    CD_TimeBom3=90,
    CD_LilCloud=91,
    CD_MedCloud=92,
    CD_BigCloud=93,
    CD_Mine=94,
    CD_FrntSnsr=95,
    CD_DblSnsr=96,
    CD_Remobit1=97,
    CD_Remobit2=98,
    CD_Remobit3=99,
    CD_AquaBall=100,
    CD_ElecBall=101,
    CD_HeatBall=102,
    CD_Geyser=103,
    CD_LavaDrag=104,
    CD_GodStone=105,
    CD_OldWood=106,
    CD_PoisMask=107,
    CD_PoisFace=108,
    CD_Whirlpl=109,
    CD_Blckhole=110,
    CD_Guard=111,
    CD_Barrier=112,
    CD_PanlOut1=113,
    CD_PanlOut3=114,
    CD_LineOut=115,
    CD_Lance=116,
    CD_ZeusHamr=117,
    CD_BrnzFist=118,
    CD_SilvFist=119,
    CD_GoldFist=120,
    CD_VarSwrd=121,
    CD_Recov10=122,
    CD_Recov30=123,
    CD_Recov50=124,
    CD_Recov80=125,
    CD_Recov120=126,
    CD_Recov150=127,
    CD_Recov200=128,
    CD_Recov300=129,
    CD_PanlGrab=130,
    CD_AreaGrab=131,
    CD_GrabRvng=132,
    CD_Geddon1=133,
    CD_Geddon2=134,
    CD_Geddon3=135,
    CD_Catcher=136,
    CD_Mindbndr=137,
    CD_Escape=138,
    CD_AirShoes=139,
    CD_Repair=140,
    CD_Candle1=141,
    CD_Candle2=142,
    CD_Candle3=143,
    CD_RockCube=144,
    CD_Prism=145,
    CD_Guardian=146,
    CD_Wind=147,
    CD_Fan=148,
    CD_Anubis=149,
    CD_SloGauge=150,
    CD_FstGauge=151,
    CD_FullCust=152,
    CD_Invis1=153,
    CD_Invis2=154,
    CD_Invis3=155,
    CD_DropDown=156,
    CD_PopUp=157,
    CD_StoneBod=158,
    CD_Shadow1=159,
    CD_Shadow2=160,
    CD_Shadow3=161,
    CD_UnderSht=162,
    CD_BblWrap=163,
    CD_LeafShld=164,
    CD_AquaAura=165,
    CD_FireAura=166,
    CD_WoodAura=167,
    CD_ElecAura=168,
    CD_LifeAur1=169,
    CD_LifeAur2=170,
    CD_LifeAur3=171,
    CD_MagLine=172,
    CD_LavaLine=173,
    CD_IceLine=174,
    CD_GrassLne=175,
    CD_LavaStge=176,
    CD_IceStage=177,
    CD_GrassStg=178,
    CD_HolyPanl=179,
    CD_Jealosy=180,
    CD_AntiFire=181,
    CD_AntiElec=182,
    CD_AntiWatr=183,
    CD_AntiDmg=184,
    CD_AntiSwrd=185,
    CD_AntiNavi=186,
    CD_AntiRecv=187,
    CD_Atk10=188,
    CD_Fire40=189,
    CD_Aqua40=190,
    CD_Wood40=191,
    CD_Elec40=192,
    CD_Navi20=193,
    CD_RollV1=194,
    CD_RollV2=195,
    CD_RollV3=196,
    CD_GutsManV1=197,
    CD_GutsManV2=198,
    CD_GutsManV3=199,
    CD_ProtomanV1=200,
    CD_ProtomanV2=201,
    CD_ProtomanV3=202,
    CD_AirManV1=203,
    CD_AirManV2=204,
    CD_AirManV3=205,
    CD_QuickManV1=206,
    CD_QuickManV2=207,
    CD_QuickManV3=208,
    CD_CutManV1=209,
    CD_CutManV2=210,
    CD_CutManV3=211,
    CD_ShadowManV1=212,
    CD_ShadowManV2=213,
    CD_ShadowManV3=214,
    CD_KnightManV1=215,
    CD_KnightManV2=216,
    CD_KnightManV3=217,
    CD_MagnetManV1=218,
    CD_MagnetManV2=219,
    CD_MagnetManV3=220,
    CD_FreezeManV1=221,
    CD_FreezeManV2=222,
    CD_FreezeManV3=223,
    CD_HeatManV1=224,
    CD_HeatManV2=225,
    CD_HeatManV3=226,
    CD_ToadManV1=227,
    CD_ToadManV2=228,
    CD_ToadManV3=229,
    CD_ThunderManV1=230,
    CD_ThunderManV2=231,
    CD_ThunderManV3=232,
    CD_SnakeManV1=233,
    CD_SnakeManV2=234,
    CD_SnakeManV3=235,
    CD_GateManV1=236,
    CD_GateManV2=237,
    CD_GateManV3=238,
    CD_PlanetManV1=239,
    CD_PlanetManV2=240,
    CD_PlanetManV3=241,
    CD_NapalmManV1=242,
    CD_NapalmManV2=243,
    CD_NapalmManV3=244,
    CD_PharaohManV1=245,
    CD_PharaohManV2=246,
    CD_PharaohManV3=247,
    CD_BassV1=248,
    CD_BassV2=249,
    CD_BassV3=250,
    CD_BgRedWav=251,
    CD_FreezBom=252,
    CD_Sparker=253,
    CD_GaiaSwrd=254,
    CD_BlkBomb=255,
    CD_FtrSword=256,
    CD_KngtSwrd=257,
    CD_HeroSwrd=258,
    CD_Meteors=259,
    CD_Poltrgst=260,
    CD_FireGspl=261,
    CD_AquaGspl=262,
    CD_ElecGspl=263,
    CD_WoodGspl=264,
    CD_GateSP=265,
    CD_Snctuary=270,
    CD_Z_Canon1=272,
    CD_Z_Canon2=273,
    CD_Z_Canon3=274,
    CD_H_Burst=275,
    CD_Z_Ball=276,
    CD_Z_Raton1=277,
    CD_Z_Raton2=278,
    CD_Z_Raton3=279,
    CD_O_Canon1=280,
    CD_O_Canon2=281,
    CD_O_Canon3=282,
    CD_M_Burst=283,
    CD_O_Ball=284,
    CD_O_Ratton1=285,
    CD_O_Ratton2=286,
    CD_O_Ratton3=287,
    CD_Arrows=288,
    CD_UltraBmd=289,
    CD_LifeSrd1=290,
    CD_LifeSrd2=291,
    CD_LifeSrd3=292,
    CD_Punch=293,
    CD_Curse=294,
    CD_TimeBom=295,
    CD_HvyStamp=296,
    CD_PoisPhar=297,
    CD_Gater=298,
    CD_GtsShoot=299,
    CD_BigHeart=300,
    CD_BodyGrd=301,
    CD_2xHero=302,
    CD_Darkness=303
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
    CC_Z=25,
    CC_Star=26,
    CC_None=27
} ChipCode;

struct BattleChip {
    enum ChipId chipId;
    enum ChipCode chipCode;
};

typedef struct BattleChipData BattleChipData, *PBattleChipData;

struct BattleChipData {
    enum ChipCode chipCodes[6];
    byte elementIndex;
    byte family;
    byte subfamily;
    byte rarity;
    byte mb;
    byte flag;
    ushort damage;
    ushort libraryIndex;
    ushort alphabetIndex;
    byte type;
    byte field11_0x13;
    struct Tile *icon;
    struct Tile *tileset;
    struct Color *palette;
};

typedef struct BattleChipFolderSlot BattleChipFolderSlot, *PBattleChipFolderSlot;

struct BattleChipFolderSlot {
    enum ChipId id;
    enum ChipCode code;
    byte field2_0x3;
};

typedef struct BattleChipInventorySlot BattleChipInventorySlot, *PBattleChipInventorySlot;

struct BattleChipInventorySlot {
    byte codes[6];
    ushort slots[6];
};

typedef enum BattleFlag {
    BF_0=0
} BattleFlag;

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

typedef struct BattleUI BattleUI, *PBattleUI;

struct BattleUI {
    byte field0_0x0[3];
    byte field1_0x3;
    byte uiFlag;
    byte chipNameWidth;
    byte fullChipGaugeAnimationTimer;
    bool isCustomGaugeRising;
    ushort hpDisplay;
    ushort hpActual;
    byte buffer[32];
    byte field9_0x2c[116];
};

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

typedef enum BgControlType {
    BGC_Standard=0,
    BGC_OnlyBg0=1,
    BGC_OnlyBg01=2,
    BGC_All_4bpp=3,
    BGC_OnlyBg012=4,
    BGC_All_8bpp=5,
    BGC_All_Bg3_8bpp=6
} BgControlType;

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

typedef struct CollisionResult CollisionResult, *PCollisionResult;

struct CollisionResult {
    int flag;
    int attribute;
};

typedef struct Demo Demo, *PDemo;

struct Demo {
    byte field0_0x0;
    byte field1_0x1;
    byte field2_0x2;
    byte field3_0x3;
    byte field4_0x4;
    byte field5_0x5;
    byte field6_0x6;
    byte field7_0x7;
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

typedef struct EnemyDetail EnemyDetail, *PEnemyDetail;

typedef enum SpriteGroup {
    SG_MegaMan=0,
    SG_Virus=4,
    SG_Navi=8,
    SG_ChipAttack=12,
    SG_VirusAttack=16,
    SG_BattleEffect=20,
    SG_Character=24,
    SG_Object=28,
    SG_Portrait=32
} SpriteGroup;

struct EnemyDetail {
    ushort hp;
    byte field1_0x2;
    byte field2_0x3;
    enum SpriteGroup routineType;
    byte lzSpriteIndex;
    byte field5_0x6;
    byte field6_0x7;
};

typedef struct EntityAllocParams EntityAllocParams, *PEntityAllocParams;

struct EntityAllocParams {
    enum AllocParamEntityType entityType;
    byte param0;
    byte field2_0x2;
    byte field3_0x3;
    int param1;
    int param2;
    int param3;
    int param4;
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

typedef enum EntityFuncFlag {
    GFF_None=0,
    GFF_PlayerLocation=1,
    GFF_Actor=2,
    GFF_Attack=4,
    GFF_DisplayObject=8,
    GFF_NPC=16,
    GFF_All=31
} EntityFuncFlag;

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

typedef struct FieldObject FieldObject, *PFieldObject;

typedef enum FieldObjectFlag {
    F9_None=0,
    F9_1=1,
    F9_IsLive=2,
    F9_NewObject=4,
    F9_IsSpread=8
} FieldObjectFlag;

typedef enum PanelFlag {
    PF_Walkable=1,
    PF_EnemyTerritory=2,
    PF_Cracked=4,
    PF_Ground=8,
    PF_PlayerOccupied=16,
    PF_EnemyOccupied=32,
    PF_Player=64,
    PF_Enemy=128,
    PF_100=256,
    PF_Deleted=512,
    PF_Teleporting=1024,
    PF_Solid=2048,
    PF_PlayerPush=4096,
    PF_EnemyPush=8192,
    PF_Break=16384,
    PF_FieldBlock=32768,
    PF_DieBombExplosion=65536,
    PF_Apple=131072,
    PF_Armor=262144,
    PF_ActorPlayer=524288,
    PF_ActorEnemy=1048576,
    PF_Freeze=2097152,
    PF_Chaser=4194304,
    PF_Numb=8388608,
    PF_Drain=16777216,
    PF_Sealed=33554432,
    PF_Trap=67108864
} PanelFlag;

struct FieldObject {
    enum FieldObjectFlag flags;
    byte id;
    struct CellPosition cPosCurr;
    struct CellPosition cPosLast;
    enum ElementId element;
    byte routineType;
    short damage;
    enum PanelFlag panelFlags;
    int idFlag;
    int attackerIdFlags;
};

typedef enum FlagType {
    FL_BASE=0,
    FL_SYSTEM=8
} FlagType;

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

typedef struct GameOver GameOver, *PGameOver;

struct GameOver {
    enum FuncState state;
    byte field1_0x1[3];
    ushort timer;
    byte field3_0x6;
    byte field4_0x7;
};

typedef struct GameStats GameStats, *PGameStats;

struct GameStats {
    byte sortOrderFolder;
    byte sortDirectionFolder;
    byte sortOrderSack;
    byte sortDirectionSack;
    bool hasUsedEscape;
    byte batteryCharge;
    byte unlockedFolderCount;
    undefined1 field7_0x7;
    byte busterAttack;
    byte busterRapid;
    byte busterCharge;
    byte nextStyleElement;
    byte field10_0xc;
    byte m_b0;
    byte totalAwardedChips;
    byte totalBattles8;
    short hpCurr;
    ushort hpMax;
    ushort field18_0x14;
    ushort field19_0x16;
    int field20_0x18;
    int stepsTotal;
    short multiBattleTotal;
    short multiBattleWins;
    int gameTimer;
    int inBattleTimer;
    int checksum;
    int currStepCounter;
    int lastStepCounter;
    byte field29_0x38[64];
    byte buildId[14];
};

typedef struct GravityXYResult GravityXYResult, *PGravityXYResult;

struct GravityXYResult {
    int delay;
    int dx;
    int dy;
};

typedef struct GravityZResult GravityZResult, *PGravityZResult;

struct GravityZResult {
    int dz;
    int time;
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

typedef enum InvisStatus {
    IS_None=0,
    IS_Invis=1,
    IS_Dropdown=2,
    IS_Popup=3
} InvisStatus;

typedef struct Main Main, *PMain;

typedef struct Manager Manager, *PManager;

typedef struct World World, *PWorld;

typedef struct PlayerBattleState PlayerBattleState, *PPlayerBattleState;

typedef struct MapEventState MapEventState, *PMapEventState;

typedef struct Scene Scene, *PScene;

typedef struct MapChange MapChange, *PMapChange;

typedef struct Transition Transition, *PTransition;

typedef struct MainMenu MainMenu, *PMainMenu;

typedef struct WindowSettings WindowSettings, *PWindowSettings;

typedef struct Text Text, *PText;

typedef struct ScreenDim ScreenDim, *PScreenDim;

typedef struct ScreenTilemapContainer ScreenTilemapContainer, *PScreenTilemapContainer;

typedef struct PetStatusControl PetStatusControl, *PPetStatusControl;

typedef struct TintList TintList, *PTintList;

typedef struct TextUI TextUI, *PTextUI;

typedef struct StartMenu StartMenu, *PStartMenu;

typedef struct Menu Menu, *PMenu;

typedef enum ManagerState {
    MS_MainMenu=0,
    MS_World=4,
    MS_Battle=8,
    MS_Transition=12,
    MS_Demo=16,
    MS_Splash=20,
    MS_Menu=24,
    MS_Shop=28,
    MS_GameOver=32,
    MS_ChipTrader=36,
    MS_Request=40,
    MS_Credits=44,
    MS_30=48
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

typedef struct PlayerLocation PlayerLocation, *PPlayerLocation;

typedef struct WorldPosition WorldPosition, *PWorldPosition;

typedef union SceneArg SceneArg, *PSceneArg;

typedef struct PlayerAnimation PlayerAnimation, *PPlayerAnimation;

typedef struct MapEntrance MapEntrance, *PMapEntrance;

typedef enum ScriptOption {
    TS_None=0,
    TS_BreakLoop=1,
    TS_ShowPortrait=2,
    TS_Unskippable_Script=4,
    TS_OpenPickControl=8,
    TS_DrawArrow=16,
    TS_DisableDialogSound=32,
    TS_ReadInput=64,
    TS_SkipSelectSound=128
} ScriptOption;

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

struct MapEntrance {
    enum MapId area;
    byte field1_0x2;
    byte direction;
    struct PositionXYZ pos;
};

struct PlayerBattleState {
    byte timerInvulnerable;
    byte chipsUsedCount;
    byte m_moveCount;
    byte m_hitsTaken;
    byte m_bx04;
    byte m_bx05;
    byte lastChipElement;
    byte betaSigmaChipIndex;
    byte busterChip;
    byte statAttack;
    byte statSpeed;
    byte statCharge;
    byte bubbleShieldFamily;
    enum InvisStatus invisStatus;
    byte numbDamage;
    byte armor;
    short busterChargeLevel;
    short busterChargeDamage;
    short busterChargeDelay;
    short m_sx16;
    short lastChipDamage;
    short zetaOmegaActiveTime;
    short timerInvisible;
    enum KeyInput curKeyState;
    enum KeyInput toggleKeyState;
    short m_unk22;
    enum KeyInput lastKeyState;
    ushort hpCurrent;
    ushort hpMax;
    short damageTaken;
    short timerBubbleShield;
    short timerIronBody;
    short numbStatusTimer;
    int field33_0x34;
    int field34_0x38;
    int field35_0x3c;
    struct Attack *auraObj;
    struct FieldObject *fieldObj0;
    struct FieldObject *fieldObj1;
    byte field39_0x4c[4];
    union EntityParam obj_50;
    struct Attack *shieldAtk;
    struct Attack *numbAtk;
    enum PanelFlag attackPanelFlags;
    byte betaSigmaChipList[10];
    byte listBattleHandIndex[6];
};

struct StartMenu {
    struct FunctionState state;
    byte menuPos;
    byte openState;
    byte selectedIndex;
    byte cursorTimer;
    struct TilemapEntry tilemapZenny[12];
    byte extra[24];
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

struct Manager {
    enum ManagerState state;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    byte softResetTimer;
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
    enum FuncState state;
    byte style; /* guts, custom, team, shield, hub */
    byte field2_0x2;
    byte field3_0x3;
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
    byte currentSongId;
    byte bustingRank;
    bool isTalkingToNPC;
    byte pressedA;
    int mapChangeCount;
    ushort hpCurrent;
    ushort hpMax;
    struct BattleChip *chipFolder;
    struct PlayerLocation *playerLocation;
    struct EnemySpawn *enemyList;
    void *npcCommandList;
    byte *bp78;
    struct PositionXYZ savedPos;
    int savedDirection;
    struct WorldPosition lastMapPosOffline;
    struct WorldPosition lastMapPosOnline;
    void *updatingEntity;
    int zenny;
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

struct MapChange {
    struct MapEntrance destination;
    byte type;
    byte field2_0x11;
    byte destinationIndex;
    byte field4_0x13;
    void *destinationList;
};

struct MapEntranceOptions {
    struct MapEntrance entrance;
    int options;
};

struct TintList {
    struct TintArgs data[18];
};

struct Menu {
    struct FunctionState state;
    struct BattleChipData *m_chipData;
    byte m_chipid;
    byte m_chipCode;
    byte b2;
    byte isShowChipDetail;
    byte curFolderVisualOffset;
    byte lastFolderVisualOffset;
    byte inputDelay;
    byte folderAnimationCounter;
    byte folderCount;
    byte folderSelectionFlag;
    ushort pageIndexFolder;
    ushort lastPageIndexFolder;
    ushort pageOffsetFolder;
    ushort lastPageOffsetFolder;
    short curFolderCount;
    ushort pageIndexSack;
    short lastPageIndexSack;
    ushort pageOffsetSack;
    short lastPageOffsetSack;
    ushort curSackCount;
    ushort m_st1;
    ushort selectedChipPageOffset;
    ushort selectedChipListOffset;
    struct TilemapEntry numberDisplay[8];
    int chipDetailX;
    int chipDetailY;
    short curSortMenuArrowPos;
    short lastSortMenuArrowPos;
    short s40;
    short s42;
    short m_sxx0;
    short sxx1;
    int ix9;
};

struct WindowSettings {
    uint winH01;
    uint winV01;
    uint winInOut;
};

struct PetStatusControl {
    byte field0_0x0;
    byte field1_0x1;
    byte field2_0x2;
    byte field3_0x3;
    enum FuncState state;
    byte petAnimCounter;
    byte alertAnimCounter;
    byte alertAudioCounter;
    ushort hpCurr;
    byte field9_0xa;
    byte field10_0xb;
    byte field11_0xc;
    byte field12_0xd;
    byte field13_0xe;
    byte field14_0xf;
};

struct MapEventState {
    enum FuncState state;
    byte field1_0x1;
    byte field2_0x2;
    byte field3_0x3;
    byte field4_0x4;
    byte field5_0x5;
    byte field6_0x6;
    byte field7_0x7;
    byte field8_0x8;
    byte field9_0x9;
    byte field10_0xa;
    byte field11_0xb;
    byte field12_0xc;
    byte field13_0xd;
    byte field14_0xe;
    byte field15_0xf;
};

struct Text {
    bool isWriteText;
    byte textBlockIndex;
    byte textBufferOffset;
    enum ScriptOption scriptOptions;
    enum TextStateDelayType dialogDelayType;
    byte isScriptJump;
    byte counter1;
    byte portraitPalIndex;
    byte nextDelay;
    byte commandParseDelay;
    byte nextAnimationIndex;
    byte currAnimationIndex;
    ushort dialogDelayCounter;
    byte textCol;
    byte textRow;
    byte layoutLineOffset;
    byte scriptParseDelay;
    byte dialogSkipDelay;
    byte charShade;
    byte optionArrowFrame;
    byte b15_optionFlag;
    byte m_b16_animIndexPlus;
    byte dialogControlOption;
    byte dialogArrowAnimCycle;
    byte arrowAnimFrame;
    byte leftPad;
    byte topPad;
    enum KeyInput curKeyState;
    enum KeyInput heldKeyState;
    enum KeyInput toggleKeyState;
    ushort textSound;
    byte *commandTextPointer;
    ushort *textBlockPointer;
    byte *layoutTextPointer;
    struct TilemapEntry *dialogLayout;
    uint itemIdList[4];
    void *textPointerAfterKeyPrint;
    void *otherTextPointerAfterKeyPrint;
    byte m_possibleBcdBuffer[12];
    byte m_tempPlayerDirection;
    byte b19;
    byte b20;
    byte b21;
    ushort textBufIndex;
    ushort otherTempTextBufIndex;
    struct Sprite portrait;
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

struct Transition {
    enum FuncState state0;
    enum FuncState state1;
    byte animationTimer;
    byte field3_0x3;
    struct MapEntrance *field4_0x4;
};

struct ScreenDim {
    struct FunctionState state;
    byte family;
    byte subFamily;
    byte owner;
    byte isDim;
    ushort timer;
    ushort field6_0xa;
    ushort damage;
    ushort field8_0xe;
    int parent;
    union EntityParam obj_14;
    byte field11_0x18;
    byte field12_0x19;
    byte field13_0x1a;
    byte field14_0x1b;
    int field15_0x1c;
};

struct Main {
    struct Manager *manager;
    struct Input *input;
    struct World *world;
    struct Battle *battle;
    struct DisplaySettings *display;
    struct Camera *camera;
    struct FadeSettings *fade;
    struct BattleUI *battleUi;
    struct PlayerBattleState *playerBattleState;
    struct MapEventState *mapEventState;
    struct Scene *scene;
    struct MapChange *mapChange;
    struct Transition *transition;
    struct MainMenu *mainMenu;
    struct WindowSettings *window;
    struct BlendSettings *blend;
    struct Demo *demo;
    struct BackgroundDataManager *bgDataManager;
    struct Text *textHandler;
    void *field19_0x4c;
    struct FrameCounter *frameCounter;
    struct ScreenDim *screenDim;
    struct BgAnimationTask *bgAnimationTaskList;
    struct ScreenTilemapContainer *screens;
    struct PetStatusControl *petStatusControl;
    struct TintList *tintList;
    struct TextUI *textUi;
    struct StartMenu *startMenu;
    void *field28_0x70;
    struct Menu *menu;
    struct GameStats *gameStats;
    void *field31_0x7c;
};

struct TextUI {
    byte textWidth;
    byte totalTextLength;
    byte charShade;
    byte pad;
    uint numberBuffer[4];
};

typedef struct MapOffset MapOffset, *PMapOffset;

struct MapOffset {
    int x;
    int y;
};

typedef struct MapParameters MapParameters, *PMapParameters;

typedef struct WallSegment WallSegment, *PWallSegment;

typedef struct WallParameters WallParameters, *PWallParameters;

struct WallSegment {
    ushort gridIndex;
    ushort wallParamPtr;
};

struct WallParameters {
    byte zCoord;
    byte attributes;
    byte zRange;
    byte shape;
};

struct MapParameters {
    struct WallSegment *wallSegmentStart;
    short wallSegmentCount;
    byte gridSizeX;
    byte gridSizeY;
    ushort curGridIndex;
    byte m_unknownIndex;
    byte m_b1;
    int mapTileX;
    int mapTileY;
    struct WallParameters *curWallParam;
    byte field10_0x18[8];
};

typedef struct MapParameters_Boundary MapParameters_Boundary, *PMapParameters_Boundary;

typedef struct MapWallSegment MapWallSegment, *PMapWallSegment;

struct MapParameters_Boundary {
    struct WallSegment *wallSegmentStart;
    short wallSegmentCount;
    ushort curGridIndex;
    byte gridSizeX;
    byte gridSizeY;
    byte countMapSegmentHistory;
    byte m_b1;
    byte curWallAttribute;
    byte field8_0xd;
    byte field9_0xe;
    byte field10_0xf;
    struct MapWallSegment *currMapSegment;
    struct MapWallSegment *mapSegmentEnd;
};

struct MapWallSegment {
    struct WallSegment wallSegment;
    struct MapOffset position;
    int _pad;
};

typedef struct MapSegmentSubPosDetail MapSegmentSubPosDetail, *PMapSegmentSubPosDetail;

struct MapSegmentSubPosDetail {
    struct PositionXYZ curr;
    struct PositionXYZ last;
    struct PositionXYZ plus;
};

typedef struct MapWallSectionHeader MapWallSectionHeader, *PMapWallSectionHeader;

struct MapWallSectionHeader {
    int segmentCount;
    struct WallSegment wallSegments[1];
};

typedef struct MusicPlayer MusicPlayer, *PMusicPlayer;

typedef struct MusicPlayerInfo MusicPlayerInfo, *PMusicPlayerInfo;

typedef struct SongHeader SongHeader, *PSongHeader;

typedef enum MusicPlayerStatus {
    MUSICPLAYER_STATUS_TRACK=65535,
    MUSICPLAYER_STATUS_PAUSE=2147483648
} MusicPlayerStatus;

struct SongHeader {
    byte trackCount;
    byte blockCount;
    byte priority;
    byte reverb;
    struct ToneData *tone;
    byte *part[1];
};

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

typedef struct OamAddObjectArgs OamAddObjectArgs, *POamAddObjectArgs;

struct OamAddObjectArgs {
    int xyAttrs;
    int tileAttrs;
    int listIndex;
    int listOffset;
};

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

typedef struct ObjectPos ObjectPos, *PObjectPos;

struct ObjectPos {
    int objectX;
    int objectY;
    int isDraw;
};

typedef struct Palette Palette, *PPalette;

struct Palette {
    struct Color colors[16];
};

typedef struct Position4 Position4, *PPosition4;

struct Position4 {
    int x;
    int y;
};

typedef struct RankResult RankResult, *PRankResult;

struct RankResult {
    int totalRank;
    int timeBcd;
    int timeRank;
};

typedef struct SceneCamera SceneCamera, *PSceneCamera;

struct SceneCamera {
    ushort *commandList;
    ushort movementTimer;
    byte isTimerEnabled;
    byte field3_0x7;
};

typedef struct Shop Shop, *PShop;

typedef struct ShopItem ShopItem, *PShopItem;

struct ShopItem {
    byte itemType;
    byte itemIndex;
    byte chipCode;
    byte stock;
    int price;
};

struct Shop {
    struct FunctionState state;
    byte inventoryCount;
    byte itemIndex;
    byte arrowPos;
    byte arrowVisualPos;
    byte arrowAnimationCounter;
    byte pageIndex;
    byte shopClerkType;
    byte field8_0xb;
    ushort menuPosSlideOut;
    ushort field10_0xe;
    int zenny;
    struct ShopItem inventoryList[1];
};

typedef struct Song Song, *PSong;

struct Song {
    struct SongHeader *header;
    ushort musicplayer;
    ushort me;
};

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
    SE_PetAlert=134,
    SE_Battle_EncounterStart=199,
    T_NoSong=255
} SongId;

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

typedef struct SpriteArchive_Header SpriteArchive_Header, *PSpriteArchive_Header;

struct SpriteArchive_Header {
    byte unk0;
    byte magic0;
    byte magic1;
    byte numSprites;
    byte data[1];
};

typedef struct SpriteDecompArg SpriteDecompArg, *PSpriteDecompArg;

struct SpriteDecompArg {
    enum SpriteGroup spriteGroup;
    byte spriteSubIndex;
};

typedef struct SpriteList SpriteList, *PSpriteList;

struct SpriteList {
    byte *header;
    int length;
};

typedef struct SpriteLzDetails SpriteLzDetails, *PSpriteLzDetails;

struct SpriteLzDetails {
    byte spriteCount;
    byte field1_0x1[3];
    short indexList[8];
    struct SpriteArchive_Header *spritePtrList[8];
    void *next;
};

typedef struct SpriteObjectEntry SpriteObjectEntry, *PSpriteObjectEntry;

struct SpriteObjectEntry {
    byte tileNumber;
    sbyte x;
    sbyte y;
    byte flag1;
    byte flag2;
};

typedef struct SpriteTilesetDetail SpriteTilesetDetail, *PSpriteTilesetDetail;

struct SpriteTilesetDetail {
    struct SpriteTilesetHeader *spriteTilesetPointer;
    uint dstTileOffset;
};

typedef struct SRFReturn SRFReturn, *PSRFReturn;

struct SRFReturn {
    int newY;
    int newX;
};

typedef enum StartMenuState {
    SMS_Suspended=32,
    SMS_SubMenuOpen=64,
    SMS_StartMenuOpen=128
} StartMenuState;

typedef struct Struct_2000E80 Struct_2000E80, *PStruct_2000E80;

struct Struct_2000E80 {
    byte inventory[64];
    byte field1_0x40[24];
    byte field2_0x58[8];
    byte hpMemoryCount;
    byte field4_0x61;
    byte field5_0x62;
    byte field6_0x63;
    byte field7_0x64;
    byte bugFragCount;
    byte field9_0x66;
    byte field10_0x67;
    int field11_0x68;
    int field12_0x6c;
    byte field13_0x70[48];
};

typedef struct Struct_F79A4 Struct_F79A4, *PStruct_F79A4;

struct Struct_F79A4 {
    int *addr;
    ushort s4;
    ushort s6;
};

typedef struct TargetPosXZ TargetPosXZ, *PTargetPosXZ;

struct TargetPosXZ {
    int x;
    int z;
};

typedef enum TextOption {
    TF_AllOptions=15,
    TF_Unused=16,
    TF_Flag_20=32,
    TF_DisableInput=64,
    TF_ClearDialogBox=128
} TextOption;

typedef struct TilemapReturn TilemapReturn, *PTilemapReturn;

struct TilemapReturn {
    int tilemapEntryBG1;
    int tilemapEntryBG2;
    int tilemapEntryBG3;
};

typedef enum WaitDmaFlag {
    WF_DMA_0=1,
    WF_DMA_1=2,
    WF_DMA_2=4,
    WF_DMA_3=8
} WaitDmaFlag;

#endif
