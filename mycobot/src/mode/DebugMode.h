#pragma once

#include "../Cobot.h"
#include "AbstractMode.h"

namespace cobot
{

    class DebugMode : public AbstractMode
    {
    public:
        DebugMode(Cobot &myCobot);
        virtual void init() override;

        virtual Mode process(RobotState &oldState, RobotState &newState) override;

        virtual ~DebugMode(){};

    private:
        void showEncoders();
        void TFTTest();
        void IOTest();
        void pumpTest();
        unsigned long m_initTime;

        bool m_solenoid;
        bool m_motorOn;
    };
}
