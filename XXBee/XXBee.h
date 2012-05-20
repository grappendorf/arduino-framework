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
 * The Original Code is grappendorf.net Arduino Libraries / XXBee.
 *
 * The Initial Developer of the Original Code is
 * Dirk Grappendorf (www.grappendorf.net)
 * Portions created by the Initial Developer are Copyright (C) 2011
 * the Initial Developer. All Rights Reserved.
 */

#ifndef XXBEE_H
#define XXBEE_H

#include <XBee/XBee.h>

/**
 * Extension of Andrew Rapp's XBee class. Adds some convenient methods
 * that simplify working with the payload data.
 *
 * PAYLOAD_BUFFER_SIZE specifies the number of bytes in the payload buffer.
 * So you can build messages up to PAYLOAD_BUFFER_SIZE bytes.
 */
template <int PAYLOAD_BUFFER_SIZE>
class XXBee : public XBee
{
	public:

	XXBee ()
	{
		payloadPtr = payloadBuf;
	}

	/**
	 * Reset the data pointer.
	 *
	 * @param data A pointer to the new data
	 * @param length The data length
	 */
	void resetData (uint8_t *data, uint8_t length)
	{
		dataPtr = data;
		dataLength = length;
	}

	/**
	 * Check if there's more data available.
	 *
	 * @param expectedBytes The number of bytes that should be available
	 * @return True if more data is available
	 */
	bool dataAvailable (uint8_t expectedBytes)
	{
		return dataLength >= expectedBytes;
	}

	/**
	 * Check if there's more data available.
	 *
	 * @return True if more data is available
	 */
	bool dataAvailable ()
	{
		return dataAvailable (1);
	}

	/**
	 * Get the next data byte.
	 *
	 * @return The next data byte
	 */
	uint8_t getData ()
	{
		--dataLength;
		return *dataPtr++;
	}

	/**
	 * Reset the payload pointer.
	 */
	void resetPayload ()
	{
		payloadPtr = payloadBuf;
	}

	/**
	 * Write the next byte to the payload array.
	 *
	 * @param data The payload data
	 */
	void putPayload (uint8_t data)
	{
		*payloadPtr++ = data;
	}

	/**
	 * Get the current payload length.
	 *
	 * @return The playload length
	 */
	uint8_t payloadLenght ()
	{
		return payloadPtr - payloadBuf;
	}

	/**
	 * Get a pointer to the payload.
	 *
	 * @return A pointer to the payload
	 */
	uint8_t * payload ()
	{
		return payloadBuf;
	}

	/** Reusable payload array */
	uint8_t payloadBuf[PAYLOAD_BUFFER_SIZE];

	/** Payload pointer */
	uint8_t *payloadPtr;

	/** Data pointer */
	uint8_t *dataPtr;

	/** Data length */
	uint8_t dataLength;
};

#endif /* XXBEE_H */
