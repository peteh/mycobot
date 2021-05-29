#pragma once

#include "State.h"

namespace cobot
{
    enum Mode
    {
        MODE_THIS, 
        MODE_ESTOP,
        MODE_AUTOMATIC,
        MODE_MAIN
    };

    class IMode
    {
        public: 
        // called after switching to the mode
        virtual void init() = 0;
        virtual void visualize() = 0;
        virtual void forceNextVisualizationUpdate() = 0;
        virtual Mode process(RobotState& oldState, RobotState& newState) = 0;
        virtual ~IMode(){};
    };

}