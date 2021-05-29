#pragma once

#include <MycobotBasic.h>
#include "AbstractMode.h"

namespace cobot
{
    

    class BootMode : public AbstractMode
    {
        public: 
            BootMode(MycobotBasic& myCobot);
            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~BootMode() {};
        
        private:          
            MycobotBasic m_mycobotBasic;
            unsigned long m_initTime;
    };
}
