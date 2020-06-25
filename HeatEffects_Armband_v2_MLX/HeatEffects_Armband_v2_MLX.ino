/*
This is the microcontroller code for the Heat Effects Sensor System. More
information can be found in the journal article:
Pham S, Yeap D, Escalera G, Basu R, Wu X, Kenyon NJ, Hertz-Picciotto I, Ko M,
Davis CE*. (2020) Wearable sensor system to monitor physical activity and the
physiological effects of heat exposure. Sensors 20(3): 855.
DOI: 10.3390/s20030855


This code is the proprietary property of The Regents of the University of
California (“The Regents.”) Copyright © 2020 The Regents of the University of
California, Davis campus. All Rights Reserved.

Redistribution and use in source and binary forms, with or without modification,
 are permitted by nonprofit, research institutions for research use only,
 provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
    The name of The Regents may not be used to endorse or promote products
    derived from this software without specific prior written permission.

The end-user understands that the program was developed for research purposes
and is advised not to rely exclusively on the program for any reason.

THE SOFTWARE PROVIDED IS ON AN "AS IS" BASIS, AND THE REGENTS HAVE NO OBLIGATION
 TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS. THE
 REGENTS SPECIFICALLY DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING BUT
 NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE REGENTS BE
 LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, EXEMPLARY OR
 CONSEQUENTIAL DAMAGES, INCLUDING BUT NOT LIMITED TO PROCUREMENT OF SUBSTITUTE
 GOODS OR SERVICES, LOSS OF USE, DATA OR PROFITS, OR BUSINESS INTERRUPTION,
 HOWEVER CAUSED AND UNDER ANY THEORY OF LIABILITY WHETHER IN CONTRACT, STRICT
 LIABILITY OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
  THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. If you do not agree to these terms, do not
  download or use the software. This license may be modified only in a writing
  signed by authorized signatory of both parties. For commercial license
  information please contact copyright@ucdavis.edu.

*/


/**************************************************************************************

                                  Libraries

**************************************************************************************/
// RTC Libraries
#include <Time.h>
#include <TimeLib.h>

// Interval Timer Library
#include <TimerOne.h>
//#include <TimerThree.h>

// SD Libraries
#include <SD.h>
#include <SD_t3.h>

// MLX Libraries
#include <Adafruit_MLX90614.h>

// LIS2DH12 Library
#include <LIS2DH12.h>

// HeartRate3Click Library
#include <HeartRate3Click.h>

// I2C Libraries
#include <Wire.h>
#include <WireKinetis.h>

// Initialize sensors
HeartRate3Click heartrate;
LIS2DH12 accel;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int chipselect = BUILTIN_SDCARD;

// Sensor files
File tempFile;
File acFile;
File hrFile;
File gsrFile;

// HeartRate3Click Pins
const int RDY = 7;
const int RST = 8;

void setup() {
  Serial.begin(115200);

  // Initialize SD Card
  pinMode(chipselect, OUTPUT);
  SD.begin(chipselect);

  // Sync RTC
  setSyncProvider(getTeensy3Time);

  // Initialize/Configure LIS2DH12
  accel.begin(0x19);
  accel.configLIS();

  // Initialize/Configure MLX90614
  mlx.begin();

  // Initialize/Configure HeartRate3Click
  heartrate.begin(0x58);
  regReset();
  heartrate.configAFE();
  heartrate.RunSequence();
  pinMode(RDY, INPUT);
  attachInterrupt(digitalPinToInterrupt(RDY), result, RISING);

  // Timer interrupt 10Hz
  Timer1.initialize(100000);
  Timer1.attachInterrupt(ISR);

  //Timer interrupt 1 Hz
  //Timer3.initialize(1000000);
  //Timer3.attachInterrupt(ISR2);

}

void loop() {


}

/**************************************************************************************

                            Interrupt Service Routine

**************************************************************************************/

void ISR()
{

  readAccel();
  skinT();

  int gsr = analogRead(A9);
  Serial.println(gsr);

  gsrFile=SD.open("GSR.csv",FILE_WRITE);
  gsrClockDisplay();
  gsrFile.println(gsr);
  gsrFile.close();
}

/**************************************************************************************

                           Read Temperature from MAX30205

**************************************************************************************/
void skinT()
{
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  tempFile = SD.open("temp.csv", FILE_WRITE);
  if (tempFile)
  {
    tempClockDisplay();
    tempFile.println(mlx.readObjectTempC());
    tempFile.close();
  }
}

/**************************************************************************************

                           Read Acceleration from LIS2DH12

**************************************************************************************/
void readAccel()
{
 accel.startRead(0xA8);

 Wire.requestFrom(0x19,6);
 if(Wire.available())
 {
  int16_t x = (int8_t)Wire.read();
  x |= (int8_t)Wire.read()<<8;
  int16_t y = (int8_t)Wire.read();
  y |= (int8_t)Wire.read()<<8;
  int16_t z = (int8_t)Wire.read();
  z |= (int8_t)Wire.read()<<8;

  //mg Conversion for 2g scale
  x = (int32_t)x*1000/(1024*16);
  y = (int32_t)y*1000/(1024*16);
  z = (int32_t)z*1000/(1024*16);

 Serial.print("x: "); Serial.print(x);
 Serial.print(" y: "); Serial.print(y);
 Serial.print(" z: "); Serial.println(z);

 acFile = SD.open("accel.csv", FILE_WRITE);
 if(acFile)
 {
  acClockDisplay();
  acFile.print(x); acFile.print(",");
  acFile.print(y); acFile.print(",");
  acFile.print(z); acFile.println();
  acFile.close();
 }

 }

}

/**************************************************************************************

                             HeartRate3Click Functions

**************************************************************************************/
void regReset()
{
  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  delayMicroseconds(35);
  digitalWrite(RST,HIGH);
}

void result()
{
  float redval = heartrate.RedVal();
  // redval = (1.2*redval)/(pow(2,21));
  Serial.print("Red: "); Serial.print(redval); Serial.print(" ");

  float irval = heartrate.IRVal();
  // irval = (1.2*irval)/(pow(2,21));
  Serial.print("IR: "); Serial.print(irval); Serial.print(" ");

  float ambval = heartrate.AmbVal();
  // ambval = (1.2*ambval)/(pow(2,21));
  Serial.print("Ambient: "); Serial.print(ambval); Serial.print(" ");
  Serial.println();

  hrFile = SD.open("hr.csv", FILE_WRITE);
  hrClockDisplay();
  if(hrFile)
  {
    hrFile.print(redval); hrFile.print(",");
    hrFile.print(irval); hrFile.print(",");
    hrFile.println(ambval);
    hrFile.close();
  }

}

/**************************************************************************************

                                LIS2DH12 RTC Functions

**************************************************************************************/

void acClockDisplay() {
  // digital clock display of the time
  acFile.print(hour());
  acDigits(minute());
  acDigits(second());
  acFile.print(",");
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void acDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  acFile.print(":");
  if(digits < 10)
    acFile.print('0');
  acFile.print(digits);
}

/**************************************************************************************

                               MLX90614 RTC Functions

**************************************************************************************/
void tempClockDisplay() {
  // digital clock display of the time
  tempFile.print(hour());
  tempDigits(minute());
  tempDigits(second());
  tempFile.print(",");
}

//time_t getTeensy3Time()
//{
//  return Teensy3Clock.get();
//}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

//unsigned long processSyncMessage() {
//  unsigned long pctime = 0L;
//  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
//
//  if(Serial.find(TIME_HEADER)) {
//     pctime = Serial.parseInt();
//     return pctime;
//     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
//       pctime = 0L; // return 0 to indicate that the time is not valid
//     }
//  }
//  return pctime;
//}

void tempDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  tempFile.print(":");
  if(digits < 10)
    tempFile.print('0');
  tempFile.print(digits);
}

/**************************************************************************************

                                HR RTC Functions

**************************************************************************************/
void hrClockDisplay() {
  // digital clock display of the time
  hrFile.print(hour());
  hrDigits(minute());
  hrDigits(second());
  hrFile.print(",");
}

//time_t getTeensy3Time()
//{
//  return Teensy3Clock.get();
//}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

//unsigned long processSyncMessage() {
//  unsigned long pctime = 0L;
//  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
//
//  if(Serial.find(TIME_HEADER)) {
//     pctime = Serial.parseInt();
//     return pctime;
//     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
//       pctime = 0L; // return 0 to indicate that the time is not valid
//     }
//  }
//  return pctime;
//}

void hrDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  hrFile.print(":");
  if(digits < 10)
    hrFile.print('0');
  hrFile.print(digits);
}

/**************************************************************************************

                                GSR RTC Functions

**************************************************************************************/
void gsrClockDisplay() {
  // digital clock display of the time
  gsrFile.print(hour());
  gsrDigits(minute());
  gsrDigits(second());
  gsrFile.print(",");
}

//time_t getTeensy3Time()
//{
//  return Teensy3Clock.get();
//}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

//unsigned long processSyncMessage() {
//  unsigned long pctime = 0L;
//  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
//
//  if(Serial.find(TIME_HEADER)) {
//     pctime = Serial.parseInt();
//     return pctime;
//     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
//       pctime = 0L; // return 0 to indicate that the time is not valid
//     }
//  }
//  return pctime;
//}

void gsrDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  gsrFile.print(":");
  if(digits < 10)
    gsrFile.print('0');
  gsrFile.print(digits);
}
