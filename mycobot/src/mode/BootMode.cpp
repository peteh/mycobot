#include "BootMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>
#include <MycobotBasic.h>
#include <ParameterList.h>

namespace cobot
{   
    BootMode::BootMode(MycobotBasic &myCobot)
        : AbstractMode(),
          m_mycobotBasic(myCobot),
          m_initTime(millis())
    {
    }

    void BootMode::init()
    {
        m_initTime = millis();
        setBigText("Booting");
    }

    Mode BootMode::process(RobotState &oldState, RobotState &newState)
    {
        delay(1000);
        return MODE_MAIN;        
    }
}