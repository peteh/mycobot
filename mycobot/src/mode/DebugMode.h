#ifndef DEBUG_MODE_H
#define DEBUG_MODE_H

#include <MycobotBasic.h>
#include "AbstractMode.h"
typedef  unsigned char u8;

namespace cobot
{
    

    class DebugMode : public AbstractMode
    {
        public: 
            DebugMode(MycobotBasic& myCobot);
            virtual void init() override;

            virtual void process(RobotState& oldState, RobotState& newState) override;

            virtual ~DebugMode() {};
        
        private:
            int readData();
            
            MycobotBasic m_mycobotBasic;
    };
}

#endif