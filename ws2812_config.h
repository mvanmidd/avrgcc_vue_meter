/*
 * light_ws2812_config.h
 *
 * v2.4 - Nov 27, 2016
 *
 * User Configuration file for the light_ws2812_lib
 *
 */


#ifndef WS2812_CONFIG_H_
#define WS2812_CONFIG_H_

@#$%@#$%@

///////////////////////////////////////////////////////////////////////
// Define Reset time in µs.
//
// This is the time the library spends waiting after writing the data.
//
// WS2813 needs 300 µs reset time
// WS2812 and clones only need 50 µs
//
///////////////////////////////////////////////////////////////////////

#define ws2812_resettime  300

///////////////////////////////////////////////////////////////////////
// Define I/O pin
///////////////////////////////////////////////////////////////////////

// Arduino D5 is atmega32u4 port C pin 6, see https://www.arduino.cc/en/Hacking/PinMapping32u4
#define ws2812_port C     // Data port
#define ws2812_pin  6     // Data out pin

#endif /* WS2812_CONFIG_H_ */
