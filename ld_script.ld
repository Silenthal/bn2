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
		eFrameWaitValue				= 0x6348; /* BN2 */
	} > ewram

	. = __iwram_start;
	iwram (NOLOAD) :
	{
		gScreens				= 0x0;
		interruptVector			= 0x2000;
		interruptHandlerStart	= 0x6300;
		interruptHandlerEnd		= 0x78B8;
	} > iwram

	. = __text_start;
	.text :  {
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
