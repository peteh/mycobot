#pragma once

#include <MycobotBasic.h>
#include "AbstractMode.h"

namespace cobot
{
    class EStopMode : public AbstractMode
    {
        public: 
            EStopMode(MycobotBasic& myCobot);

            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;
            void updateVisualization(RobotState &robotState);

            virtual ~EStopMode() {};
        
        private:
            MycobotBasic m_mycobotBasic;
            bool m_cobotFreeMove;
    };
}