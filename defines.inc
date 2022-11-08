;
; NES defines and macros
;

; PPU registers

.define PPU_CONTROL	$2000
.define PPU_MASK	$2001
.define PPU_STATUS	$2002
.define OAM_ADDR	$2003
.define OAM_DATA	$2004
.define PPU_SCROLL	$2005
.define PPU_ADDR	$2006
.define PPU_DATA	$2007
.define OAM_TRANSFER	$4014

; PPU_CONTROL bits
.define PPU_ENABLE_NMI	%10000000	; enable NMI interrupt
.define PPU_SLAVE	%01000000	; master/slave select (idk what this does)
.define PPU_TALL_SPRITE	%00100000	; enable 8x16 sprites
.define PPU_BG_HIGH	%00010000	; background tiles are in the high bank
.define PPU_SPR_HIGH	%00001000	; sprite tiles are in the high bank (ignored in 8x16)
.define PPU_DATA_ROW	%00000100	; PPU_DATA increments by row

; PPU_MASK bits
.define PPU_GRAYSCALE	%00000001
.define PPU_MASK_BG	%00000010
.define PPU_MASK_SPR	%00000100
.define PPU_SHOW_BG	%00001000
.define PPU_SHOW_SPR	%00010000
.define PPU_HIGH_RED	%00100000
.define PPU_HIGH_GREEN	%01000000
.define PPU_HIGH_BLUE	%10000000

.macro ppu_wait_for_vblank
:	bit PPU_STATUS
	bpl :-
.endmacro

.macro ppu_addr_set addr
	bit PPU_STATUS	; reset latch
	
	lda #>addr
	sta PPU_ADDR

	lda #<addr
	sta PPU_ADDR
.endmacro

.macro ppu_scroll_set xpos, ypos
	bit PPU_STATUS	; reset register

	lda #xpos
	sta PPU_SCROLL

	lda #ypos
	sta PPU_SCROLL
.endmacro

.macro oam_sprite index, tile, xpos, ypos, attr
	lda ypos
	sta $0200 + (4 * index)
	lda tile
	sta $0200 + (4 * index) + 1
	lda attr
	sta $0200 + (4 * index) + 2
	lda xpos
	sta $0200 + (4 * index) + 3
.endmacro

.define SPR_PRIORITY	%00100000
.define SPR_FLIP_H	%01000000
.define SPR_FLIP_V	%10000000


; PPU memory addresses

.define PATTERN_TABLE_0	$0000
.define PATTERN_TABLE_1	$1000

.define NAMETABLE_0	$2000
.define NAMETABLE_1	$2400
.define NAMETABLE_2	$2800
.define NAMETABLE_3	$2C00

.define PALETTE_TILES	$3F00
.define PALETTE_SPRITES	$3F10


; APU

.define SQ1_VOLUME	$4000
.define SQ1_SWEEP	$4001
.define SQ1_LOWBYTE	$4002
.define SQ1_HIGHBYTE	$4003

.define SQ2_VOLUME	$4004
.define SQ2_SWEEP	$4005
.define SQ2_LOWBYTE	$4006
.define SQ2_HIGHBYTE	$4007

.define TRI_LINEAR	$4008
.define TRI_LOWBYTE	$400A
.define TRI_HIGHBYTE	$400B

.define NOISE_VOLUME	$400C
.define NOISE_LOWBYTE	$400E
.define NOISE_HIGHBYTE	$400F

.define DMC_FREQ	$4010
.define DMC_SAMPLE	$4011
.define DMC_START	$4012
.define DMC_LENGTH	$4013

.define SOUND_CHANNELS	$4015
.define JOYSTICK_LATCH	$4016
.define JOYSTICK1	$4016
.define FRAME_COUNTER	$4017
.define JOYSTICK2	$4017


; Controllers

.define BUTTON_A	1 << 7
.define BUTTON_B	1 << 6
.define BUTTON_SELECT	1 << 5
.define BUTTON_START	1 << 4
.define BUTTON_UP	1 << 3
.define BUTTON_DOWN	1 << 2
.define BUTTON_LEFT	1 << 1
.define BUTTON_RIGHT	1 << 0
