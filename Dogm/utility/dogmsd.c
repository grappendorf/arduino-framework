/*

  dogmsd.c

  (c) 2010 Oliver Kraus (olikraus@gmail.com)
  
  This file is part of the dogm128 Arduino library.

  The dogm128 Arduino library is free software: you can redistribute it and/or modify
  it under the terms of the Lesser GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  The dogm128 Arduino library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  Lesser GNU General Public License for more details.

  You should have received a copy of the Lesser GNU General Public License
  along with dogm128.  If not, see <http://www.gnu.org/licenses/>.


*/

#include "dogm128.h"

//#ifdef DOG_REVERSE
static unsigned char dog_bit_to_mask_reverse[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
//#else
static unsigned char dog_bit_to_mask_normal[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
//#endif

unsigned char* dog_get_bit_to_mask()
{
	return dog_reverse ? dog_bit_to_mask_reverse : dog_bit_to_mask_normal;
}



