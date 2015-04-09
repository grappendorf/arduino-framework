Arduino Framework
=================

This is a project containing the core Arduino code, a selection of third party
Arduino libraries and my own Arduino libraries.

Modifications to the original third party code is made only to make the code compile as an
Eclipse C/C++ project.

I made some bigger changes to the Dogm library. Now you can specify the display type in the
Dogm constructor, so we now have one binary library code for all display types.

Use it with Eclipse and the AVR plugin
---------------------------------------

Get the latest version of my Arduino-Eclipse project from GitHub and import it as an Eclipse project into your workspace directory.

There are some build configurations defined, all with a crystal clock 16 MHz. You can define more build configurations as needed.

Choose for example the atmega168_16000000 configuration and compile the project. You should get a libarduino.a file in the atmega168_16000000 subdirectory.

Standalone usage
----------------

Since all Makefiles are contained in the project, you can simply cd into an architecture directory and execute make.

After make has finished compiling the files, you will find the libarduino.a library in the architecture directory.

My own libraries
----------------

All of my own libraries are licensed under the GNU LESSER GENERAL PUBLIC LICENSE Version 3
You find the license at http://www.gnu.org/licenses/lgpl.html

* CMPS03
* Fader
* SRF02
* WheelEncoder
* XXBee

Arduino Core
------------

The Arduino core code is licensed under the GNU LESSER GENERAL PUBLIC LICENSE Version 3
You find the license at http://www.gnu.org/licenses/lgpl.html
You find the Arduino project at http://http://arduino.cc/

Third party libraries
--------------------- 

In case

 * i stated the wrong license
 * i stated the wrong home page
 * you want me to add your favorite library
 
please send me an email.

### Licenses

 * APACHE2 Apache License Version 2.0
  You find the license at http://www.apache.org/licenses/LICENSE-2.0
 * LGPL3 GNU LESSER GENERAL PUBLIC LICENSE Version 3
  You find the license at http://www.gnu.org/licenses/lgpl.html
 * GPL3 GNU General Public License Version 2 
  You find the license at http://www.gnu.org/licenses/gpl-3.0.html
 * GPL2 GNU General Public License Version 2 
  You find the license at http://www.gnu.org/licenses/gpl-2.0.html
 * BSD3 The BSD 3-Clause License
  You find the license at http://opensource.org/licenses/BSD-3-Clause
 * MIT License
  You find the license at http://opensource.org/licenses/MIT
 * CUSTOM A custom open source/freeware license
  See the library source code for the license text 

###  Libraries

 * Android ADK
  http://arduino.cc/en/Main/ArduinoBoardADK
  Apache2
 * Bounce 
  http://www.arduino.cc/playground/Code/Bounce  
  LGPL3
 * ClickEncoder
  https://github.com/0xPIT/encoder
  CUSTOM (MIT style)
 * CmdMessenger
  http://playground.arduino.cc//Code/CmdMessenger  
 * DallasTemperature 
  http://milesburton.com/Dallas_Temperature_Control_Library   
  GPL2 
 * Dogm
  http://code.google.com/p/dogm128/
  LGPL3 
 * EEPROM (Arduino Core)
 * EEPROMEx
  http://thijs.elenbaas.net/2012/07/extended-eeprom-library-for-arduino/
  LGPL
 * Ethernet (Arduino Core)
 * Firmata (Arduino Core)
 * FrequencyTimer2
  http://arduino.cc/playground/Code/FrequencyTimer2
  LGPL 
 * LiquidCrystal (Arduino Core)
 * LiquidCrystal440
  https://code.google.com/p/liquidcrystal440/
  GPL3
 * Matrix (Arduino Core pre 1.0) 
  http://www.wiring.org.co/reference/libraries/Matrix/index.html
 * Midi
  http://playground.arduino.cc/Main/MIDILibrary
  GPL3
 * MsTimer2
  http://arduino.cc/playground/Main/MsTimer2
  LGPL
 * Nokia_lcd
  http://www.nuelectronics.com/estore/index.php?main_page=product_info&products_id=10
  License unknown, assuming LGPL?
 * OneWire
  http://www.pjrc.com/teensy/td_libs_OneWire.html
  CUSTOM
 * PID Library / PID Autotune Library
  http://playground.arduino.cc/Code/PIDLibrary
  GPL3
 * PinChangeInt
  http://arduino.cc/playground/Main/PinChangeInt
  GPL3
 * ps2dev
  http://arduino.cc/playground/ComponentLib/Ps2mouse
  License unknown, assuming LGPL?
 * RealSIDShield
  https://github.com/atbrask/RealSIDShield
  CUSTOM
 * RotaryEncoder
  http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1205879808
  License unknown, assuming LGPL?
 * Running Average Library
  http://playground.arduino.cc/Main/runningAverage
  License unknown, assuming LGPL?
 * SD (Arduino Core)
 * Servo (Arduino Core)
 * SoftwareSerial (Arduino Core)
 * SPI (Arduino Core)
 * Sprite (Arduino Core pre 1.0) 
 * Stepper (Arduino Core)
 * Streaming
  http://arduiniana.org/libraries/streaming/
  LGPL3
 * TimerOne
  http://arduino.cc/playground/Code/Timer1
  GPL3
 * u8glib
  http://code.google.com/p/u8glib/
  BSD3
 * UsbKeyboard
  http://code.google.com/p/vusb-for-arduino/
  GPL2/GPL3/Commercial
 * WiFi_Shield
  http://arduino.cc/en/Reference/WiFi
  MIT
 * WiFlySerial
  http://arduinowifly.sourceforge.net
  LGPL
 * Wire (Arduino Core)
 * XBee
  http://code.google.com/p/xbee-arduino/
  GPL3
