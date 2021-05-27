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
          m_mycobotBasic(myCobot), 
          m_incomingCommand()
    {
    }

    void DebugMode::init()
    {
    }

    void DebugMode::process(RobotState &oldState, RobotState &newState)
    {
        int inData;
        int outData;
        if (Serial.available() > 0)
        {
            inData = Serial.read(); 
            if(inData == -1)
            {
                Log::error("I AM ERROR IN -1");
                return;
            }
            m_incomingCommand.readByte(inData);
            //Log::infof("in: %02x", inData);
            if(m_incomingCommand.isFinished())
            {
                //Log::info("Got a full command");
                m_incomingCommand.forwardCommand(Serial2);
                m_incomingCommand = Command();
            }
            
        }

        if (Serial2.available() > 0)
        {
            outData = Serial2.read(); 
            if(outData == -1)
            {
                Log::error("I AM ERROR OUT -1");
                return;
            }
            Serial.write(outData);
            //Log::infof("out: %02x", outData);
            /*
            m_outgoingCommand.readByte(outData);
            

            if(m_outgoingCommand.isFinished())
            {
                Log::info("Got a full command");
                m_outgoingCommand.forwardCommand(Serial);
                m_outgoingCommand = Command();
            }
            */
        }
        
    }
}