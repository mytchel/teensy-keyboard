/* Keyboard example for Teensy USB Development Board
 * http://www.pjrc.com/teensy/usb_keyboard.html
 * Copyright (c) 2008 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard.h"
#include "matrix.h"

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

void init_pins(void) {
	uint8_t i;

	for (i = 0; i < NROWS; i++) {
		*row_ddr[i]  |= row_bit[i];
		*row_port[i] |= row_bit[i];
	}

	for (i = 0; i < NCOLS; i++) {
		*col_ddr[i]  &= ~col_bit[i];
		*col_port[i] |= col_bit[i];
	}
}

int main(void)
{
	uint8_t i, j, k;
	uint8_t row, col;
	uint8_t nkeys, keys[12];
	bool function_pressed;

	// set for 16 MHz clock
	CPU_PRESCALE(0);
	
	init_pins();

	// Initialize the USB, and then wait for the host to set configuration.
	// If the Teensy is powered without a PC connected to the USB port,
	// this will wait forever.
	usb_init();
	while (!usb_configured()) /* wait */ ;

	// Wait an extra second for the PC's operating system to load drivers
	// and do whatever it does to actually be ready for input
	_delay_ms(100);

	while (1) {
		nkeys = 0;
		for (row = 0; row < NROWS && nkeys < 12; row++) {
			*row_port[row] &= ~row_bit[row];
	
			for (col = 0; col < NCOLS && nkeys < 12; col++) {
				if ((*col_pin[col] & col_bit[col]) == 0) {
					keys[nkeys++] = col * NROWS + row;
				}
			}
		
			*row_port[row] |= row_bit[row];
		}

		function_pressed = false;
		for (i = 0; i < nkeys; i++)
			for (j = 0; j < NFUNCTION_KEYS; j++)
				if (keys[i] == key_fn[j])
					function_pressed = true;
		
		keyboard_modifier_keys = 0;
		for (k = 0; k < 6; k++)
			keyboard_keys[k] = 0;

		k = 0;
		for (i = 0; i < nkeys; i++) {
       			if (modifiers[keys[i]]) {
				keyboard_modifier_keys |= layout_nm[keys[i]];
			} else {
				if (function_pressed)
					keyboard_keys[k++] = layout_fn[keys[i]];
				else
					keyboard_keys[k++] = layout_nm[keys[i]];
			}
		}
		
		usb_keyboard_send();
	}
}
