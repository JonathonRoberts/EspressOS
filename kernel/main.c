#include <stddef.h>
#include <stdint.h>

#define VIDEO_MEM 0xB8000
#define VIDEO_COLS 80
#define VIDEO_ROWS 25
#define TAB_SPACE 8

/* Global Vars */
/* Cursor position */
int cx = 0;
int cy = 0;

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
	return getScancode();
}

int main(){
	disable_cursor();
	kclearscreen();
	kprint(0x2, "Hello world!\n");
	kprint(0x2, "Hello world!\n");
	kprint(0x2, "Implementing tabs\n1234567890\n\ttab\n123\ttab\n");
	int i;
	char c;
	while(1){
		c = getchar();
		for(i=0;i<10000000;i++);
		kputs(0x2,c);
	}
	kscrollup();
	__asm__("hlt");
	return 0;
}
