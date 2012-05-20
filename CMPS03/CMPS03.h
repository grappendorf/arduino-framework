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

#ifndef CMPS03_H
#define CMPS03_H

#include <inttypes.h>

/**
 * This class is an interface to the CMPS03 compass sensor. It uses the I2C
 * protocol and retrieves integer values in the range [0,3600].
 */
class CMPS03
{
	public:

	/**
	 * Initialize a CMPS03.
	 *
	 * @param deviceId The 7-bit I2C device id (the default address is 0x60)
	 */
	CMPS03(uint8_t deviceId = 0x60);

	/**
	 * Read a compass value.
	 *
	 * @param The current compass value.
	 */
	unsigned int read();

	protected:

	/** The 7-bit I2C device id */
	uint8_t deviceId;
};

#endif /* CMPS03_H */
