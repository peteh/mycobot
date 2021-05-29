#pragma once

#include <MycobotBasic.h>
#include "AbstractMode.h"
#include "record/Recorder.h"

namespace cobot
{

    class RecordMode : public AbstractMode
    {
    public:
        RecordMode(MycobotBasic &myCobot, record::Recorder *recorder);

        virtual void init() override;

        virtual Mode process(RobotState &oldState, RobotState &newState) override;

        virtual ~RecordMode(){};

    private:
        enum InternalMode
        {
            MAIN,
            RECORDING,
            FREE_MOVE
        };

        void updateVisualization();

        MycobotBasic m_mycobotBasic;
        unsigned long m_lastRecordTime;
        InternalMode m_mode;

        record::Recorder *m_recorder;
    };
}
