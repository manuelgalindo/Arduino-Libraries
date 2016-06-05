/*Example of GPS library with NMEA 0183
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

#include <GPS.h>


GPS gps(Serial1); //Set Serial port(Serial1,Serial2,Serial3 only available on Arduino Mega)
GPSDATA gpsdata; //Create variable from struct to get GPS data

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  gps.begin(9600); //Set GPS port baudrate and start it
}

void loop() {
  gps.read();                   //Pool GPS change
  if (gps.update()) {           //In change event
    gpsdata = gps.read();       //Get GPS data

    //Print captured data
    Serial.print("Time:");
    Serial.print(gpsdata.time);
    Serial.print("  Date:");
    Serial.print(gpsdata.date);
    Serial.print("  Latitude:");
    Serial.print(gpsdata.lat);
    Serial.print("  Longitude:");
    Serial.println(gpsdata.lon);
    Serial.print("Altitude:");
    Serial.print(gpsdata.alt);
    Serial.print("  Sats:");
    Serial.print(gpsdata.sats);
    Serial.print("  Status:");
    Serial.print(gpsdata.fix);
    Serial.print("  Valid:");
    Serial.print(gpsdata.valid);
    Serial.print("  Course:");
    Serial.print(gpsdata.course_h);
    Serial.print("  Speed(Km/h):");
    Serial.println(gpsdata.speed_h);
    Serial.println();
    
    gps.clear();                //Clear GPS flag
  }

}



