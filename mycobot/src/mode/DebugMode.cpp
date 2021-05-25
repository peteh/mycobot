#include "DebugMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>
#include <MycobotBasic.h>
#include <ParameterList.h>

namespace cobot
{   
    DebugMode::DebugMode(MycobotBasic &myCobot)
        : AbstractMode(),
          m_mycobotBasic(myCobot)
    {
    }

    void DebugMode::init()
    {
    }

    void DebugMode::process(RobotState &oldState, RobotState &newState)
    {
        uint8_t rec_data;
        while (Serial.available() > 0)
        {
            rec_data = Serial.read(); // readSerial
            Log::infof("in: %02x", rec_data);
            Serial2.write(rec_data);
        }

        while (Serial2.available() > 0)
        {
            rec_data = Serial2.read(); // readSerial
            Log::infof("out: %02x", rec_data);
            Serial.write(rec_data);
        }
    }
}