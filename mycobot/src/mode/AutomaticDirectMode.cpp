#include "AutomaticDirectMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>
#include <MycobotBasic.h>
#include <ParameterList.h>

namespace cobot
{   
    AutomaticDirectMode::AutomaticDirectMode(MycobotBasic &myCobot)
        : AbstractMode(myCobot),
          m_mycobotBasic(myCobot)
    {
    }

    void AutomaticDirectMode::init()
    {
    }

    Mode AutomaticDirectMode::process(RobotState &oldState, RobotState &newState)
    {
        int inData;
        int outData;

        // read all data from the external controller and forward them
        // to the atom directly
        if (Serial.available() > 0)
        {
            inData = Serial.read(); 
            if(inData == -1)
            {
                Log::error("I AM ERROR IN -1");
                return MODE_THIS;
            }
            Serial2.write(inData);
        }

        // read available bytes from the Atom controller
        // and forward them directly

        // currently also acts as a filter for all non-responses
        // the controller sends angle data regularly as it seems
        if (Serial2.available() > 0)
        {
            outData = Serial2.read(); 
            if(outData == -1)
            {
                Log::error("I AM ERROR OUT -1");
                return MODE_THIS;
            }
            Serial.write(outData);
        }

        return MODE_THIS;
    }
}