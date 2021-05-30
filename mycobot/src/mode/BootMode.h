#pragma once

#include "../Cobot.h"
#include "AbstractMode.h"

namespace cobot
{
    

    class BootMode : public AbstractMode
    {
        public: 
            BootMode(Cobot& myCobot);
            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~BootMode() {};
        
        private:          
            void pulse(uint delay, uint stepSize);
            void pulseUp(uint delay, uint stepSize);
            void pulseDown(uint delay, uint stepSize);
            unsigned long m_initTime;
    };
}
