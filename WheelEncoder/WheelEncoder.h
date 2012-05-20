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

#ifndef WHEEL_ENCODER_H
#define WHEEL_ENCODER_H

#include <inttypes.h>

/**
 */
class WheelEncoder
{
	public:

	/**
	 * Initialize the WheelEncoder.
	 */
	static void init();

	/**
	 * Update the sensor values.
	 */
	static void update();

	/**
	 * Set the update interval. Every interval miliseconds, the speed values
	 * are calculated.
	 *
	 * @param interval The update interval
	 */
	static void setInterval (unsigned int interval)
	{
		WheelEncoder::interval = interval;
	}

	/**
	 * Read the left speed value.
	 */
	static unsigned long getLeftSpeed();

	/**
	 * Read the left distance value.
	 */
	static unsigned long getLeftDistance();

	/**
	 * Read the right speed value.
	 */
	static unsigned long getRightSpeed();

	/**
	 * Read the right speed value.
	 */
	static unsigned long getRightDistance();

	protected:

	/**
	 * Interrupt routine for the left encoder.
	 */
	static void leftInterrupt();

	/**
	 * Interrupt routine for the right encoder.
	 */
	static void rightInterrupt();

	/** Update interval (milli seconds). */
	static unsigned int interval;

	/** When to perform the next speed update (milli seconds) */
	static unsigned long nextUpdate;

	/** Current left distance value. */
	static volatile unsigned int leftDistance;

	/** Current right distance value. */
	static volatile unsigned int rightDistance;

	/** Current left speed value. */
	static unsigned int leftSpeed;

	/** Current right speed value. */
	static unsigned int rightSpeed;
};

#endif /*WHEEL_ENCODER_H*/

