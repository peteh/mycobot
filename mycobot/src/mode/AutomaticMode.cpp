#include "AutomaticMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>
#include <MycobotBasic.h>
#include <ParameterList.h>

namespace cobot
{   
    AutomaticMode::AutomaticMode(MycobotBasic &myCobot)
        : AbstractMode(),
          m_mycobotBasic(myCobot)
    {
    }

    void AutomaticMode::init()
    {
        setBigText("AUTO");
        setButtonAText("");
        setButtonBText("Main");
        setButtonCText("");
    }

    Mode AutomaticMode::process(RobotState &oldState, RobotState &newState)
    {
        int inData;
        int outData;

        if(M5.BtnB.wasPressed())
        {
            return MODE_MAIN;
        }
        // read all data from the external controller and forward them
        // to the atom if the command is finished.
        if (Serial.available() > 0)
        {
            inData = Serial.read(); 
            if(inData == -1)
            {
                Log::error("I AM ERROR IN -1");
                return MODE_THIS;
            }
            m_incomingCommand.readByte(inData);
            if(m_incomingCommand.isFinished())
            {
                m_incomingCommand.forwardCommand(Serial2);
                m_incomingCommand = Command();
            }
            
        }

        // read available bytes from the Atom controller
        // and forward them as soon as we have a full one

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

            m_outgoingCommand.readByte(outData);
            if(m_outgoingCommand.isFinished())
            {
                m_outgoingCommand.forwardCommand(Serial);
                m_outgoingCommand = Response();
            }
        }

        return MODE_THIS;
    }

}