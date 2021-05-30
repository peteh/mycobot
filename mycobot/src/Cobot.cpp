#include "Cobot.h"

namespace cobot
{
    Cobot::Cobot()
        : m_myCobot(),
          m_suctionPump()
    {
    }

    MycobotBasic& Cobot::getBase()
    {
        return m_myCobot;
    }

    tools::SuctionPump& Cobot::getSuctionPump()
    {
        return m_suctionPump;
    }
}