OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Start)

MEMORY {
	bios	: ORIGIN = 0x00000000, LENGTH = 16K
	ewram	: ORIGIN = 0x02000000, LENGTH = 256K
	iwram	: ORIGIN = 0x03000000, LENGTH = 32K
	io		: ORIGIN = 0x04000000, LENGTH = 1K
	palette	: ORIGIN = 0x05000000, LENGTH = 1K
	vram	: ORIGIN = 0x06000000, LENGTH = 96K
	oam		: ORIGIN = 0x07000000, LENGTH = 1K
	rom		: ORIGIN = 0x08000000, LENGTH = 8M
	sram	: ORIGIN = 0x0E000000, LENGTH = 64K
}
__ewram_start	= ORIGIN(ewram);
__ewram_end		= ORIGIN(ewram) + LENGTH(ewram);
__iwram_start	= ORIGIN(iwram);
__iwram_end		= ORIGIN(iwram) + LENGTH(iwram);
__text_start	= ORIGIN(rom);
__vram_start    = ORIGIN(vram);
__pal_start     = ORIGIN(palette);

SECTIONS {
	. = __ewram_start;
	ewram (NOLOAD) :
	{
		gWorld						= 0xDC0;
		gGameStats					= 0x1120;
		gEntityListNpc				= 0x2D80;
		gPrintBufferStart			= 0x3A88;
		gStartMenuState				= 0x4C50;
		gBitsetActor				= 0x4C54;
		gEntityBoundsList			= 0x4C60;
		gBattle						= 0x4EE0;
		gSpriteTilesetDetailCount	= 0x5F54;
		gBgAnimationTaskList		= 0x5F60;
		gBitsetAttack				= 0x6110;
		gFillValue					= 0x6250;
		gBlendSettings				= 0x6260;
		gBitsetEffect				= 0x6268;
		gTintList					= 0x6270;
		gFrameWaitValue				= 0x6348;
		gCamera						= 0x6370;
		gIsObjectXFlipped			= 0x63B8;
		gSpriteAffineDataFlag		= 0x6870;
		gListEffect					= 0x68A0;
		gOamBufferList				= 0x8724;
		gSceneCamera				= 0x8728;
		gTextHandler				= 0x8730;
		gTextOptionFlags			= 0x87C4;
		gFrameCounter				= 0x8880;
		gTextUi						= 0x89C0;
		gInput						= 0x89E0;
		gFadeSettings				= 0x9070;
		gManager					= 0x9078;
		gRngState					= 0x9080;
		gVBlankFrameCounter			= 0x9620;
		gFuncPtrBgUpdatePostLoop	= 0x9630;
		gFuncPtrBgUpdateHBlank		= 0x9634;
		gFuncPtrBgUpdatePreLoop		= 0x9638;
		gScene						= 0x9640;
		gListSpriteTilesetDetail	= 0x97A0;
		gEntityBoundsListCount		= 0x9A80;
		eDmaTransferQueueSize		= 0x9A84;
		gDisplaySettings			= 0x9AF0;
		gChipTrader					= 0x9B10;
		gPlayerAnimation			= 0x9B60;
		gMainMenu					= 0x9B80;
		gOamFreeObjectCount			= 0xA170;
		eDmaParamList				= 0xA3B0;
		gEntityListAttack			= 0xA9B0;
		gBgDataManager				= 0xC1F0;
		gBgTileDataBuffer0			= 0xD5C0;
		gSpritePalettesLoaded		= 0xE9C0;
		gSpriteTilesetOffset0		= 0xE9D0;
		gWindowSettings				= 0xEA70;
		gNpcTalkState				= 0xF0B0;
		musicPlayerInfo_13			= 0xF0C0;
		musicPlayerInfo_17			= 0xF100;
		musicPlayerInfo_0D			= 0xF140;
		musicPlayerInfo_05			= 0xF180;
		musicPlayerInfo_1E			= 0xF1C0;
		musicPlayerInfo_10			= 0xF200;
		musicPlayerInfo_09			= 0xF240;
		musicPlayerInfo_06			= 0xF280;
		musicPlayerInfo_00			= 0xF2C0;
		musicPlayerInfo_1A			= 0xF300;
		musicPlayerInfo_14			= 0xF340;
		musicPlayerInfo_18			= 0xF380;
		musicPlayerInfo_15			= 0xF3C0;
		musicPlayerInfo_12			= 0xF400;
		musicPlayerInfo_0E			= 0xF440;
		musicPlayerInfo_1C			= 0xF480;
		musicPlayerInfo_1F			= 0xF4C0;
		musicPlayerInfo_07			= 0xF500;
		musicPlayerInfo_01			= 0xF540;
		musicPlayerInfo_02			= 0xF580;
		musicPlayerInfo_0A			= 0xF5C0;
		musicPlayerInfo_19			= 0xF600;
		musicPlayerInfo_1D			= 0xF640;
		musicPlayerInfo_16			= 0xF680;
		musicPlayerInfo_0F			= 0xF6C0;
		musicPlayerInfo_0C			= 0xF700;
		musicPlayerInfo_11			= 0xF740;
		musicPlayerInfo_04			= 0xF780;
		musicPlayerInfo_1B			= 0xF7D0;
		musicPlayerInfo_08			= 0xF810;
		musicPlayerInfo_03			= 0xF850;
		musicPlayerInfo_0B			= 0xF890;
	} > ewram

	. = __iwram_start;
	iwram (NOLOAD) :
	{
		gScreens					= 0x0;
		interruptVector				= 0x2000;
		gOamAttributeList			= 0x2440;
		gSpriteContainerList		= 0x4880;
		gMPlayJumpTable				= 0x5B80;
		SoundMainRAM				= 0x5D10;
		interruptHandlerStart		= 0x6300;
		listCharShade				= 0x6DB4;
		interruptHandlerEnd			= 0x78B8;
		ptrSoundInfo				= 0x7FF0;
	} > iwram

	. = __text_start;
	.text :  {
		build/crt0.o(.text)
		build/main.o(.text)
		build/sound.o(.text)
		build/dma.o(.text)
		INCLUDE include.ld
	} > rom

	. = __pal_start;
	pal (NOLOAD) :
	{
		PAL_BG = 0;
		PAL_OBJ = 0x200;
	} > palette

	. = __vram_start;
	vram (NOLOAD) :
	{
		BG_VRAM_BASE0			= 0;
		BG_VRAM_BASE1			= 0x4000;
		BG_VRAM_BASE2			= 0x8000;
		BG_VRAM_BASE3			= 0xC000;
		BG_VRAM_SCREEN0			= 0xE000;
		OBJ_VRAM0				= 0x10000;
	} > vram

	/DISCARD/ : {
		*(.glue_7*);
		*(.vfp11_veneer);
		*(.v4_bx);
		*(.iplt);
		*(.igot.plt);
		*(.rel*);
		*(.comment);
		*(.ARM*);
	}
}
