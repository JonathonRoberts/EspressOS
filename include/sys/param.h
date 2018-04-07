/*
 * The FUGPL License
 * ===================
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software with only one restriction. No part of
 * it may be included in software projects that are solely distributed under
 * strong copyleft restricted licenses.  This license is *NOT* GPL compatible,
 * and that is it's only restriction.
 *
 * There otherwise exists no restrictions in using this software, including
 * without other limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _PARAM_H_
#define _PARAM_H_

#define VIDEO_MEM 0xB8000
#define VIDEO_COLS 80
#define VIDEO_ROWS 25
#define TAB_SPACE 8

#define SERIAL_COLS 90

#define PIC1            0x20            /* IO base address for master PIC */
#define PIC2            0xA0            /* IO base address for slave PIC */
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)
#define PIC_EOI         0x20            /* End-of-interrupt command code */

#define ICW1_ICW4       0x01            /* ICW4 (not) needed */
#define ICW1_SINGLE     0x02            /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04            /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08            /* Level triggered (edge) mode */
#define ICW1_INIT       0x10            /* Initialization - required! */

#define ICW4_8086       0x01            /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02            /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08            /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C            /* Buffered mode/master */
#define ICW4_SFNM       0x10            /* Special fully nested (not) */

char qwertyscancode[128] =
{
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
 '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,							/* Control */
 'a','s','d','f','g','h','j','k','l',';',
 '\'', '`', 0,						/* Leftshift */
 '\\','z','x','c','v','b','n','m',',','.','/', 0,	/*Rightshift*/
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* F1 */
	0,	/* F2 */
	0,	/* F3 */
	0,	/* F4 */
	0,	/* F5 */
	0,	/* F6 */
	0,	/* F7 */
	0,	/* F8 */
	0,	/* F9 */
	0,	/* F10 */
	0,	/* Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* End */
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert */
	0,	/* Delete */
	0,   0,   0,
	0,	/* F11 */
	0,	/* F12 */
	0,	/* undefined */
};

char dvorakscancode[128] =
{
    0, 27, '1','2','3','4','5','6','7','8','9','0','[',']','\b',
 '\t','\'',',','.','p','y','f','g','c','r','l','/','=','\n',
    0,							/* Control */
 'a','o','e','u','i','d','h','t','n','s',
 '-', '`', 0,						/* Leftshift */
 '\\',';','q','j','k','x','b','m','w','v','z', 0,	/*Rightshift*/
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* F1 */
	0,	/* F2 */
	0,	/* F3 */
	0,	/* F4 */
	0,	/* F5 */
	0,	/* F6 */
	0,	/* F7 */
	0,	/* F8 */
	0,	/* F9 */
	0,	/* F10 */
	0,	/* Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* End */
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert */
	0,	/* Delete */
	0,   0,   0,
	0,	/* F11 */
	0,	/* F12 */
	0,	/* undefined */
};
char *scancode = dvorakscancode;



static int cx = 0;
static int cy = 0;
int scx = 0; /* Serial port column counter */
 #endif
