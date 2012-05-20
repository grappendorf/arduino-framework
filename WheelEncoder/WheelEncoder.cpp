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
 * The Original Code is grappendorf.net Arduino Libraries / WheelEncoder.
 *
 * The Initial Developer of the Original Code is
 * Dirk Grappendorf (www.grappendorf.net)
 * Portions created by the Initial Developer are Copyright (C) 2008-2011
 * the Initial Developer. All Rights Reserved.
 */

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Wire/Wire.h"
#include "WheelEncoder.h"

unsigned int WheelEncoder::interval = 100;

unsigned long WheelEncoder::nextUpdate = 0;

volatile unsigned int WheelEncoder::leftDistance = 123;

volatile unsigned int WheelEncoder::rightDistance = 456;

unsigned int WheelEncoder::leftSpeed = 0;

unsigned int WheelEncoder::rightSpeed = 0;

void WheelEncoder::init()
{
	attachInterrupt(0, WheelEncoder::leftInterrupt, RISING);
	attachInterrupt(1, WheelEncoder::rightInterrupt, RISING);
}

void WheelEncoder::update()
{
	if (millis() > nextUpdate)
	{
		leftSpeed = leftDistance;
		leftDistance = 0;
		rightSpeed = rightDistance;
		rightDistance = 0;
		nextUpdate = millis() + interval;
	}
}

unsigned long WheelEncoder::getLeftSpeed()
{
	return leftSpeed;
}

unsigned long WheelEncoder::getLeftDistance()
{
	return leftDistance;
}

unsigned long WheelEncoder::getRightSpeed()
{
	return rightSpeed;
}

unsigned long WheelEncoder::getRightDistance()
{
	return rightDistance;
}

void WheelEncoder::leftInterrupt()
{
	++leftDistance;
}

void WheelEncoder::rightInterrupt()
{
	++rightDistance;
}
