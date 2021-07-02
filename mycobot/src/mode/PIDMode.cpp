#include "PIDMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>

namespace cobot
{
    /**
     * MyCobot provides two modes:
     * Mode 1 (default):  
     *  Servo 1-3:
     *  P = 5, I = 0, D = 15
     *  Servo 4-6:
     *  P = 8, I = 0, D = 24
     * 
     * Mode 2: 
     *  P = 10, I = 1, D = 0
     */
    PIDMode::PIDMode(Cobot &myCobot)
        : AbstractMode(myCobot)
    {
    }

    void PIDMode::init()
    {
        // TODO: label buttons
    }

    void PIDMode::setMode1()
    {
        int P, I, D;
        for (int i = 1; i < 7; i++)
        {
            if (i < 4)
            {
                P = 5;
                I = 0;
                D = 15;
            }
            else
            {
                P = 8;
                I = 0;
                D = 24;
            }
            getCobot().getBase().setServoData(i, 21, P); //P
            delay(50);
            getCobot().getBase().setServoData(i, 22, D); //D
            delay(50);
            getCobot().getBase().setServoData(i, 23, I); //I
            delay(50);
        }
    }

    void PIDMode::setMode2()
    {
        int P, I, D;
        P = 10;
        I = 1;
        D = 0;
        for (int i = 1; i < 7; i++)
        {
            getCobot().getBase().setServoData(i, 21, P); //P
            delay(50);
            getCobot().getBase().setServoData(i, 22, D); //D
            delay(50);
            getCobot().getBase().setServoData(i, 23, I); //I
            delay(50);
        }
    }

    Mode PIDMode::process(RobotState &oldState, RobotState &newState)
    {
        if (M5.BtnA.wasPressed())
        {
            setMode1();
        }
        if (M5.BtnB.wasPressed())
        {
            setMode2();
        }
        M5.Lcd.clear(BLACK);
        M5.Lcd.setCursor(0, 10);
        M5.Lcd.setTextSize(2);
        M5.Lcd.println("Servo CHANGE PID is");
        for (int i = 1; i < 7; i++)
        {
            M5.Lcd.print("servo: ");
            M5.Lcd.print(i);
            M5.Lcd.print(" P: ");
            M5.Lcd.print(getCobot().getBase().getServoData(i, 21)); //P
            delay(50);
            M5.Lcd.print(" D: ");
            M5.Lcd.print(getCobot().getBase().getServoData(i, 22)); //D
            delay(50);
            M5.Lcd.print(" I: ");
            M5.Lcd.print(getCobot().getBase().getServoData(i, 23)); //I
            delay(50);
            M5.Lcd.println();
            M5.Lcd.println();
        }
        return MODE_THIS;
    }
}