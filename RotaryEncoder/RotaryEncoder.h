/******************************************************************************
 *  RotaryEncoder.h - Arduino library for reading RotaryEncoder encoders.
 *  Version 0.90
 *  (C) SunboX
 *  See http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1205879808
 ******************************************************************************/

#ifndef RotaryEncoder_h
#define RotaryEncoder_h

class RotaryEncoder
{
public:
	RotaryEncoder (int encoderPin1, int encoderPin2, int buttonPin);

	void minimum (int min);
	int minimum (void);
	void maximum (int max);
	int maximum (void);
	void nominimum (void);
	void nomaximum (void);

	int position (void);
	void position (int pos);

	int pressed (void);

	static void isr (void);

private:
	int _readEncoderPins (void);
	int _readButtonPin (void);
	int _encoderPin1, _encoderPin2, _buttonPin;

	volatile int _position;

	int _min, _max;
	bool _usingmin, _usingmax, _buttonState, _buttonPrevious;

	volatile int _previous, _time;

	static RotaryEncoder* _instance;
};

inline void RotaryEncoder::minimum (int min)
{
	_min = min;
	_usingmin = 1;

	//  adjust position if lower than new minimum
	//_position = max(_position, min);
	_position = _position > min ? _position : min;
}

inline int RotaryEncoder::minimum ()
{
	return _min;
}

inline void RotaryEncoder::maximum (int max)
{
	_max = max;
	_usingmax = 1;

	//  adjust position if higher than new maximum
	//_position = min(_position, max);
	_position = _position < max ? _position : max;
}

inline int RotaryEncoder::maximum ()
{
	return _max;
}

inline void RotaryEncoder::nominimum (void)
{
	_usingmin = 0;
}

inline void RotaryEncoder::nomaximum (void)
{
	_usingmax = 0;
}

inline int RotaryEncoder::position (void)
{
	return _position;
}

inline void RotaryEncoder::position (int pos)
{
	_position = pos;
}

inline int RotaryEncoder::pressed (void)
{
	return _buttonState;
}
#endif // RotaryEncoder_h
