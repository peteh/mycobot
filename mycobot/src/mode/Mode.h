#ifndef MODE_H
#define MODE_H

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
        virtual void process(RobotState& state) = 0;
        virtual ~IMode(){};
    };

}

#endif