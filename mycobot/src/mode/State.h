#ifndef STATE_H
#define STATE_H
#include <EStopReceiver.h>

namespace cobot
{
    class RobotState
    {
        estop::EStopReceiver::EStopState eStopState;
    };
}

#endif