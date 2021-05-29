#include "MainMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>
#include <MycobotBasic.h>
#include <ParameterList.h>

namespace cobot
{   
    MainMode::MainMode(MycobotBasic &myCobot)
        : AbstractMode(),
          m_mycobotBasic(myCobot)
    {
    }

    void MainMode::init()
    {
        setBigText("Main");
        setButtonCText("Auto");
    }

    Mode MainMode::process(RobotState &oldState, RobotState &newState)
    {
        if(M5.BtnC.wasPressed())
        {
            return MODE_AUTOMATIC;
        }
        return MODE_THIS;
        
    }
}