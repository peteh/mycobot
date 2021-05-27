#ifndef DEBUG_MODE_H
#define DEBUG_MODE_H

#include <MycobotBasic.h>
#include "AbstractMode.h"
#include "../pipe/Command.h"

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
            Command m_incomingCommand;
            Command m_outgoingCommand;
    };
}

#endif