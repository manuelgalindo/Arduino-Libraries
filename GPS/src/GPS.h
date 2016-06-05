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

#include "Arduino.h"

struct GPSDATA {
  long lon;
  long lat;
  long time;
  long date;
  int alt;
  int sats;
  int fix;
  bool valid;
  float course_h;
  float speed_h;
};

class GPS {
  
  public:
    GPS(HardwareSerial &serial);
    
    void begin();
    void begin(uint32_t baudrate);
    GPSDATA read();
    bool update();
    void clear();

  private:
    HardwareSerial* _serial;
    String inputString = "";
    boolean stringComplete = false; 
    boolean sw_uart=false;
    GPSDATA gps;
    GPSDATA nmea_decode(uint8_t mode);
    
};

