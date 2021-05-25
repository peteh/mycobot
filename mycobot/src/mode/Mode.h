#pragma once

#include "State.h"

namespace cobot
{
    enum Mode
    {
        THIS, 
        ESTOP
    };

    class IMode
    {
        public: 
        // called after switching to the mode
        virtual void init() = 0;
        virtual void visualize() = 0;
        virtual void process(RobotState& oldState, RobotState& newState) = 0;
        virtual ~IMode(){};
    };

}