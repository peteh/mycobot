#include "MainMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>
#include <MycobotBasic.h>
#include <ParameterList.h>

namespace cobot
{   
    MainMode::MainMode(MycobotBasic &myCobot)
        : AbstractMode(myCobot),
          m_mycobotBasic(myCobot)
    {
    }

    void MainMode::init()
    {
        setBigText("Main");
        setButtonAText("Record");
        setButtonBText("Play Record");
        setButtonCText("Debug");
        m_mycobotBasic.setLEDRGB(255, 255, 255);
    }

    Mode MainMode::process(RobotState &oldState, RobotState &newState)
    {
        if(M5.BtnA.wasPressed())
        {
            return MODE_RECORD;
        }

        if(M5.BtnB.wasPressed())
        {
            return MODE_PLAY_RECORD;
        }
        if(M5.BtnC.wasPressed())
        {
            return MODE_DEBUG;
        }
        return MODE_THIS;
        
    }
}