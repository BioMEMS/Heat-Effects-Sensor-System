/*
This is one of the libraries for the Heat Effects Sensor System. More information can be found in the journal article:
Pham S, Yeap D, Escalera G, Basu R, Wu X, Kenyon NJ, Hertz-Picciotto I, Ko M, Davis CE*. (2020) Wearable sensor system to monitor physical activity and the physiological effects of heat exposure. Sensors 20(3): 855. DOI: 10.3390/s20030855


This code is the proprietary property of The Regents of the University of California (“The Regents.”) Copyright © 2020 The Regents of the University of California, Davis campus. All Rights Reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted by nonprofit, research institutions for research use only, provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The name of The Regents may not be used to endorse or promote products derived from this software without specific prior written permission.

The end-user understands that the program was developed for research purposes and is advised not to rely exclusively on the program for any reason.

THE SOFTWARE PROVIDED IS ON AN "AS IS" BASIS, AND THE REGENTS HAVE NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS. THE REGENTS SPECIFICALLY DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES, INCLUDING BUT NOT LIMITED TO PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, LOSS OF USE, DATA OR PROFITS, OR BUSINESS INTERRUPTION, HOWEVER CAUSED AND UNDER ANY THEORY OF LIABILITY WHETHER IN CONTRACT, STRICT LIABILITY OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. If you do not agree to these terms, do not download or use the software. This license may be modified only in a writing signed by authorized signatory of both parties. For commercial license information please contact copyright@ucdavis.edu.

*/

#include <Wire.h>
#include "HeartRate3Click.h"

HeartRate3Click::HeartRate3Click()
{
}

void HeartRate3Click::begin(uint8_t address)
{
    _address = address;
    Wire.begin(_address);

}

/*              Configure               */

void HeartRate3Click::configAFE(void)
{
    writeData(0x00, 0x00, 0x00, 0x00); //Set Write Bit
    writeData(DYNAMIC, 0x12, 0x42, 0x18); // Use internal oscillator and set dynamic modes, 100mA current control
    // Sixteen(); // Set LED current 16 mA
    Eight();
    writeData(TIAGAIN1, 0x00, 0x80, 0x15); // 10k, 10pF
    writeData(TIAGAIN2, 0x00, 0x00, 0x05); // 10k , 10pF
    writeData(CTRL1, 0x00, 0x01, 0x04); // Enable Timer, 4 averages
    writeData(PRF, 0x00, 0x9C, 0x3F); // Set PRF to 50Hz
    writeData(PRFCLKDIV, 0x00, 0x00, 0x04); // Divide clock by 2
    // writeData(DACOFF, 0x0C, 0x00, 0x18); // LED 2 & 3 = - 4.0 uA
    // writeData(DACOFF, 0x0E, 0x00, 0x1C); // LED 2 & 3 = - 6.0 uA
    writeData(DACOFF, 0x0F, 0x00, 0x1E); // LED 2 & 3 = - 7.0 uA
}

/*              LED Sampling/Conversion               */

void HeartRate3Click::RunSequence(void)
{
    writeData(LED2ST, 0x00, 0x00, 0x00);
    writeData(LED2END, 0x00, 0x01, 0x8F);

    writeData(SAMPLELED2ST, 0x00, 0x00, 0x50);
    writeData(SAMPLELED2END, 0x00, 0x01, 0x8F);

    writeData(ADCRST0ST, 0x00, 0x01, 0x91);
    writeData(ADCRST0END, 0x00, 0x01, 0x94);

    writeData(CONVERTLED2ST, 0x00, 0x01, 0x96);
    writeData(CONVERTLED2END, 0x00, 0x04, 0x0B);

    writeData(LED3ST, 0x00, 0x01, 0x91);
    writeData(LED3END, 0x00, 0x03, 0x20);

    writeData(SAMPLEAMB2LED3ST, 0x00, 0x01, 0xE1);
    writeData(SAMPLEAMB2LED3END, 0x00, 0x03, 0x20);

    writeData(ADCRST1ST, 0x00, 0x04, 0x0D);
    writeData(ADCRST1END, 0x00, 0x04, 0x10);

    writeData(CONVERTAMB2LED3ST, 0x00, 0x04, 0x12);
    writeData(CONVERTAMB2LED3END, 0x00, 0x06, 0x87);

    writeData(LED1ST, 0x00, 0x03, 0x22);
    writeData(LED1END, 0x00, 0x04, 0xB1);

    writeData(SAMPLELED1ST, 0x00, 0x03, 0x72);
    writeData(SAMPLELED1END, 0x00, 0x04, 0xB1);

    writeData(ADCRST2ST, 0x00, 0x06, 0x89);
    writeData(ADCRST2END, 0x00, 0x06, 0x8C);

    writeData(CONVERTLED1ST, 0x00, 0x06, 0x8E);
    writeData(CONVERTLED1END, 0x00, 0x09, 0x03);

    writeData(SAMPLEAMB1ST, 0x00, 0x05, 0x03);
    writeData(SAMPLEAMB1END, 0x00, 0x06, 0x42);

    writeData(ADCRST3ST, 0x00, 0x09, 0x05);
    writeData(ADCRST3END, 0x00, 0x09, 0x08);

    writeData(CONVERTAMB1ST, 0x00, 0x09, 0x0A);
    writeData(CONVERTAMB1END, 0x00, 0x0B, 0x7F);

    writeData(PWDNST, 0x00, 0x0D, 0x0F);
    writeData(PWDNEND, 0x00, 0x9A, 0xAF);
}

/*              LED Control               */

void HeartRate3Click::Eight(void) // Set LED current 16 mA
{
    writeData(LEDCTRL, 0x00, 0x51, 0x40);
}

void HeartRate3Click::Sixteen(void) // Set LED current 16 mA
{
    writeData(LEDCTRL, 0x01, 0x45, 0x00);
}

void HeartRate3Click::TwentyFour(void) // Set LED current 24 mA
{
    writeData(LEDCTRL, 0x01, 0xE7, 0x80);
}

void HeartRate3Click::ThirtySix(void) // Set LED current 36 mA
{
    writeData(LEDCTRL, 0x02, 0x8A, 0x00);
}

/*              Optical Values               */

float HeartRate3Click::RedVal()
{
    int32_t redval = readData(LED2VAL);
    // redval = (redval/(2^21))*1.2;
    return redval;
}

float HeartRate3Click::IRVal()
{
    int32_t irval = readData(AMB2LED3VAL);
    // irval = (irval/(2^21))*1.2;
    return irval;
}

float HeartRate3Click::AmbVal()
{
    int32_t ambval = readData(AMB1VAL);
    // ambval = (ambval/(2^21))*1.2;
    return ambval;
}

/*              Read & Write               */

void HeartRate3Click::writeData(uint8_t pointer, uint8_t msb, uint8_t mb, uint8_t lsb)
{
    Wire.beginTransmission(_address);
    Wire.write(pointer);
    Wire.write(msb);
    Wire.write(mb);
    Wire.write(lsb);
    Wire.endTransmission();
}

float HeartRate3Click::readData(uint8_t pointer)
{
    Wire.beginTransmission(_address);
    Wire.write(pointer);
    Wire.endTransmission();

    Wire.requestFrom(_address, (uint8_t)3);
    uint8_t a = Wire.read();
    uint8_t b = Wire.read();
    uint8_t c = Wire.read();

    uint32_t result = a;
    result = (result<<8) | b;
    result = (result<<8) | c;

    return result;
}
