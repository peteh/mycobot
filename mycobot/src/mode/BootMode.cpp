#include "BootMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>

namespace cobot
{
    BootMode::BootMode(Cobot &myCobot)
        : AbstractMode(myCobot),
          m_initTime(millis())
    {
    }

    void BootMode::init()
    {
        m_initTime = millis();
        setBigText("Booting");
    }
    
    void BootMode::pulseUp(uint delayMs, uint stepSize)
    {
        for (int16_t x = 0; x <= 255; x += stepSize)
        {
            getCobot().getBase().setLEDRGB(x, x, x);
            delay(delayMs);
        }
        getCobot().getBase().setLEDRGB(255, 255, 255);
        delay(delayMs);
    }

    void BootMode::pulseDown(uint delayMs, uint stepSize)
    {
        for (int16_t x = 255; x >= 0; x -= stepSize)
        {
            getCobot().getBase().setLEDRGB(x, x, x);
            delay(delayMs);
        }
        getCobot().getBase().setLEDRGB(0, 0, 0);
        delay(delayMs);
    }

    void BootMode::pulse(uint delayMs, uint stepSize)
    {
        pulseUp(delayMs, stepSize);
        pulseDown(delayMs, stepSize);
    }

    Mode BootMode::process(RobotState &oldState, RobotState &newState)
    {
        getCobot().getBase().jogStop();
        // TODO make cool
        for(uint i = 0; i < 0; i++)
        {
            pulse(50, 10);
        }
        pulseUp(50, 10);
        return MODE_MAIN;
    }
}