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
#ifndef _LIS2DH12_h
#define _LIS2DH12_h

#include <Arduino.h>

typedef enum{
    STATUS = 0x07, // Data available status
    TEMPL = 0x0C, // Temp Sensor data
    TEMPH = 0x0D, // Temp Sensor data
    WHOAMI = 0x0F, // Device ID
    CNTRL0 = 0x1E, // Disconnect SDO pullup
    TEMPCON = 0x1F, // Enable or disable temperature sensor
    CNTRL1 = 0x20, // Enable axes and select operating modes
    CNTRL2 = 0x21, // Choose high pass filters
    CNTRL3 = 0X22, // Configure interrupt modes
    CNTRL4 = 0x23, // Choose full scale
    CNTRL5 = 0x24, // Miscellaneous settings
    CNTRL6 = 0x25, // Enable interrupt pins
    REF = 0x26, // Reference value for interrupt generation
    XYZSTAT = 0x27, // Status of XYZ data
    OUTXL = 0x28, // X output
    OUTXH = 0x29, // X output
    OUTYL = 0x2A, // Y output
    OUTYH = 0x2B, // Y output
    OUTZL = 0x2C, // Z output
    OUTZH = 0x2D, // Z output
    FIFOCTRL = 0x2E, // FIFO control
    FIFOSRC = 0x2F, // FIFO source
    INT1CFG = 0x30, // Interrupt 1 configuration
    INT1SRC = 0x31, // Interrupt 1 source
    INT1THS = 0x32, // Interrupt 1 threshold
    INT1DUR = 0x33, // Interrupt 1 duration
    INT2CFG = 0x34, // Interrupt 2 configuration
    INT2SRC = 0x35, // Interrupt 2 source
    INT2THS = 0x36, // Interrupt 2 threshold
    INT2DUR = 0x37, // Interrupt 2 duration
    CLICKCFG = 0x38, // Click configuration
    CLICKSRC = 0x39, // Click source
    CLICKTHS = 0x3A, // Click threshold
    TIMELIM = 0x3B, // Click time limit
    TIMELAT = 0x3C, // Click time latency
    TIMEWIN = 0x3D, // Click time window
    ACTTHS = 0x3E, // Sleep to wake, return to sleep activation threshold
    ACTDUR = 0x3F, // Sleep to wake, return to sleep duration

} LISDH12_Registers;

class LIS2DH12
{
    public:
        LIS2DH12();
        void begin(uint8_t address);
        void configLIS();
        void startRead(uint8_t pointer);
        int16_t xConvert(uint16_t rawX);
        int16_t yConvert(uint16_t rawY);
        int16_t zConvert(uint16_t rawZ);

    private:
        void writeData(uint8_t pointer, uint8_t data);

        uint8_t _address;

};

#endif
