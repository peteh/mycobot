#ifndef AUTOMATIC_MODE_H
#define AUTOMATIC_MODE_H

#include <MycobotBasic.h>
#include "AbstractMode.h"
#include "../pipe/Command.h"
#include "../pipe/Response.h"

typedef  unsigned char u8;

namespace cobot
{
    

    class AutomaticMode : public AbstractMode
    {
        public: 
            AutomaticMode(MycobotBasic& myCobot);
            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~AutomaticMode() {};
        
        private:
            MycobotBasic m_mycobotBasic;
            Command m_incomingCommand;
            Response m_outgoingCommand;
    };
}

#endif