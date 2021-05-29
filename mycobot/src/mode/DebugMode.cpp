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
        /*
        for(int i = 0; i < 6; i++)
        {
            Log::infof("%d: %d", i, m_mycobotBasic.getEncoder(i+1));
        }
        
        delay(2000);
        return MODE_THIS;
        */

        TFT_eSprite spr = TFT_eSprite(&M5.Lcd);

        int16_t screenWidth = M5.Lcd.width();
        int16_t screenHeight = M5.Lcd.height();
        spr.createSprite(screenWidth, screenHeight-70);

        spr.fillSprite(TFT_BLUE);
        spr.setTextSize(5);
        spr.setCursor(100, 100);
        spr.setTextSize(5);
        //spr.setTextDatum(MC_DATUM);
        //spr.drawString("BIG TEXT", screenWidth / 2, screenHeight / 2);
        spr.setTextSize(2);
        
        spr.pushSprite(0,0);
    }
}