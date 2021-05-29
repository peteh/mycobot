#include "DebugMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>

namespace cobot
{
    DebugMode::DebugMode(MycobotBasic &myCobot)
        : AbstractMode(myCobot),
          m_mycobotBasic(myCobot),
          m_initTime(millis())
    {
    }

    void DebugMode::init()
    {
        m_mycobotBasic.setFreeMove();
    }
    
    Mode DebugMode::process(RobotState &oldState, RobotState &newState)
    {
        for(int i = 0; i < 6; i++)
        {
            Log::infof("%d: %d", i, m_mycobotBasic.getEncoder(i+1));
        }
        
        delay(2000);
        return MODE_THIS;
    }
}