
#include <avr/io.h>
#include "Dogm.h"
#include <Arduino.h>


void Dogm::Init(void)
{
  is_req_init = 0;
  dog_Init(a0Pin);
}

Dogm::Dogm(uint8_t pin_a0)
{
  rot = 0;
  size = 0;
  tx = 0;
  ty = 0;
  a0Pin = pin_a0;
  is_req_init= 1;
  // why can dog_Init() not be called here... arduino will hang if this is done in the constructor
  // should be investigated some day
  // dog_Init(pin_a0);

}

Dogm::Dogm(uint8_t model, uint8_t reverse, uint8_t pin_a0)
{
  rot = 0;
  size = 0;
  tx = 0;
  ty = 0;
  a0Pin = pin_a0;
  is_req_init= 1;
  dog_model = model;
  dog_reverse = reverse;
  switch (model)
  {
	  case DOGM128_HW:
		  dog_width = 128;
		  dog_height = 64;
		  break;
	  case DOGM132_HW:
		  dog_width = 132;
		  dog_height = 32;
		  break;
	  case DOGS102_HW:
		  dog_width = 102;
		  dog_height = 64;
		  break;
  }
  dog_page_cnt = dog_height / DOG_PAGE_HEIGHT;
}

Dogm::~Dogm()
{
}

void Dogm::start(void)
{
  if ( is_req_init )
    Init();
  dog_StartPage();
}

// values between 0 and 63 allowed
void Dogm::setContrast(uint8_t val)
{
  if ( is_req_init )
    Init();
  dog_SetContrast(val);
}

void Dogm::setInvertPixelMode(uint8_t val)
{
  if ( is_req_init )
    Init();
  dog_SetInvertPixelMode(val);
}



void Dogm::xy_char_correction(uint8_t len)
{
  switch( rot )
  {
    default:
      tx += len;
      break;
    case 1:
      ty += len;
      break;
    case 2:
      tx -= len;
      break;
    case 3:
      ty -= len;
      break;
  }
}

void Dogm::drawChar(uint8_t c)
{
  xy_char_correction(dog_DrawRChar(tx, ty, rot, fptr, c));
}
void Dogm::drawStr(const char *s)
{
  xy_char_correction(dog_DrawRStr(tx, ty, rot, fptr, s));
}

