#include "AutomaticMode.h"
#include <Arduino.h>
#include <M5Stack.h>

#include <MycobotBasic.h>
#include <ParameterList.h>

namespace cobot
{
    byte IO_TIME_OUT = 25;
    int IO_REC_WRONG = -1;
    byte HEADER = 0xfe;
    byte FOOTER = 0xfa;
    
    AutomaticMode::AutomaticMode(MycobotBasic &myCobot)
        : AbstractMode(),
          m_mycobotBasic(myCobot),
          m_cobotFreeMove(false)
    {
    }
    void AutomaticMode::init()
    {
    }

    void AutomaticMode::process(RobotState &oldState, RobotState &newState)
    {
        readData();
    }

    bool AutomaticMode::checkHeader()
    {
        u8 bDat;
        u8 bBuf[2] = {0, 0};
        u8 Cnt = 0;

        while (true)
        {
            if (!readSerial(&bDat, 1))
                return 0;
            bBuf[1] = bBuf[0];
            bBuf[0] = bDat;

            if (bBuf[0] == HEADER && bBuf[1] == HEADER)
                break;
            ++Cnt;
            if (Cnt > 10)
                return 0;
        }
        return 1;
    }

    int AutomaticMode::readSerial(unsigned char *nDat, int nLen)
    {
        int Size = 0;
        int rec_data;
        unsigned long t_begin = millis();
        unsigned long t_use;

        while (true)
        {
            M5.update();
            if (Serial.available() > 0)
            {
                rec_data = Serial.read(); // readSerial
                Serial2.write(rec_data);
                if (rec_data != IO_REC_WRONG)
                {
                    if (nDat)
                        nDat[Size] = rec_data;
                    ++Size;
                    t_begin = millis();
                }
                if (Size >= nLen)
                    break;
                t_use = millis() - t_begin;
                if (t_use > IO_TIME_OUT)
                    break;
            }
            // read serial 2
            if (Serial2.available() > 0)
            {                                 // If anything comes in Serial 2
                Serial.write(Serial2.read()); // read it and send it out Serial (USB)
            }
        }
        return Size;
    }

    void AutomaticMode::rFlushSerial()
    {
        while (Serial.read() != -1)
            ;
    }

    int AutomaticMode::readData()
    {
        rFlushSerial();
        if (!checkHeader())
            return -1;

        u8 data_len[1];
        u8 r_data_4[4];
        if (readSerial(data_len, 1) != 1)
            return -1;

        switch (static_cast<int>(data_len[0]))
        {
        case 4:
            readSerial(r_data_4, 4);
            switch (int(r_data_4[0]))
            {
            case 0xa0:
            {
                //0xfe 0xfe 0x04 0xa0 pin_no pin_data 0xfa

                byte pin_no = r_data_4[1];
                bool pin_data = r_data_4[2];

                digitalWrite(pin_no, pin_data);
            }
            break;
            }
            break;

        default:
            break;
        }

        while (Serial.available() > 0)
        {
            Serial2.write(Serial.read());
        }
        while (Serial2.available() > 0)
        {
            Serial.write(Serial2.read());
        }
    }
}