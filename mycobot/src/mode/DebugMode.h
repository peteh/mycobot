#pragma once

#include <MycobotBasic.h>
#include "AbstractMode.h"

namespace cobot
{
    

    class DebugMode : public AbstractMode
    {
        public: 
            DebugMode(MycobotBasic& myCobot);
            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~DebugMode() {};
        
        private:          
            MycobotBasic m_mycobotBasic;
            unsigned long m_initTime;
    };
}
