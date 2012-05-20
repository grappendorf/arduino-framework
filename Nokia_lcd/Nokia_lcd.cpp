// a wrapper class for PCF8838.c , Nokia 6610 Color LCD (Philips Variant)

extern "C" {
	#include "PCF8833.h"
	#include <avr/pgmspace.h>
 
}
#include "Nokia_lcd.h"

//constructor
Nokia_lcd::Nokia_lcd(){
}

void Nokia_lcd::cLCD_Init(void){
	LCD_Init();
}

void Nokia_lcd::cLCD_GotoXY(unsigned char x, unsigned char y){
	LCD_GotoXY(x, y);
}


void Nokia_lcd::cLCD_Pixel(unsigned char x, unsigned char y, int color){
	LCD_Pixel(x,y,color);

}
void Nokia_lcd::cLCD_Line(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color) { 
	LCD_Line(x0,y0, x1,y1, color); 

}

void Nokia_lcd::cLCD_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char fill, int color) { 
	LCD_Box(x0, y0, x1, y1, fill, color);
}



void Nokia_lcd::cLCD_Circle(unsigned char x0, unsigned char y0, unsigned char radius, int color) { 
	LCD_Circle(x0,y0, radius,color);
} 

void Nokia_lcd::cLCD_Char(char c, unsigned char x, unsigned char y, int fColor, int bColor) { 
 	LCD_Char(c, y,x, fColor, bColor);
} 

void Nokia_lcd::cLCD_String(char *pString, unsigned char  x, unsigned char  y,  int fColor, int bColor) { 
	LCD_String(pString, y,x, fColor, bColor);
}

void Nokia_lcd::cLCD_Bitmap(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data) {
	LCD_Bitmap (start_x, start_y, h_size, v_size, bitmap_data);
} 
 
void Nokia_lcd::cLCD_Bitmap_Datbuf_Start(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size){
	LCD_Bitmap_Datbuf_Start(start_x, start_y, h_size, v_size);
}

void Nokia_lcd::cLCD_Bitmap_Datbuf(unsigned char *bitmap_data, int len){
	LCD_Bitmap_Datbuf(bitmap_data, len);
}