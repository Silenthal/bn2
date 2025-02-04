#include "offsets.h"
    .include "constants.inc"
    .include "macros.inc"

@ Start: 0x1E597C


@@ Copies onscreen tilemap entries from a given tilemap list to the screen
@@ buffer in a horizontal line.
@@ In:
@@ r0: x - The X coordinate of the target screen.
@@ r1: y - The Y coordinate of the target screen.
@@ r2: screen - The screen to draw to.
@@ r3: entryList - The list of tilemap entries.
@@ r4: entryListSz - The size of the tilemap entry list.
_fts Screen_SafeCopyTileMapH
    mov        r6,r10
    ldr        r6,[r6,#0x5c]
    lsl        r2,r2,#0xb
    add        r6,r6,r2
    lsl        r1,r1,#0x6
    add        r6,r6,r1
    mov        r2,#0x1f
    mvn        r2,r2
LAB_0300648c:
    tst        r0,r2
    bne        LAB_03006496
    ldrh       r7,[r3,#0x0]
    lsl        r1,r0,#0x1
    strh       r7,[r6,r1]
LAB_03006496:
    add        r0,#0x1
    add        r3,#0x2
    sub        r4,#0x1
    cmp        r4,#0x0
    bgt        LAB_0300648c
    mov        pc,lr


@@ Copies onscreen tilemap entries from a given tilemap list to the screen
@@ buffer in a vertical line.
@@ In:
@@ r0: x - The X coordinate of the target screen.
@@ r1: y - The Y coordinate of the target screen.
@@ r2: screen - The screen to draw to.
@@ r3: entryList - The list of tilemap entries.
@@ r4: entryListSz - The size of the tilemap entry list.
_fts Screen_SafeCopyTileMapV
    mov        r6,r10
    ldr        r6,[r6,#0x5c]
    lsl        r2,r2,#0xb
    add        r6,r6,r2
    lsl        r0,r0,#0x1
    add        r6,r6,r0
    mov        r2,#0x1f
    mvn        r2,r2
LAB_030064b4:
    tst        r1,r2
    bne        LAB_030064be
    ldrh       r7,[r3,#0x0]
    lsl        r0,r1,#0x6
    strh       r7,[r6,r0]
LAB_030064be:
    add        r1,#0x1
    add        r3,#0x2
    sub        r4,#0x1
    cmp        r4,#0x0
    bgt        LAB_030064b4
    mov        pc,lr


@@ Copies onscreen tilemap entries from a given tilemap list to the screen
@@ buffer in a rectangle.
@@ In:
@@ r0: x - The X coordinate of the target screen.
@@ r1: y - The Y coordinate of the target screen.
@@ r2: screen - The screen to draw to.
@@ r3: entryList - The list of tilemap entries.
@@ r4: width - The width of the rectangle.
@@ r5: height - The height of the rectangle.
_fts Screen_SafeCopyTileMapRect
    mov        r6,r10
    ldr        r6,[r6,#0x5c]
    lsl        r2,r2,#0xb
    add        r6,r6,r2
    add        r4,r4,r0
    add        r5,r5,r1
LAB_030064d8:
    push       {r0}
LAB_030064da:
    mov        r2,#0x1f
    mvn        r2,r2
    add        r7,r0,#0x0
    orr        r7,r1
    tst        r7,r2
    bne        LAB_030064f0
    lsl        r7,r0,#0x1
    lsl        r2,r1,#0x6
    add        r2,r2,r7
    ldrh       r7,[r3,#0x0]
    strh       r7,[r6,r2]
LAB_030064f0:
    add        r3,#0x2
    add        r0,#0x1
    cmp        r0,r4
    blt        LAB_030064da
    pop        {r0}
    add        r1,#0x1
    cmp        r1,r5
    blt        LAB_030064d8
    mov        pc,lr


@@ Sets all tilemap entries in a rectanglular area in a given screen buffer
@@ to the given tilemap entry.
@@ In:
@@ r0: x - The X coordinate of the target screen.
@@ r1: y - The Y coordinate of the target screen.
@@ r2: screen - The screen to draw to.
@@ r3: width - The width of the rectangle.
@@ r4: height - The height of the rectangle.
@@ r5: entry - The tilemap entry.
_fts Screen_SetTileMapRect
    mov        r6,r10
    ldr        r6,[r6,#0x5c]
    lsl        r2,r2,#0xb
    add        r6,r6,r2
    lsl        r0,r0,#0x1
    add        r6,r6,r0
    lsl        r1,r1,#0x6
    add        r6,r6,r1
    mov        r2,#0x0
    add        r1,r6,#0x0
LAB_03006518:
    strh       r3,[r6,#0x0]
    add        r6,#0x2
    add        r2,#0x1
    cmp        r2,r4
    blt        LAB_03006518
    mov        r2,#0x0
    add        r1,#0x40
    add        r6,r1,#0x0
    sub        r5,#0x1
    cmp        r5,#0x0
    bgt        LAB_03006518
    mov        pc,lr


@@ Sets all onscreen tilemap entries in a rectanglular area in a given screen
@@ buffer to the given tilemap entry.
@@ In:
@@ r0: x - The X coordinate of the target screen.
@@ r1: y - The Y coordinate of the target screen.
@@ r2: screen - The screen to draw to.
@@ r3: width - The width of the rectangle.
@@ r4: height - The height of the rectangle.
@@ r5: entry - The tilemap entry.
_fts Screen_SafeSetTileMapRect
    mov        r6,r10
    ldr        r6,[r6,#0x5c]
    lsl        r2,r2,#0xb
    add        r6,r6,r2
    add        r4,r4,r0
    add        r5,r5,r1
LAB_0300653c:
    push       {r0}
LAB_0300653e:
    mov        r2,#0x1f
    mvn        r2,r2
    add        r7,r0,#0x0
    orr        r7,r1
    tst        r7,r2
    bne        LAB_03006552
    lsl        r7,r0,#0x1
    lsl        r2,r1,#0x6
    add        r2,r2,r7
    strh       r3,[r6,r2]
LAB_03006552:
    add        r0,#0x1
    cmp        r0,r4
    blt        LAB_0300653e
    pop        {r0}
    add        r1,#0x1
    cmp        r1,r5
    blt        LAB_0300653c
    mov        pc,lr

    .byte 0, 0 @ TODO: Till following file is set
