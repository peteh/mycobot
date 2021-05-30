#include "DebugMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>

namespace cobot
{
    DebugMode::DebugMode(Cobot &myCobot)
        : AbstractMode(myCobot),
          m_initTime(millis()),
          m_solenoid(true),
          m_motorOn(true)
    {
    }

    void DebugMode::init()
    {
        pinMode(2,OUTPUT); //set pin G2 to output state
        pinMode(5,OUTPUT); //set pin G5 to output state
        digitalWrite(2, m_solenoid);
        digitalWrite(5, m_motorOn);
    }

    void DebugMode::showEncoders()
    {
        for (int i = 0; i < 6; i++)
        {
            Log::infof("%d: %d", i, getCobot().getBase().getEncoder(i + 1));
        }

        delay(2000);
    }

    void DebugMode::TFTTest()
    {
        TFT_eSprite spr = TFT_eSprite(&M5.Lcd);

        int16_t screenWidth = M5.Lcd.width();
        int16_t screenHeight = M5.Lcd.height();
        spr.createSprite(screenWidth, screenHeight - 70);

        spr.fillSprite(TFT_BLUE);
        spr.setTextSize(5);
        spr.setCursor(100, 100);
        spr.setTextSize(5);
        //spr.setTextDatum(MC_DATUM);
        //spr.drawString("BIG TEXT", screenWidth / 2, screenHeight / 2);
        spr.setTextSize(2);

        spr.pushSprite(0, 0);
    }

    void DebugMode::IOTest()
    {
        //m_mycobotBasic.setPinMode(GPIO_NUM_39, 1);
        unsigned int gpio = GPIO_NUM_39;
        int value = digitalRead(gpio);
        //int value = m_mycobotBasic.getDigitalInput(GPIO_NUM_39);
        Log::infof("IO %d: %d", gpio, value);
    }

    void DebugMode::pumpTest()
    {
        if(M5.BtnA.wasPressed())
        {
            m_solenoid = !m_solenoid;
            digitalWrite(2, m_solenoid);
            Log::infof("Solenoid: %d", m_solenoid);
        }

        if(M5.BtnB.wasPressed())
        {
            m_motorOn = !m_motorOn;
            digitalWrite(5, m_motorOn);
            Log::infof("Motor: %d", m_motorOn);
        }
    }

    Mode DebugMode::process(RobotState &oldState, RobotState &newState)
    {
        pumpTest();
        return MODE_THIS;
    }
}