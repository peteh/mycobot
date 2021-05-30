#pragma once
#include <MycobotBasic.h>
#include "tools/SuctionPump.h"
namespace cobot
{
    class Cobot
    {
    public:
        Cobot();

        MycobotBasic &getBase();
        tools::SuctionPump &getSuctionPump();

    private:
        MycobotBasic m_myCobot;
        tools::SuctionPump m_suctionPump;
    };
}