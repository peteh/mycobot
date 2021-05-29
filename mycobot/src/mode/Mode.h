#pragma once

#include "State.h"

namespace cobot
{
    enum Mode
    {
        MODE_THIS, 
        MODE_BOOT,
        MODE_ESTOP,
        MODE_RECORD,
        MODE_PLAY_RECORD, 
        MODE_AUTOMATIC,
        MODE_AUTOMATIC_DIRECT,
        MODE_MAIN,
        MODE_AUTOMATIC_WAIT,

        MODE_DEBUG

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