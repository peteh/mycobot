#ifndef ESTOP_MODE_H
#define ESTOP_MODE_H

#include <MycobotBasic.h>
#include "AbstractMode.h"

namespace cobot
{
    class EStopMode : public AbstractMode
    {
        public: 
            EStopMode(MycobotBasic& myCobot);
            virtual void init() override;

            virtual void process(RobotState& state);

            virtual ~EStopMode() {};
        
        private:
            MycobotBasic m_mycobotBasic;
            bool m_cobotFreeMove;
    };
}

#endif