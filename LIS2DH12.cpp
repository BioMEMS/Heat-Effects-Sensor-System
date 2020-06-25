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
#include "LIS2DH12.h"

/*              Initialize               */

LIS2DH12::LIS2DH12()
{
}

void LIS2DH12::begin(uint8_t address)
{
    _address = address;
    Wire.begin(_address);
}

/*              Configure               */
void LIS2DH12::configLIS()
{
    writeData(CNTRL1, 0x27); // 10Hz, Normal mode, XYZ enabled
    writeData(CNTRL4, 0x00); // Set 2G Scale
}

/*              Acceleration Data               */
/*void LIS2DH12::Acceleration()
{
    int16_t data = readData(0xA8);
    return data;
}*/


/*              Conversion               */
int16_t LIS2DH12::xConvert(uint16_t rawX)
{
    int16_t x = (rawX*1000)/(1024*16);
    return x;
}

int16_t LIS2DH12::yConvert(uint16_t rawY)
{
    int16_t y = (rawY*1000)/(1024*16);
    return y;
}

int16_t LIS2DH12::zConvert(uint16_t rawZ)
{
    int16_t z = (rawZ*1000)/(1024*16);
    return z;
}


/*              Write Data               */
void LIS2DH12::writeData(uint8_t pointer, uint8_t data)
{
    Wire.beginTransmission(_address);
    Wire.write(pointer);
    Wire.write(data);
    Wire.endTransmission();
}

/*              Start Read               */


void LIS2DH12::startRead(uint8_t pointer)
{
    Wire.beginTransmission(_address);
    Wire.write(pointer);
    Wire.endTransmission();
}
