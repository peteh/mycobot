#include "MainMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>

namespace cobot
{   
    MainMode::MainMode(Cobot &myCobot)
        : AbstractMode(myCobot)
    {
    }

    void MainMode::init()
    {
        setBigText("Main");
        setButtonAText("Record");
        setButtonBText("Replay");
        setButtonCText("Debug");
        setLEDColor(color::COLOR_WHITE);
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