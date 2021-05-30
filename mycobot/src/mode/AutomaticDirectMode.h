#ifndef DEBUG_MODE_H
#define DEBUG_MODE_H

#include <MycobotBasic.h>
#include "AbstractMode.h"
#include "../pipe/Command.h"
#include "../pipe/Response.h"

typedef  unsigned char u8;

namespace cobot
{
    

    class AutomaticDirectMode : public AbstractMode
    {
        public: 
            AutomaticDirectMode(Cobot& myCobot);
            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~AutomaticDirectMode() {};

    };
}

#endif