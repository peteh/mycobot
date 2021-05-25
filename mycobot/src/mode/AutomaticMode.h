#ifndef AUTOMATIC_MODE_H
#define AUTOMATIC_MODE_H

#include <MycobotBasic.h>
#include "AbstractMode.h"
typedef  unsigned char u8;

namespace cobot
{
    

    class AutomaticMode : public AbstractMode
    {
        public: 
            AutomaticMode(MycobotBasic& myCobot);
            virtual void init() override;

            virtual void process(RobotState& oldState, RobotState& newState) override;

            virtual ~AutomaticMode() {};
        
        private:
            int readData();
            
            bool checkHeader();
            void rFlushSerial();
            int readSerial(unsigned char* nDat, int nLen);
            MycobotBasic m_mycobotBasic;
            bool m_cobotFreeMove;
    };
}

#endif