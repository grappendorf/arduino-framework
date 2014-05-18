#if defined(__AVR_ATmega2560__)
#include "pins_arduino_mega2560.h"
#elif defined(__AVR_ATmega1284P__)
#include "pins_arduino_mega1284p.h"
#elif defined(__AVR_ATmega644P__)
#include "pins_arduino_mega644p.h"
#elif defined(__AVR_ATmega32U4__)
#include "pins_arduino_mega32u4.h"
#else
#include "pins_arduino_standard.h"
#endif
