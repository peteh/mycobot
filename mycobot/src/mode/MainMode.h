#pragma once

#include <MycobotBasic.h>
#include "AbstractMode.h"

namespace cobot
{
    

    class MainMode : public AbstractMode
    {
        public: 
            MainMode(Cobot& myCobot);
            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~MainMode() {};

    };
}
