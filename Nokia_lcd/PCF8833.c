/* PCF8833.c  -- c program for NOkia 6610 (Philips) LCD */
/* most of the source code are extracted from James Lynch's LCD application note */

#include <avr/io.h>
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WConstants.h"
#endif
#include "PCF8833.h"
#include "FONT8x8.h"




void SendLcd_color(unsigned char color){
  
    LCD_DATA(LCDData);                     // set up first bit as command or data 

    LCD_CLK(0);							// Pull Clock LOW
    LCD_CLK(1);							// Pul Clock HIGH
    
    
   
     LCD_CLK(0);  
    SPCR |=0x50;						// Enable Hardware SPI
    SPSR |=0x1;

    SPDR = color; 						// send data
    
    while(!(SPSR & 0x80));				// wait until send complete

						// disable device CS

    SPCR &=~0x50;						// Disable Hardware SPI, this releases the SPI pins
   
	LCD_CLK(0);										// for general IO use. which is used to send the 1'st 
									// bit out
}

void SendLcd(unsigned char type, unsigned char dat) 
{
	byte i;

    LCD_DATA(type);                     // set up first bit as command or data 
    LCD_CS(0);							// Enable device CS

    LCD_CLK(0);							// Pull Clock LOW
    LCD_CLK(1);							// Pul Clock HIGH
    
    if(dat == 0x0){        // spi cannot transfer zero??
      LCD_DATA(0);
      for(i=0; i<8; i++){
      
        LCD_CLK(0);							// Pull Clock LOW
        LCD_CLK(1);	
      }
    }
    else{
    SPCR |=0x50;						// Enable Hardware SPI
    SPSR |= 0x1;
    SPDR = dat; 						// send data
    
    while(!(SPSR & 0x80));				// wait until send complete

    }

    SPCR &=~0x50;						// Disable Hardware SPI, this releases the SPI pins
										// for general IO use. which is used to send the 1'st 
      LCD_CS(1);							// disable device CS									// bit out
}




void LCD_Init(void)
{
	

    LCD_CS(1);
    LCD_CLK(0);
    LCD_DATA(0);

    LCD_RESET(1);
    delay(50);
    LCD_RESET(0);
    delay(50);
    LCD_RESET(1);
    delay(50);

    LCD_CS(1);
    LCD_CLK(1);
    LCD_DATA(1);
    delay(10);

    SendLcd(LCDCommand,SWRESET);
    delay(10);

    SendLcd(LCDCommand,SLEEPOUT);  // Sleepout
//       SendLcd(LCDCommand,INVON);  // Invert display mode
//    SendLcd(LCDCommand,BSTRON);  // BoostON
	SendLcd(LCDCommand,MADCTL);  // memory access control
    SendLcd(LCDData,0xe0);
	SendLcd(LCDCommand,SETCON);  // Set Contrast
    SendLcd(LCDData,0x40);
	delay(10);
    SendLcd(LCDCommand,DISPON);  // Display On
	
	SendLcd(LCDCommand,COLMOD);  // Set Color Mode
  
  	SendLcd(LCDData,0x03);			// 12bit per pixel
	SendLcd(LCDCommand,NOP);  // Set Color Mode

}
//*****************************************************************************
//	Name: 			GotoXY(unsigned char x, unsigned char y)
// 	Copyright:		Free to use at will & at own risk.
// 	Author: 		JCP
// 	Date: 			03.30.06 17:10
// 	Description:    Sets position to x-y location on LCD
// 	Useage:			GotoXY(param 1,param 2)
//					param 1: x direction 0-131
//					param 2: y direction 0-131
//
//	Example:		GotoXY(32,17);        
//					
//  Notes:			No bounds checking	
//*******************************************************************************
void LCD_GotoXY(unsigned char x, unsigned char y)
{
  SendLcd(LCDCommand, PASET);                           // page start/end ram
  SendLcd(LCDData,x);                                   // Start Page to display to
  SendLcd(LCDData,x);                                 // End Page to display to
  
  SendLcd(LCDCommand, CASET);                           // column start/end ram
  SendLcd(LCDData,y);                                   // Start Column to display to
  SendLcd(LCDData,y);                                 // End Column to display to
}

void LCD_Pixel(unsigned char x, unsigned char y, int color)
{
	  LCD_GotoXY(x,y);
  	SendLcd(LCDCommand,RAMWR);                             
        LCD_CS(0);
      //  SendLcd(LCDData, (unsigned char)((color>>4)& 0xff) );
      //  SendLcd(LCDData, (unsigned char)((color&0xf)<<4)|0x00 );
  	SendLcd_color( (unsigned char)((color>>4)& 0xff) );    
  	SendLcd_color( (unsigned char)((color&0xf)<<4)|0x00 );
        LCD_CS(1);
  	SendLcd(LCDCommand, NOP);
}



 
//  ************************************************************************************************* 
//      
//  Draws a line in the specified color from (x0,y0) to (x1,y1)  
//      
// Inputs:   x     =   row address (0 .. 131) 
//      y     =   column address  (0 .. 131) 
//      color =   12-bit color value  rrrrggggbbbb 
//     rrrr = 1111 full red 
//          : 
//      0000 red is off 
// 
//     gggg = 1111 full green 
//          : 
//      0000 green is off 
// 
//     bbbb = 1111 full blue 
//          : 
//      0000 blue is off 
// 
//  Returns:   nothing  
// 
//  Note:  good write-up on this algorithm in Wikipedia (search for Bresenham's line algorithm) 
//    see lcd.h for some sample color settings   
// 
//  Authors:   Dr. Leonard McMillan, Associate Professor UNC 
//      Jack Bresenham IBM, Winthrop University (Father of this algorithm, 1962) 
// 
//      Note: taken verbatim from Professor McMillan's presentation:  
//            http://www.cs.unc.edu/~mcmillan/comp136/Lecture6/Lines.html 
// 
//  *************************************************************************************************  
 
void LCD_Line(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color) { 
 
  int dy = y1 - y0; 
  int dx = x1 - x0; 
  int stepx, stepy; 
	if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; } 
  if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; } 
 
  dy <<= 1;        // dy is now 2*dy 
  dx <<= 1;        // dx is now 2*dx 
 
 
  LCD_Pixel(x0, y0, color); 
 
  if (dx > dy) { 
 		int fraction = dy - (dx >> 1);  // same as 2*dy - dx 
    while (x0 != x1) { 
 	    if (fraction >= 0) { 
 				y0 += stepy; 
        fraction -= dx;    // same as fraction -= 2*dx 
 			} 
 			x0 += stepx; 
 
      fraction += dy;    // same as fraction -= 2*dy 
      LCD_Pixel(x0, y0, color); 
    } 
 	} 
 	else { 
 		int fraction = dx - (dy >> 1); 
    while (y0 != y1) { 
 			if (fraction >= 0) { 
 				x0 += stepx; 
 				fraction -= dy; 
      } 
      y0 += stepy; 
 			fraction += dx; 
      LCD_Pixel(x0, y0, color); 
    } 
 	} 
 
} 
 
//  ***************************************************************************************** 
//  
//  Draws a rectangle in the specified color from (x1,y1) to (x2,y2) 
//  Rectangle can be filled with a color if desired  
//      
// Inputs:   x     =   row address (0 .. 131) 
//      y     =   column address  (0 .. 131) 
//      fill  =   0=no fill, 1-fill entire rectangle  
//      color =   12-bit color value for lines  rrrrggggbbbb 
//   Returns:   nothing  
// 
//   Notes: 
// 
//    The best way to fill a rectangle is to take advantage of the "wrap-around" featute 
//    built into the Philips PCF8833 controller. By defining a drawing box, the memory can 
//    be simply filled by successive memory writes until all pixels have been illuminated. 
// 
//      1.  Given the coordinates of two opposing corners (x0, y0) (x1, y1) 
//          calculate the minimums and maximums of the coordinates 
// 
//        xmin = (x0 <= x1) ? x0 : x1; 
//        xmax = (x0 > x1) ? x0 : x1; 
//        ymin = (y0 <= y1) ? y0 : y1; 
//        ymax = (y0 > y1) ? y0 : y1; 
// 
//      2. Now set up the drawing box to be the desired rectangle 
// 
//     WriteSpiCommand(PASET);   // set the row boundaries 
//     WriteSpiData(xmin); 
//     WriteSpiData(xmax); 
//     WriteSpiCommand(CASET);   // set the column boundaries 
//     WriteSpiData(ymin); 
//     WriteSpiData(ymax); 
// 
//      3. Calculate the number of pixels to be written divided by 2 
// 
//        NumPixels = ((((xmax - xmin + 1) * (ymax - ymin + 1)) / 2) + 1) 
// 
//        You may notice that I added one pixel to the formula.  
//        This covers the case where the number of pixels is odd and we  
//        would lose one pixel due to rounding error. In the case of 
//        odd pixels, the number of pixels is exact.  
//        in the case of even pixels, we have one more pixel than 
//        needed, but it cannot be displayed because it is outside 
//     the drawing box. 
// 
//        We divide by 2 because two pixels are represented by three bytes. 
//        So we work through the rectangle two pixels at a time. 
// 
//      4.  Now a simple memory write loop will fill the rectangle 
// 
//        for (i = 0; i < ((((xmax - xmin + 1) * (ymax - ymin + 1)) / 2) + 1); i++) { 
//      WriteSpiData((color >> 4) & 0xFF); 
//          WriteSpiData(((color & 0xF) << 4) | ((color >> 8) & 0xF)); 
//      WriteSpiData(color & 0xFF); 
//     } 
// 
//    In the case of an unfilled rectangle, drawing four lines with the Bresenham line 
//    drawing algorithm is reasonably efficient. 
// 
//    Author:  James P Lynch      July 7, 2007 
//  *****************************************************************************************  
 
 
 
void LCD_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char fill, int color) { 
  unsigned char   xmin, xmax, ymin, ymax; 
	int   i; 
 
 // check if the rectangle is to be filled 
  if (fill == FILL) { 
 
    // best way to create a filled rectangle is to define a drawing box 
    // and loop two pixels at a time 
    // calculate the min and max for x and y directions 
      xmin = (x0 <= x1) ? x0 : x1;  
 		xmax = (x0 > x1) ? x0 : x1; 
		ymin = (y0 <= y1) ? y0 : y1; 
		ymax = (y0 > y1) ? y0 : y1; 
 
		// specify the controller drawing box according to those limits 
		// Row address set  (command 0x2B) 
		SendLcd(LCDCommand,PASET); 
		SendLcd(LCDData,xmin); 
		SendLcd(LCDData, xmax); 
		// Column address set  (command 0x2A) 
		SendLcd(LCDCommand,CASET); 
		SendLcd(LCDData,ymin); 
		SendLcd(LCDData,ymax); 
 
		// WRITE MEMORY 
		SendLcd(LCDCommand,RAMWR); 
                
               
		// loop on total number of pixels / 2 
		for (i = 0; i < ((((xmax - xmin + 1) * (ymax - ymin + 1))/2 )+1 ); i++) { 
                  
  		  // use the color value to output three data bytes covering two pixels 
                 // SendLcd(LCDData,(color >> 4) & 0xFF ); 
  		 // SendLcd(LCDData,((color & 0xF) << 4) | ((color >> 8) & 0xF) ); 
 		 // SendLcd(LCDData, color & 0xFF); 
                   LCD_CS(0);
  		  SendLcd_color((color >> 4) & 0xFF ); 
  		  SendLcd_color(((color & 0xF) << 4) | ((color >> 8) & 0xF) ); 
 		  SendLcd_color(color & 0xFF);
                   LCD_CS(1);
		} 
              
                                  
           SendLcd(LCDCommand,NOP); 
	} 
    else { 

  // best way to draw un unfilled rectangle is to draw four lines 
 	 	LCD_Line(x0, y0, x1, y0, color); 
 	 	LCD_Line(x0, y1, x1, y1, color); 
 	 	LCD_Line(x0, y0, x0, y1, color); 
 	 	LCD_Line(x1, y0, x1, y1, color); 
  }
}

//  ************************************************************************************* 
//          LCD_Circle.c 
//  
//  Draws a line in the specified color at center (x0,y0) with radius  
//      
// Inputs:   x0     =   row address (0 .. 131) 
//      y0     =   column address  (0 .. 131) 
//      radius =   radius in pixels 
//      color  =   12-bit color value  rrrrggggbbbb 
// 
//  Returns:   nothing   
// 
//  Author:    Jack Bresenham IBM, Winthrop University (Father of this algorithm, 1962) 
// 
//         Note: taken verbatim Wikipedia article on Bresenham's line algorithm   
//          http://www.wikipedia.org 
// 
//  *************************************************************************************  
 
 
void LCD_Circle(unsigned char x0, unsigned char y0, unsigned char radius, int color) 
{ 
 
  int f = 1 - radius; 
 
  int ddF_x = 0; 
 
  int ddF_y = -2 * radius; 
  unsigned char x = 0; 
 
  unsigned char y = radius; 
 
  
 
  LCD_Pixel(x0, y0 + radius, color); 
  LCD_Pixel(x0, y0 - radius, color); 
 
  LCD_Pixel(x0 + radius, y0, color); 
 
  LCD_Pixel(x0 - radius, y0, color); 
  
 
  while (x < y) { 
 
  if (f >= 0) { 
 
   y--; 
   ddF_y += 2; 
 
   f += ddF_y; 
 
  } 
 
  x++; 
  ddF_x += 2; 
 
    f += ddF_x + 1;     
    LCD_Pixel(x0 + x, y0 + y, color); 
 
    LCD_Pixel(x0 - x, y0 + y, color); 
    LCD_Pixel(x0 + x, y0 - y, color); 
 
    LCD_Pixel(x0 - x, y0 - y, color); 
 
    LCD_Pixel(x0 + y, y0 + x, color); 
 
    LCD_Pixel(x0 - y, y0 + x, color); 
    LCD_Pixel(x0 + y, y0 - x, color); 
 
    LCD_Pixel(x0 - y, y0 - x, color); 

 } 
}

void LCD_Bitmap_Datbuf_Start(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size)
{
	// specify the controller drawing box according to those limits 
		// Row address set  (command 0x2B) 
		SendLcd(LCDCommand,PASET); 
		SendLcd(LCDData,start_x); 
		SendLcd(LCDData, start_x+h_size-1); 
		// Column address set  (command 0x2A) 
		SendLcd(LCDCommand,CASET); 
		SendLcd(LCDData,start_y); 
		SendLcd(LCDData,start_y+v_size-1); 
 
		// WRITE MEMORY 
		SendLcd(LCDCommand,RAMWR); 
}

void LCD_Bitmap_Datbuf(unsigned char *bitmap_data, int len)
{
	int i;
	LCD_CS(0);
	for(i=0; i<len; i++)
		SendLcd_color(*(bitmap_data+i));
  LCD_CS(1);
}


void LCD_Bitmap (unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data) 
{
	int i;
	unsigned char *pBitmap;
	// specify the controller drawing box according to those limits 
		// Row address set  (command 0x2B) 
		SendLcd(LCDCommand,PASET); 
		SendLcd(LCDData,start_x); 
		SendLcd(LCDData, start_x+h_size-1); 
		// Column address set  (command 0x2A) 
		SendLcd(LCDCommand,CASET); 
		SendLcd(LCDData,start_y); 
		SendLcd(LCDData,start_y+v_size-1); 
 
		// WRITE MEMORY 
		SendLcd(LCDCommand,RAMWR); 

	pBitmap = bitmap_data;                
               
		// loop on total number of pixels / 2 
		for (i = 0; i< (h_size*v_size)>>1  ; i++) { 
			unsigned char bitmap;                  

        LCD_CS(0);
        
        bitmap = pgm_read_byte(pBitmap++);
  		  SendLcd_color(bitmap);
  		  bitmap =pgm_read_byte(pBitmap++);
  		  SendLcd_color(bitmap); 
  		  bitmap =pgm_read_byte(pBitmap++);
  		  SendLcd_color(bitmap); 
  		  LCD_CS(1);
		} 
    SendLcd(LCDCommand,NOP); 
}

void LCD_Char(char c, unsigned char x, unsigned char y, int fColor, int bColor) { 
 
 int    i,j; 
 
 unsigned char   nCols; 
 
 unsigned char  nRows; 
 
 unsigned char  nBytes; 
 unsigned char   PixelRow; 
 
 unsigned char   Mask; 
 
 unsigned int   Word0; 
 
 
 unsigned char *pFont,   *pChar; 
  
  pFont = (unsigned char *)FONT8x8;   
 
  
 
  // get the nColumns, nRows and nBytes 
  nCols = pgm_read_byte(pFont); 
 
  nRows = pgm_read_byte(pFont + 1); 
 
  nBytes = pgm_read_byte(pFont + 2); 
   
  // get pointer to the last byte of the desired character 
 
  pChar = pFont + (nBytes * (c - 0x1F)); 
 
    
  // Row address set  (command 0x2B) 
 
/*SendLcd(LCDCommand,PASET); 
 
 SendLcd(LCDData,x); 
 
  SendLcd(LCDData,x + nRows - 1); 
   
   Serial.print(x + nRows - 1);
 
  // Column address set  (command 0x2A) 
 
SendLcd(LCDCommand,CASET); 
 
 SendLcd(LCDData,y); 
  SendLcd(LCDData,y + nCols - 1); 
 
  Serial.print(y + nCols -1);
 
 // WRITE MEMORY 
 
 SendLcd(LCDCommand,RAMWR); 
  */
 
  // loop on each row, working backwards from the bottom to the top 
 
  for (i = 0; i<nRows; i++) { 
 
   
    // copy pixel row from font table and then decrement row 
 
  PixelRow = pgm_read_byte(pChar++); 
  
 
  Mask = 0x80; 
 
    for (j = 0; j < nCols; j += 1) { 
   
 
      // if pixel bit set, use foreground color; else use the background color 
 
      // now get the pixel color for two successive pixels 
 
      if ((PixelRow & Mask) == 0) 
    Word0 = bColor; 
 
   else 
 
    Word0 = fColor; 
    
    LCD_Pixel( y+j,x+i, Word0);

   Mask = Mask >> 1; 
 /*     if ((PixelRow & Mask) == 0) 
 
    Word1 = bColor; 
 
   else 
    Word1 = fColor; 
 
   Mask = Mask >> 1; 
 
    
 
      // use this information to output three data bytes 
      SendLcd(LCDCommand,(Word0 >> 4) & 0xFF); 
 
      SendLcd(LCDCommand,((Word0 & 0xF) << 4) | ((Word1 >> 8) & 0xF)); 
 
   SendLcd(LCDCommand,Word1 & 0xFF); 
*/ 
  }   
 } 
 
  // terminate the Write Memory command 
 SendLcd(LCDCommand,NOP);   
} 
 
void LCD_String(char *pString, unsigned char x, unsigned char  y,  int fColor, int bColor) { 
 
       
  // loop until null-terminator is seen 
 
  while (*pString != 0x00) { 
 
 
    // draw the character 
 
    LCD_Char(*pString++, x, y, fColor, bColor);  
 
 
    // advance the y position 
 
     y=y+8;
    if (x > 131) break; 
 
 } 
} 
