#pragma once

#include <MycobotBasic.h>
#include "AbstractMode.h"

namespace cobot
{
    

    class WaitAutomaticMode : public AbstractMode
    {
        public: 
            WaitAutomaticMode(Cobot& myCobot);
            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~WaitAutomaticMode() {};
        
        private:
            unsigned long m_initTime;
    };
}
