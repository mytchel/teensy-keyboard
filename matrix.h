#include "teensy.h"

#define NCOLS 15
#define NROWS 5
#define NKEYS (NCOLS * NROWS)

#define NROLL 6

#define NLAYOUTS 1

uint8_t layout0[NKEYS] = {
/* ROW0,	ROW1,		ROW2,		ROW3,		ROW4,		*/
 KEY_LEFT_CTRL,	KEY_LEFT_SHIFT,	KEY_CAPS_LOCK,	KEY_TAB,	KEY_ESC,	/* COL0 */
 NO,		NO,		NO,		NO,		KEY_1,	 	/* COL1 */
 NO,		NO,		NO,		KEY_Q,		KEY_2,		/* COL2 */
 /*fun?*/NO,	NO,		KEY_A,		KEY_W,		KEY_3,		/* COL3 */
 NO,		KEY_Z,		KEY_S,		KEY_E,		KEY_4,		/* COL4 */
 NO,	KEY_X,		KEY_D,		KEY_R,		KEY_5,		/* COL5 */
 KEY_LEFT_ALT,	KEY_C,		KEY_F,		KEY_T,		KEY_6,		/* COL6 */
 NO,		KEY_V,		KEY_G,		KEY_Y,		KEY_7,		/* COL7 */
 KEY_SPACE,	KEY_B,		KEY_H,		KEY_U,		KEY_8,		/* COL8 */
 NO,		KEY_N,		KEY_J,		KEY_I,		KEY_9,		/* COL9 */
 KEY_SPACE,	KEY_M,		KEY_K,		KEY_O,		KEY_0,		/* COL10 */
 KEY_RIGHT_ALT,	KEY_COMMA,	KEY_L,		KEY_P,		KEY_MINUS,	/* COL11 */
 NO,		KEY_PERIOD,	KEY_SEMICOLON,	KEY_LEFT_BRACE,	KEY_EQUAL,	/* COL12 */
 /*fun?*/NO,	KEY_SLASH,	KEY_QUOTE,	KEY_RIGHT_BRACE,KEY_BACKSPACE,	/* COL13 */
 KEY_RIGHT_CTRL,KEY_RIGHT_SHIFT,KEY_ENTER,	KEY_BACKSLASH,	KEY_DELETE,	/* COL14 */
};

uint8_t *layouts[NLAYOUTS] = {layout0};

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

uint8_t *const row_pin[NROWS] = {
	_PINB, _PINB, _PINF, _PINF, _PINF,
};

uint8_t row_bit[NROWS] = {
	1<<5, 1<<6, 1<<7, 1<<6, 1<<5,
};
