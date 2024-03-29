#include "EStopMode.h"
#include <M5Stack.h>
#include <Log.h>
namespace cobot
{
    EStopMode::EStopMode(Cobot &myCobot)
        : AbstractMode(myCobot),
          m_cobotFreeMove(false)
    {
    }

    void EStopMode::init()
    {
        // flush all serials
        Serial2.flush();
        while (Serial2.available())
        {
            Serial2.read();
        }
        getCobot().getBase().jogStop();
        getCobot().getSuctionPump().unsuck();
        delay(50);
        m_cobotFreeMove = false;
    }

    void EStopMode::updateVisualization(RobotState &newState)
    {
        if (newState.eStopState == estop::ESTOP_FREE)
        {
            setBigText("Waiting");
            
            setButtonCText("Auto");
            if (m_cobotFreeMove)
            {
                setLEDColor(color::COLOR_BLUE);
                setButtonBText("");
                setButtonAText("Hold");
            }
            else
            {
                setLEDColor(color::COLOR_WHITE);
                setButtonBText("Main");
                setButtonAText("Move Free");
            }
        }

        else if (newState.eStopState == estop::ESTOP_TIMEOUT)
        {
            setLEDColor(color::COLOR_RED);
            setBigText("E-STOP TIMEOUT");
            setButtonAText("");
            setButtonBText("");
            setButtonCText("");
        }
        else
        {
            setLEDColor(color::COLOR_RED);
            setBigText("E-STOP");
            setButtonAText("");
            setButtonBText("");
            setButtonCText("");
        }
    }

    Mode EStopMode::process(RobotState &oldState, RobotState &newState)
    {
        bool forceUpdate = false;
        if (newState.eStopState == estop::ESTOP_FREE)
        {
            if (M5.BtnA.wasPressed())
            {
                m_cobotFreeMove = !m_cobotFreeMove;
                if (m_cobotFreeMove)
                {
                    getCobot().getBase().setFreeMove();
                }
                else
                {
                    getCobot().getBase().jogStop();
                }
                forceUpdate = true;
                delay(50);
            }

            // Main Button pressed
            if (M5.BtnB.wasPressed() && !m_cobotFreeMove)
            {
                return MODE_MAIN;
            }

            // Automatic Button pressed
            if (M5.BtnC.wasPressed())
            {
                return MODE_AUTOMATIC_WAIT;
            }
        }

        if (oldState.eStopState != newState.eStopState || forceUpdate)
        {
            updateVisualization(newState);
        }

        return MODE_THIS;
    }
}