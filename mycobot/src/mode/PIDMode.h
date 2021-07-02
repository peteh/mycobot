#pragma once

#include "../Cobot.h"
#include "AbstractMode.h"

namespace cobot
{

    class PIDMode : public AbstractMode
    {
    public:
        PIDMode(Cobot &myCobot);
        virtual void init() override;

        virtual Mode process(RobotState &oldState, RobotState &newState) override;

        virtual ~PIDMode(){};

    private:
        void setMode1();
        void setMode2();
    };
}
