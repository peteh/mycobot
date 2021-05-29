#pragma once

#include <MycobotBasic.h>
#include "AbstractMode.h"

namespace cobot
{
    

    class WaitAutomaticMode : public AbstractMode
    {
        public: 
            WaitAutomaticMode(MycobotBasic& myCobot);
            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~WaitAutomaticMode() {};
        
        private:
            MycobotBasic m_mycobotBasic;
            unsigned long m_initTime;
    };
}
