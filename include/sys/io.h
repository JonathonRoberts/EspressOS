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

#ifndef _IO_H_
#define _IO_H_

#include "param.h"
void outb(uint16_t port, uint8_t val)
{
        __asm__ __volatile__("outb %0, %1"::"a"(val),"d"(port));
}
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__ ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
static inline void io_wait(void)
{
    /* Port 0x80 is used for 'checkpoints' during POST. */
    /* The Linux kernel seems to think it is free for use :-/ */
    __asm__ __volatile__ ( "outb %%al, $0x80" : : "a"(0) );
    /* %%al instead of %0 makes no difference.  TODO: does the register need to be zeroed? */
}
void disable_cursor()
{
        outb(0x3D4, 0x0A);
        outb(0x3D5, 0x20);
}
void move_cursor(int x, int y)
{
        uint16_t pos = y * VIDEO_COLS + x;

        outb(0x3D4, 0x0F);
        outb(0x3D5, (uint8_t) (pos & 0xFF));
        outb(0x3D4, 0x0E);
        outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void kscrollup()
{
        volatile char *video1 = (volatile char*)VIDEO_MEM;
        volatile char *video2 = (volatile char*)(VIDEO_MEM+VIDEO_COLS*2);
        int i;
        for(i=0; i<((VIDEO_COLS)*(VIDEO_ROWS-1))*2;i++)
                *video1++ = *video2++;
        move_cursor(cx, --cy);
}

void kputs( uint8_t colour, const char a )
{
        volatile char *video = (volatile char*)VIDEO_MEM+(cy*VIDEO_COLS +cx++)*2;
        *video++ = a;
        *video++ = colour;
        if(cx == VIDEO_COLS){
                cx = 0;
                cy++;
                if(cy==VIDEO_ROWS){
                        kscrollup();
                }
        }
        move_cursor(cx, cy);
}
void kprint( uint8_t colour, const char *string )
{
        volatile char *video = ((volatile char*) VIDEO_MEM+(cy*VIDEO_COLS)*2);
        int col = 0;
        while(*string) {
                switch(*string){
                        case '\t': {
                                if(col<VIDEO_COLS-TAB_SPACE){
                                        string++;
                                        do{
                                                video++;
                                                *video++ = colour;
                                                col++;
                                        }while(col%TAB_SPACE);
                                }
                                        break;
                        }
                        case '\n': {
                                video+=(VIDEO_COLS-col)*2;
                                col = 0;
                                string++;
                                if(cy++==VIDEO_ROWS){
                                        cy--;
                                        kscrollup();

                                }
                                break;
                        }
                        default:
                                *video++ = *string++;
                                *video++ = colour;
                                col++;
                }
        }
        cx = col;
        move_cursor(cx,cy);
}
void kclearscreen()
{
        move_cursor(0,0);
        cx = 0;
        cy = 0;
        int i;
        for(i=0;i<2000;i++)
                kputs(0x12,' ');
        move_cursor(0,0);
        cx = 0;
        cy = 0;
}
void ksleep(int ticks){
        while(ticks){
                io_wait();
                ticks--;
        }
}
char getScancode() {
    char c=0;
    do {
        if(inb(0x60)!=c) {
            c=inb(0x60);
            if(c>0)
                return c;
        }
    } while(1);
}

char getchar() {
        char c =  getScancode();
        ksleep(1000000);
        return c;
}
#endif
