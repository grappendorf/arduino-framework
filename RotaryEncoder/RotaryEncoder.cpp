/******************************************************************************
 *  RotaryEncoder.cpp - Arduino library for reading RotaryEncoder encoders.
 *  Version 0.90
 *  (C) SunboX
 *  See http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1205879808
 ******************************************************************************/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "RotaryEncoder.h"

extern "C"
{
#include <inttypes.h>
#include <avr/interrupt.h>
}

const int _quadrature[4][4] =
{
{ 0, 0, 0, 0 }, //  00 -> 10 is silent CW
		{ 1, 0, 0, 0 }, //  01 -> 00 is CW
		{ - 1, 0, 0, 0 }, //  10 -> 11 is CW
		{ 0, 0, 0, 0 } //  11 -> 01 is silent CW
};

RotaryEncoder * RotaryEncoder::_instance;

RotaryEncoder::RotaryEncoder (int encoderPin1, int encoderPin2, int buttonPin) :
	_encoderPin1 (encoderPin1), _encoderPin2 (encoderPin2), _buttonPin (
			buttonPin), _position (0), _min (0), _max (0), _usingmin (0),
			_usingmax (0), _buttonState (0), _buttonPrevious (0), _time (0) // constructor initializer list
{
	pinMode (encoderPin1, INPUT);
	pinMode (encoderPin2, INPUT);
	pinMode (buttonPin, INPUT);
	digitalWrite (encoderPin1, HIGH); //  activate internal pullups
	digitalWrite (encoderPin2, HIGH);
	digitalWrite (buttonPin, HIGH);

	_previous = _readEncoderPins (); //  read initial position

	TIMSK2 |= (1 << TOIE2); //  enable timer 2 overflow interrupt

	_instance = this;
}

inline int RotaryEncoder::_readEncoderPins (void)
{
	return digitalRead (_encoderPin2) << 1 | digitalRead (_encoderPin1);
}

inline int RotaryEncoder::_readButtonPin (void)
{
	return digitalRead (_buttonPin) == HIGH ? 0 : 1;
}

inline void RotaryEncoder::isr (void)
{
	//____________________________________________
	//                                Read Encoder
	int quadbits = _instance->_readEncoderPins ();

	if (quadbits != _instance->_previous)
	{
		int position = _instance->_position
				+ _quadrature[_instance->_previous][quadbits];

		//  limit to minimum if assigned
		position = _instance->_usingmin ? max(_instance->_min, position)
				: position;

		//  limit to maximum if assigned
		_instance->_position
				= _instance->_usingmax ? min(_instance->_max, position)
						: position;

		_instance->_previous = quadbits;
	}

	//____________________________________________
	//                                 Read Button
	int reading = _instance->_readButtonPin ();

	// if we just pressed the button (i.e. the input went from LOW to HIGH),
	// and we've waited long enough since the last press to ignore any noise...
	if (reading != _instance->_buttonPrevious)// && millis() - _instance->_time > 100)
	{
		_instance->_buttonState = reading;

		// ... and remember when the last button press was
		//_instance->_time = millis();
	}

	_instance->_buttonPrevious = reading;
}

ISR(TIMER2_OVF_vect)
{
	RotaryEncoder::isr ();
}
