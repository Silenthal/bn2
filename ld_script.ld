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
		gChipFolders				= 0xAB0;
		gBitsetNpc					= 0xC18;
		gStylePoints				= 0xDA0;
		gWorld						= 0xDC0;
		gGameStats					= 0x1120;
		gBattleChipInventory		= 0x11B0;
		gEntityListNpc				= 0x2D80;
		gInventoryChecksumIndex		= 0x3A40;
		gStyleJudge					= 0x3A50;
		gPrintBufferStart			= 0x3A88;
		gPrintBufferEnd				= 0x3E88;
		gStartMenuState				= 0x4C50;
		gBitsetActor				= 0x4C54;
		gEntityBoundsList			= 0x4C60;
		gBattle						= 0x4EE0;
		textTileBuffer				= 0x4F90;
		gBattleDeck					= 0x5EC0;
		tempBg1Hofs					= 0x5F30;
		gSpriteTilesetDetailCount	= 0x5F54;
		gBgAnimationTaskList		= 0x5F60;
		gBitsetAttack				= 0x6110;
		gCurMapElevationData		= 0x6120;
		gTransition					= 0x6140;
		gFillValue					= 0x6250;
		gBlendSettings				= 0x6260;
		gBitsetEffect				= 0x6268;
		gBattleSpriteCount			= 0x626C;
		gTintList					= 0x6270;
		gFrameWaitValue				= 0x6348;
		gMapEventState				= 0x6350;
		gCamera						= 0x6370;
		gIsObjectXFlipped			= 0x63B8;
		gObjPaletteBuffer0			= 0x63C0;
		gObjPalette0				= 0x65C0;
		gBattleUi					= 0x67D0;
		gSpriteAffineDataFlag		= 0x6870;
		gMapChange					= 0x6880;
		gListEffect					= 0x68A0;
		gMenu						= 0x7EA0;
		gOamBufferList				= 0x8724;
		gSceneCamera				= 0x8728;
		gTextHandler				= 0x8730;
		gBitsetPlayerLocation		= 0x87C0;
		gTextOptionFlags			= 0x87C4;
		gEntityListPlayerLocation	= 0x87D0;
		gFrameCounter				= 0x8880;
		gTextUi						= 0x89C0;
		gInput						= 0x89E0;
		gFadeSettings				= 0x9070;
		gManager					= 0x9078;
		gRngState					= 0x9080;
		gBgPaletteBuffer0			= 0x9090;
		gBgPaletteBuffer1			= 0x90b0;
		gBgPaletteBuffer2			= 0x90d0;
		gBgPaletteBuffer3			= 0x90f0;
		gBgPaletteBuffer4			= 0x9110;
		gBgPaletteBuffer5			= 0x9130;
		gBgPaletteBuffer6			= 0x9150;
		gBgPaletteBuffer7			= 0x9170;
		gBgPaletteBuffer8			= 0x9190;
		gBgPaletteBuffer9			= 0x91b0;
		gBgPaletteBufferA			= 0x91d0;
		gBgPaletteBufferB			= 0x91f0;
		gBgPaletteBufferC			= 0x9210;
		gBgPaletteBufferD			= 0x9230;
		gBgPaletteBufferE			= 0x9250;
		gBgPaletteBufferF			= 0x9270;
		gBgPalette0					= 0x9290;
		gBgPalette1					= 0x92b0;
		gBgPalette2					= 0x92d0;
		gBgPalette3					= 0x92f0;
		gBgPalette4					= 0x9310;
		gBgPalette5					= 0x9330;
		gBgPalette6					= 0x9350;
		gBgPalette7					= 0x9370;
		gBgPalette8					= 0x9390;
		gBgPalette9					= 0x93b0;
		gBgPaletteA					= 0x93d0;
		gBgPaletteB					= 0x93f0;
		gBgPaletteC					= 0x9410;
		gBgPaletteD					= 0x9430;
		gBgPaletteE					= 0x9450;
		gBgPaletteF					= 0x9470;
		gVBlankFrameCounter			= 0x9620;
		gFuncPtrBgUpdatePostLoop	= 0x9630;
		gFuncPtrBgUpdateHBlank		= 0x9634;
		gFuncPtrBgUpdatePreLoop		= 0x9638;
		gScene						= 0x9640;
		gCurMapBoundaryData			= 0x9680;
		gListMapWallSegmentHistory	= 0x9698;
		gListSpriteTilesetDetail	= 0x97A0;
		gPetStatusControl			= 0x9A70;
		gEntityBoundsListCount		= 0x9A80;
		gDemo						= 0x9A88;
		gDmaParamListSize			= 0x9A84;
		gDisplaySettings			= 0x9AF0;
		gChipTrader					= 0x9B10;
		gPlayerAnimation			= 0x9B60;
		gMainMenu					= 0x9B80;
		gPlayerBattleState			= 0x9BF0;
		gBattleSpriteArgsArray		= 0x9EF0;
		gOamFreeObjectCount			= 0xA170;
		gScreenDim					= 0xA180;
		gLayoutDialogueText			= 0xA1B0;
		gDmaParamList				= 0xA3B0;
		gEntityListAttack			= 0xA9B0;
		gCurMapEventData			= 0xC1B0;
		gCurMapCoverData			= 0xC1D0;
		gBgDataManager				= 0xC1F0;
		gSpriteLzDetails			= 0xC220;
		gMpBattleChipInventory		= 0xC260;
		gStartMenu					= 0xD580;
		gBgTileDataBuffer0			= 0xD5C0;
		gBgTileDataBuffer8			= 0xD680;
		gBgTileDataBuffer1			= 0xD6E0;
		gBgTileDataBuffer9			= 0xD7C0;
		gBgTileDataBuffer2			= 0xD800;
		gBgTileDataBuffer7			= 0xD8C0;
		gBgTileDataBuffer3			= 0xD920;
		gBgTileDataBufferA			= 0xD9C0;
		gBgTileDataBuffer4			= 0xDA40;
		gBgTileDataBuffer5			= 0xDB20;
		gBgTileDataBufferD			= 0xDC60;
		gBgTileDataBufferB			= 0xDCC0;
		gBgTileDataBuffer6			= 0xDD40;
		gBgTileDataBufferC			= 0xE3C0;
		gSpritePalettesLoaded		= 0xE9C0;
		gGameOver					= 0xE9C8;
		gSpriteTilesetOffset0		= 0xE9D0;
		tempBg1Vofs					= 0xEA40;
		gWindowSettings				= 0xEA70;
		gBattleKeyStates			= 0xEA80;
		gCustomScreen				= 0xEEF0;
		gEnemyHp					= 0xEFD0;
		gFixedEncounter				= 0xEFE8;
		gBattleResult				= 0xEFF0;
		gStyleChange				= 0xF010;
		gCurPlayerPos				= 0xF020;
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
		interruptVectorHblank		= 0x2004;
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
