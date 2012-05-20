/*
	Nokia_lcd.h
*/

#ifndef NOKIALCD_H
#define NOKIALCD_H

#include <inttypes.h>
#include "PCF8833.h"


class Nokia_lcd
{
  public:
  
  	Nokia_lcd();
	void cLCD_Init(void);
	void cLCD_GotoXY(unsigned char x, unsigned char y);
	void cLCD_Pixel(unsigned char x, unsigned char y, int color);
	void cLCD_Line(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color);
	void cLCD_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char fill, int color);
	void cLCD_Circle(unsigned char x0, unsigned char y0, unsigned char radius, int color);
	void cLCD_Char(char c, unsigned char x, unsigned char y, int fColor, int bColor);
	void cLCD_String(char *pString, unsigned char  x, unsigned char  y,  int fColor, int bColor);
	void cLCD_Bitmap(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data);
	void cLCD_Bitmap_Datbuf_Start(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size);
	void cLCD_Bitmap_Datbuf(unsigned char *bitmap_data, int len);
};	
		
#endif

