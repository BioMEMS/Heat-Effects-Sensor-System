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

#ifndef _HeartRate3Click_h

#define _HeartRate3Click_h
#include <Arduino.h>

typedef enum
{
    SLAVE = 0x58,
    SAMPLELED2ST = 0x01,
    SAMPLELED2END = 0x02,
    LED1ST = 0x03,
    LED1END = 0x04,
    SAMPLEAMB2LED3ST = 0x05,
    SAMPLEAMB2LED3END = 0x06,
    SAMPLELED1ST = 0x07,
    SAMPLELED1END = 0x08,
    LED2ST = 0x09,
    LED2END = 0x0A,
    SAMPLEAMB1ST = 0x0B,
    SAMPLEAMB1END = 0x0C,
    CONVERTLED2ST = 0x0D,
    CONVERTLED2END = 0x0E,
    CONVERTAMB2LED3ST = 0x0F,
    CONVERTAMB2LED3END = 0x10,
    CONVERTLED1ST = 0x11,
    CONVERTLED1END = 0x12,
    CONVERTAMB1ST = 0x13,
    CONVERTAMB1END = 0x14,
    ADCRST0ST = 0x15,
    ADCRST0END = 0x16,
    ADCRST1ST = 0x17,
    ADCRST1END = 0x18,
    ADCRST2ST = 0x19,
    ADCRST2END = 0x1A,
    ADCRST3ST = 0x1B,
    ADCRST3END = 0x1C,
    PRF = 0x1D,
    CTRL1 = 0x1E, //Timer enable and ADC averaging
    TIAGAIN1 = 0x20,
    TIAGAIN2 = 0x21,
    LEDCTRL = 0x22,
    DYNAMIC = 0x23, //Set dynamic power down modes
    CLKDIV = 0x29,
    LED2VAL = 0x2A,
    AMB2LED3VAL = 0x2B,
    LED1VAL = 0x2C,
    AMB1VAL = 0x2D,
    LED2AMB2VAL = 0x2E,
    LED1AMB1VAL = 0x2F,
    CTRL2 = 0x31,
    PWDNST = 0x32,
    PWDNEND = 0x33,
    PROGST = 0x34,
    PROGEND = 0x35,
    LED3ST = 0x36,
    LED3END = 0x37,
    PRFCLKDIV = 0x39, //Clock divisor for PRF
    DACOFF = 0x3A, //DAC offset
} AFE_Registers;


class HeartRate3Click
{
    public:
        HeartRate3Click();
        void begin(uint8_t address);
        void configAFE(void);
        void RunSequence(void);
        float RedVal();
        float IRVal();
        float AmbVal();

    private:
        void Eight();
        void Sixteen(void);
        void TwentyFour(void);
        void ThirtySix(void);
        void writeData(uint8_t pointer, uint8_t msb, uint8_t mb, uint8_t lsb);
        float readData(uint8_t pointer);
        uint8_t _address;

};

#endif
