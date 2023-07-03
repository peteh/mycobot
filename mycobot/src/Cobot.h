#pragma once
#include <MyCobotBasic.h>
#include "tools/SuctionPump.h"
namespace cobot
{
    class Cobot
    {
    public:
        Cobot();

        MyCobotBasic &getBase();
        tools::SuctionPump &getSuctionPump();

    private:
        MyCobotBasic m_myCobot;
        tools::SuctionPump m_suctionPump;
    };
}