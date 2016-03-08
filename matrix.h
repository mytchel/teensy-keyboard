#include "teensy.h"

#define NCOLS 15
#define NROWS 5
#define NKEYS (NCOLS * NROWS)

#define NFUNCTION_KEYS 2
uint8_t key_fn[NFUNCTION_KEYS] = {
	 3 * NROWS + 0,
	13 * NROWS + 0,	
};

/*
 * Sadly there isn't really any other way to do this as the modifiers
 * share the same key codes as some of the normal keys.
 */
uint8_t modifiers[NKEYS] = {
/* ROW0,	ROW1,		ROW2,		ROW3,		ROW4,		*/
 true,		true,		false,		false,		false,		/* COL0 */
 false,		false,		false,		false,		false,	 	/* COL1 */
 false,		false,		false,		false,		false,		/* COL2 */
 false,		false,		false,		false,		false,		/* COL3 */
 false,		false,		false,		false,		false,		/* COL4 */
 true,		false,		false,		false,		false,		/* COL5 */
 true,		false,		false,		false,		false,		/* COL6 */
 false,		false,		false,		false,		false,		/* COL7 */
 false,		false,		false,		false,		false,		/* COL8 */
 false,		false,		false,		false,		false,		/* COL9 */
 false,		false,		false,		false,		false,		/* COL10 */
 true,		false,		false,		false,		false,		/* COL11 */
 false,		false,		false,		false,		false,		/* COL12 */
 false,		false,		false,		false,		false,		/* COL13 */
 true,		true,		false,		false,		false,		/* COL14 */
};

uint8_t layout_nm[NKEYS] = {
/* ROW0,	ROW1,		ROW2,		ROW3,		ROW4,		*/
 KEY_LEFT_CTRL,	KEY_LEFT_SHIFT,	KEY_CAPS_LOCK,	KEY_TAB,	KEY_ESC,	/* COL0 */
 NO,		NO,		NO,		NO,		KEY_1,	 	/* COL1 */
 NO,		NO,		NO,		KEY_Q,		KEY_2,		/* COL2 */
 /*fun*/NO,	NO,		KEY_A,		KEY_W,		KEY_3,		/* COL3 */
 NO,		KEY_Z,		KEY_S,		KEY_E,		KEY_4,		/* COL4 */
 KEY_LEFT_GUI,	KEY_X,		KEY_D,		KEY_R,		KEY_5,		/* COL5 */
 KEY_LEFT_ALT,	KEY_C,		KEY_F,		KEY_T,		KEY_6,		/* COL6 */
 NO,		KEY_V,		KEY_G,		KEY_Y,		KEY_7,		/* COL7 */
 KEY_SPACE,	KEY_B,		KEY_H,		KEY_U,		KEY_8,		/* COL8 */
 NO,		KEY_N,		KEY_J,		KEY_I,		KEY_9,		/* COL9 */
 KEY_SPACE,	KEY_M,		KEY_K,		KEY_O,		KEY_0,		/* COL10 */
 KEY_RIGHT_ALT,	KEY_COMMA,	KEY_L,		KEY_P,		KEY_MINUS,	/* COL11 */
 NO,		KEY_PERIOD,	KEY_SEMICOLON,	KEY_LEFT_BRACE,	KEY_EQUAL,	/* COL12 */
 /*fun*/NO,	KEY_SLASH,	KEY_QUOTE,	KEY_RIGHT_BRACE,KEY_BACKSPACE,	/* COL13 */
 KEY_RIGHT_CTRL,KEY_RIGHT_SHIFT,KEY_ENTER,	KEY_BACKSLASH,	KEY_DELETE,	/* COL14 */
};

uint8_t layout_fn[NKEYS] = {
/* ROW0,	ROW1,		ROW2,		ROW3,		ROW4,		*/
 NO,		NO,		NO,		NO,		KEY_TILDE,	/* COL0 */
 NO,		NO,		NO,		NO,		KEY_MUTE, 	/* COL1 */
 NO,		NO,		NO,		NO,		KEY_VOLUMEDOWN,	/* COL2 */
 NO,		NO,		NO,		NO,		KEY_VOLUMEUP,	/* COL3 */
 NO,		NO,		NO,		NO,		NO,		/* COL4 */
 NO,		NO,		NO,		NO,		NO,		/* COL5 */
 NO,		NO,		KEY_PAGE_DOWN,	NO,		NO,		/* COL6 */
 NO,		NO,		KEY_HOME,	NO,		NO,		/* COL7 */
 NO,		KEY_PAGE_UP,	KEY_LEFT,	NO,		NO,		/* COL8 */
 NO,		NO,		KEY_DOWN,	NO,		NO,		/* COL9 */
 NO,		NO,		KEY_UP,		NO,		NO,		/* COL10 */
 NO,		NO,		KEY_RIGHT,	NO,		NO,		/* COL11 */
 NO,		NO,		NO,		NO,		NO,		/* COL12 */
 NO,		NO,		NO,		NO,		NO,		/* COL13 */
 NO,		NO,		NO,		NO,		NO,		/* COL14 */
};

uint8_t *const col_ddr[NCOLS] = {
	_DDRD, _DDRD, _DDRD, _DDRD, _DDRB, _DDRB, _DDRB,
	_DDRB, _DDRD, _DDRB, _DDRD, _DDRB, _DDRD, _DDRC,
	_DDRC,
};

uint8_t *const col_port[NCOLS] = {
	_PORTD, _PORTD, _PORTD, _PORTD, _PORTB, _PORTB, _PORTB,
	_PORTB, _PORTD, _PORTB, _PORTD, _PORTB, _PORTD, _PORTC,
	_PORTC,
};

uint8_t *const col_pin[NCOLS] = {
	_PIND, _PIND, _PIND, _PIND, _PINB, _PINB, _PINB,
	_PINB, _PIND, _PINB, _PIND, _PINB, _PIND, _PINC,
	_PINC,
};

uint8_t col_bit[NCOLS] = {
	1<<1, 1<<2, 1<<4, 1<<0, 1<<3, 1<<2, 1<<1,
	1<<0, 1<<7, 1<<4, 1<<5, 1<<7, 1<<3, 1<<6,
	1<<7,
};

uint8_t *const row_ddr[NROWS] = {
	_DDRB, _DDRB, _DDRF, _DDRF, _DDRF,
};

uint8_t *const row_port[NROWS] = {
	_PORTB, _PORTB, _PORTF, _PORTF, _PORTF,
};

uint8_t row_bit[NROWS] = {
	1<<5, 1<<6, 1<<7, 1<<6, 1<<5,
};
