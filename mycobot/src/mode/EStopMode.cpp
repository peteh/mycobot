#include "EStopMode.h"
#include <M5Stack.h>
namespace cobot
{
    EStopMode::EStopMode(MycobotBasic& myCobot)
    : AbstractMode(),
    m_mycobotBasic(myCobot),
    m_cobotFreeMove(false)
    {

    }
    void EStopMode::init()
    {
        m_mycobotBasic.stop();
        m_cobotFreeMove = false;
        setButtonAText("Move Free");
    }
    void EStopMode::process(RobotState& state)
    {
        
        if(M5.BtnA.wasPressed())
        {
            m_cobotFreeMove = !m_cobotFreeMove;

            if(m_cobotFreeMove)
            {
                setButtonAText("Hold");
                m_mycobotBasic.setFreeMove();
            }
            else
            {
                setButtonAText("Move Free");
                m_mycobotBasic.stop();
            }
        }

        if(M5.BtnB.wasPressed())
        {
            m_mycobotBasic.stop();
            setButtonBText("Pressed");
        }
    }
}