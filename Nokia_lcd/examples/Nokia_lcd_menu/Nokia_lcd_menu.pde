/* test program to demonstration LCD & Joystick, using a menu */
#include "Nokia_lcd.h"
#include "image.h"
#include <avr/pgmspace.h>

#define BL_PIN 8

//keypad debounce parameter
#define DEBOUNCE_MAX 15
#define DEBOUNCE_ON  10
#define DEBOUNCE_OFF 3 

#define NUM_KEYS 5

// joystick number
#define UP_KEY 3
#define LEFT_KEY 0
#define CENTER_KEY 1
#define DOWN_KEY 2
#define RIGHT_KEY 4

// adc preset value, represent top value,incl. noise & margin,that the adc reads, when a key is pressed
// set noise & margin = 30 (0.15V@5V)
int  adc_key_val[NUM_KEYS] ={30, 128, 260, 374, 515 };


// debounce counters
byte button_count[NUM_KEYS];
// button status - pressed/released
byte button_status[NUM_KEYS];
// button on flags for user program 
byte button_flag[NUM_KEYS];


#define MENU_X	25
#define MENU_Y	50
#define ITEM_H		10

#define BACKGROUND_COLOR	BLUE
#define NORMAL_FG_COLOR		BLUE
#define NORMAL_BK_COLOR		WHITE
#define HIGHLIGHT_FG_COLOR 	CYAN
#define HIGHLIGHT_BK_COLOR      MAGENTA
#define NUM_MENU_ITEM		4

void charmap(void);
void bitmap(void);
void colorbar(void);
void about(void);
void init_MENU(void);

// menu definition
char menu_items[NUM_MENU_ITEM][16]={
	"COLORBAR",
	"CHAR MAP",
	"BITMAP",
	"ABOUT"	
};

void (*menu_funcs[NUM_MENU_ITEM])(void) = {
	colorbar,
	charmap,
	bitmap,
	about
};

char current_menu_item;

//end of menu definition



Nokia_lcd lcd=Nokia_lcd();

void InitPort(){
  DDRB=0x2F;
}

void setup(void){

    // setup interrupt-driven keypad arrays  
   // reset button arrays
   for(byte i=0; i<NUM_KEYS; i++){
     button_count[i]=0;
     button_status[i]=0;
     button_flag[i]=0;
   }
  
  // Setup timer2 -- Prescaler/256
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
  TCCR2B = (1<<CS22)|(1<<CS21);      
  
  ASSR |=(0<<AS2);

   // Use normal mode  
   TCCR2A =0;    
     //Timer2 Overflow Interrupt Enable  
     TIMSK2 |= (0<<OCIE2A);
     TCNT2=0x6;  // counting starts from 6;  
   TIMSK2 = (1<<TOIE2);    
   
                  
 
  SREG|=1<<SREG_I;
  
  InitPort();
  //LCD_BACKLIGHT(1);
  digitalWrite(BL_PIN, HIGH);   // turn on backlight
  
  lcd.cLCD_Init();
  lcd.cLCD_Box(0,0,131,131,FILL,LIGHTBLUE);

   //menu initialization
   init_MENU();
   
   current_menu_item = 0;
   
}

void loop(void)
{
  
    byte i;
    for(i=0; i<NUM_KEYS; i++){
       if(button_flag[i] !=0){
            
            button_flag[i]=0;  // reset button flag
			switch(i){

				case UP_KEY:
					// current item to normal display
					lcd.cLCD_String(menu_items[current_menu_item], MENU_X, MENU_Y + current_menu_item* ITEM_H, NORMAL_FG_COLOR, NORMAL_BK_COLOR );
					current_menu_item -=1;
					if(current_menu_item <0)  current_menu_item = NUM_MENU_ITEM -1;
					// next item to highlight display
					lcd.cLCD_String(menu_items[current_menu_item], MENU_X, MENU_Y + current_menu_item* ITEM_H, HIGHLIGHT_FG_COLOR, HIGHLIGHT_BK_COLOR );
					break;
				case DOWN_KEY:
				// current item to normal display
					lcd.cLCD_String(menu_items[current_menu_item], MENU_X, MENU_Y + current_menu_item* ITEM_H, NORMAL_FG_COLOR, NORMAL_BK_COLOR );
					current_menu_item +=1;
					if(current_menu_item >(NUM_MENU_ITEM-1))  current_menu_item = 0;
					// next item to highlight display
					lcd.cLCD_String(menu_items[current_menu_item], MENU_X, MENU_Y + current_menu_item* ITEM_H, HIGHLIGHT_FG_COLOR, HIGHLIGHT_BK_COLOR );
					break;
				case LEFT_KEY:
                                     init_MENU();
					current_menu_item = 0;
					break;   
				case RIGHT_KEY:
                                         lcd.cLCD_Box(0,0,131,131,FILL,0x0FF);
				        (*menu_funcs[current_menu_item])();
                                          lcd.cLCD_Box(0,0,131,131,FILL,0xAEE);     
                                       init_MENU();
					current_menu_item = 0;           
					break;	
			}
				
		}
    }
	
 
}

         
// waiting for center key press
void waitfor_OKkey(){
  byte i;
  byte key = 0xFF;
	while (key!= CENTER_KEY){
    for(i=0; i<NUM_KEYS; i++){
       if(button_flag[i] !=0){
           button_flag[i]=0;  // reset button flag
           if(i== CENTER_KEY) key=CENTER_KEY;
        }
     }
   }
		
}

void charmap(){
  byte i,j;
  lcd.cLCD_Box(10, 5, 120,  110, FILL, WHITE);  // OK button
  for(i=0; i<10; i++){
    for(j=0; j<10; j++){
      if(i*10+j<97){
        lcd.cLCD_Char(i*10+j+0x1F,  j*10+15, i*10+10, BLACK, CYAN);
      }
    }
  }
  lcd.cLCD_Box(50, 115, 80, 127, FILL, BLUE);  // OK button
  lcd.cLCD_String("OK", 56, 117, WHITE, BLUE);
  waitfor_OKkey();
      
}

void bitmap(){
  unsigned char *pbitmap;
  byte image_h, image_w;
  pbitmap = image;
  
  image_w = pgm_read_byte(pbitmap+1);
  image_h = pgm_read_byte(pbitmap+2);

  lcd.cLCD_Bitmap(35, 20, image_w, image_h, pbitmap+5);
  
  lcd.cLCD_Box(50, 90, 80, 102, FILL, BLUE);  // OK button
  lcd.cLCD_String("OK", 56, 92, WHITE, BLUE);
  waitfor_OKkey();
}
// definition of menu functions, CENTER key to return
void colorbar(){

  byte i;
  	int color[8]={
       WHITE, BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW 
    };
  char color_name[8][7]={
	"WHITE",
	"BLACK",
	"RED",
	"GREEN",
	"BLUE",
	"CYAN",
	"MAGENT",
	"YELLOW",
	};
	
	for(i=0; i<8; i++){
		lcd.cLCD_Box(10,(i+1)*10,120,(i+2)*10, FILL, color[i]);
		lcd.cLCD_String(color_name[i],30,(i+1)*10+2, WHITE, color[i] );
	}	
	lcd.cLCD_Box(50, 100, 80, 112, FILL, BLUE);  // OK button
	lcd.cLCD_String("OK", 56, 102, WHITE, BLUE);
	
  waitfor_OKkey();	
}

void menu_action() {

	lcd.cLCD_Box(20, 30, 110, 100, FILL, WHITE);  // dialog box
	lcd.cLCD_Box(50, 80, 80, 92, FILL, BLUE);  // OK button
	lcd.cLCD_String("OK", 56, 82, WHITE, BLUE);
	lcd.cLCD_String("Use Your", 30, 50, BLACK, WHITE);  
	lcd.cLCD_String("Func Here", 30, 60, BLACK,WHITE); 
	waitfor_OKkey();

}	
void about(){
	lcd.cLCD_Box(10, 30, 120, 100, FILL, WHITE);  // dialog box
	lcd.cLCD_Box(50, 80, 80, 92, FILL, BLUE);  // OK button
	lcd.cLCD_String("OK", 56, 82, WHITE, BLUE);
	lcd.cLCD_String("Nuelectronics", 12, 50, BLACK, WHITE);  
	lcd.cLCD_String("Nokia LCD6610", 12, 64, BLACK, WHITE); 
	waitfor_OKkey();
	
		
}
void init_MENU(void){

	byte i;
	
        lcd.cLCD_Box(0,0, 131,131, FILL, RED);
        lcd.cLCD_Box(10,10, 121,121, FILL, BLACK);
        lcd.cLCD_Box(MENU_X-5, MENU_Y-20, MENU_X+85, MENU_Y+45, FILL, WHITE);
        lcd.cLCD_Box(MENU_X-5, MENU_Y-20, MENU_X+85, MENU_Y-5, FILL, BLUE);
        lcd.cLCD_String("Main Menu", MENU_X+5, MENU_Y-18, WHITE, BLUE);
	lcd.cLCD_String(menu_items[0], MENU_X, MENU_Y, HIGHLIGHT_FG_COLOR, HIGHLIGHT_BK_COLOR );

	
	for (i=1; i<NUM_MENU_ITEM; i++){
		lcd.cLCD_String(menu_items[i], MENU_X, MENU_Y + i* ITEM_H, NORMAL_FG_COLOR, NORMAL_BK_COLOR );
	}
	
	
}
	

// The followinging are interrupt-driven keypad reading 
//  which includes DEBOUNCE ON/OFF mechanism, and continuous pressing detection


// Convert ADC value to key number
char get_key(unsigned int input)
{
	char k;
    
	for (k = 0; k < NUM_KEYS; k++)
	{
		if (input < adc_key_val[k])
		{
           
    return k;
        }
	}
    
    if (k >= NUM_KEYS)
        k = -1;     // No valid key pressed
    
    return k;
}

void update_adc_key(){
  int adc_key_in;
  char key_in;
  byte i;
  
  adc_key_in = analogRead(0);
  key_in = get_key(adc_key_in);
  for(i=0; i<NUM_KEYS; i++)
  {
    if(key_in==i)  //one key is pressed 
    { 
      if(button_count[i]<DEBOUNCE_MAX)
      {
        button_count[i]++;
        if(button_count[i]>DEBOUNCE_ON)
        {
          if(button_status[i] == 0)
          {
            button_flag[i] = 1;
            button_status[i] = 1; //button debounced to 'pressed' status
          }
		  
        }
      }
	
    }
    else // no button pressed
    {
      if (button_count[i] >0)
      {  
		button_flag[i] = 0;	
		button_count[i]--;
        if(button_count[i]<DEBOUNCE_OFF){
          button_status[i]=0;   //button debounced to 'released' status
        }
      }
    }
    
  }
}

// Timer2 interrupt routine -
// 1/(160000000/256/(256-6)) = 4ms interval

ISR(TIMER2_OVF_vect) {  
  TCNT2  = 6;
  update_adc_key();
}





