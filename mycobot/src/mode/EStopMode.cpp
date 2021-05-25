#include "EStopMode.h"
#include <M5Stack.h>
namespace cobot
{
    EStopMode::EStopMode(MycobotBasic &myCobot)
        : AbstractMode(),
          m_mycobotBasic(myCobot),
          m_cobotFreeMove(false)
    {
    }
    void EStopMode::init()
    {
        m_mycobotBasic.stop();
        m_cobotFreeMove = false;
    }
    void EStopMode::process(RobotState &oldState, RobotState &newState)
    {
        if (newState.eStopState == estop::ESTOP_FREE)
        {
            setBigText("Waiting");
            if (m_cobotFreeMove)
            {
                setButtonAText("Hold");
            }
            else
            {
                setButtonAText("Move Free");
            }

            if (M5.BtnA.wasPressed())
            {
                m_cobotFreeMove = !m_cobotFreeMove;
                if (m_cobotFreeMove)
                {
                    m_mycobotBasic.setFreeMove();
                }
                else
                {
                    m_mycobotBasic.stop();
                }
            }
        }
        else
        {
            setBigText("E-STOP");
            setButtonAText("");
        }
    }
}