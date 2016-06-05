/*GPS library with NMEA 0183 decoder
 * Tested with GP 20U7
 * Author: Manuel Galindo (mfg90@live.com)
 * Copyright (c) 2016 Manuel Galindo

 * MIT License

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.*/

#include "GPS.h"

GPS::GPS(HardwareSerial &serial){
  _serial = &serial;
}

void GPS::begin() {
  _serial->begin(9600); 
}

void GPS::begin(uint32_t baudrate) {
  _serial->begin(baudrate); 
}

GPSDATA GPS::read() {
  while (_serial->available()) {
    // get the new byte:
    char inChar = (char)_serial->read();
    inputString += inChar;
    if (inChar == '\n') {
      if (inputString.substring(0, 6) == "$GPGGA")
      {
        nmea_decode(0);
      }
      if (inputString.substring(0, 6) == "$GPRMC")
      {
        nmea_decode(1);
      }
      if (inputString.substring(0, 6) == "$GPVTG")
      {
        nmea_decode(2);
        stringComplete = true;
      }
      // clear the string:
      inputString = "";
    }
  }
  return gps;
}

bool GPS::update(){
  return stringComplete;
}

void GPS::clear(){
  stringComplete=false;
}

GPSDATA GPS::nmea_decode(uint8_t mode)
{
  int i = 0, x = 0;
  switch (mode) {
    //Global Positioning System Fixed Data (GGA)
    case 0: {
        for (int p = 0; p < 9; p++)
        {
          i = inputString.indexOf(',', x);
          x = inputString.indexOf(',', i + 1);
          String msg = inputString.substring(i + 1, x);
          switch (p) {
            case 0: {
                gps.time = msg.toFloat();
                break;
              }
            case 1: {
                int a = msg.indexOf('.');
                String out1 = msg.substring(0, a);
                String out2 = msg.substring(a + 1, a + 6);
                gps.lat = out1.toInt() * 100000;
                gps.lat = gps.lat + out2.toInt();
                break;
              }
            case 2: {
                if (msg.charAt(0) == 'S') {
                  gps.lat = gps.lat * (-1);
                }
                break;
              }
            case 3: {
                int a = msg.indexOf('.');
                String out1 = msg.substring(0, a);
                String out2 = msg.substring(a + 1, a + 6);
                gps.lon = out1.toInt() * 100000;
                gps.lon = gps.lon + out2.toInt();
                break;
              }
            case 4: {
                if (msg.charAt(0) == 'W') {
                  gps.lon = gps.lon * (-1);
                }
                break;
              }
            case 5: {
                gps.fix = msg.toInt();
                break;
              }
            case 6: {
                gps.sats = msg.toInt();
                break;
              }
            case 8: {
                gps.alt = msg.toInt();
                break;
              }
          }
        }
        break;
      }
    //Recommended Minimum Specific GNSS Data (RMC)
    case 1: {
        for (int p = 0; p < 9; p++)
        {
          i = inputString.indexOf(',', x);
          x = inputString.indexOf(',', i + 1);
          String msg = inputString.substring(i + 1, x);
          switch (p) {
            case 1: {
                if (msg.charAt(0) == 'A') {
                  gps.valid = true;
                }
                else {
                  gps.valid = false;
                }
                break;
              }
            case 8: {
                gps.date = msg.toInt();
                break;
              }
          }
        }
        break;
      }
    //Course over ground and ground speed(VTG)
    case 2: {
        for (int p = 0; p < 9; p++)
        {
          i = inputString.indexOf(',', x);
          x = inputString.indexOf(',', i + 1);
          String msg = inputString.substring(i + 1, x);
          switch (p) {
            case 0: {
                gps.course_h = msg.toFloat();
                break;
              }
            case 6: {
                gps.speed_h = msg.toFloat();
                break;
              }
          }
        }
        break;
      }
  }
}


