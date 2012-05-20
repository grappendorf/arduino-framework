/*
 * This file is part of the grappendorf.net Arduino Libraries.
 *
 * The contents of this file are subject to the Apache License Version
 * 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is grappendorf.net Arduino Libraries / CMPS03.
 *
 * The Initial Developer of the Original Code is
 * Dirk Grappendorf (www.grappendorf.net)
 * Portions created by the Initial Developer are Copyright (C) 2008-2011
 * the Initial Developer. All Rights Reserved.
 */

#if ARDUINO >= 100
#include "Arduino.h"
#define WIRE_WRITE Wire.write
#define WIRE_READ Wire.read
#else
#include "WProgram.h"
#define WIRE_WRITE Wire.send
#define WIRE_READ Wire.receive
#endif
#include "Wire/Wire.h"
#include "CMPS03.h"

CMPS03::CMPS03(uint8_t deviceId)
{
	this->deviceId = deviceId;
}

unsigned int CMPS03::read ()
{
	Wire.beginTransmission(deviceId);
	WIRE_WRITE((uint8_t) 2);
	Wire.endTransmission();
	delay(1);
	Wire.requestFrom(deviceId, (uint8_t) 2);
	unsigned int value = ((unsigned int) WIRE_READ()) << 8;
	value = value + ((unsigned int) WIRE_READ());
	return value;
}
