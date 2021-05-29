#include "WaitAutomaticMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>
#include <MycobotBasic.h>
#include <ParameterList.h>

namespace cobot
{   
    WaitAutomaticMode::WaitAutomaticMode(MycobotBasic &myCobot)
        : AbstractMode(myCobot),
          m_mycobotBasic(myCobot),
          m_initTime(millis())
    {
    }

    void WaitAutomaticMode::init()
    {
        setBigText("3");
        m_initTime = millis();
    }

    Mode WaitAutomaticMode::process(RobotState &oldState, RobotState &newState)
    {
        long timeDelta = millis() - m_initTime;

        if(timeDelta >= 3000)
        {
            return MODE_AUTOMATIC;
        }
        else if(timeDelta >= 2000)
        {
            setBigText("1");
        }
        else if(timeDelta >= 1000)
        {
            setBigText("2");
        }
        else if(timeDelta >= 0)
        {
            setBigText("3");
        }

        return MODE_THIS;
    }

}