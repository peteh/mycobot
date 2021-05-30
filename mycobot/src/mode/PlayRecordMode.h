#pragma once
#include "AbstractMode.h"
#include "record/Recorder.h"

namespace cobot
{
    
    class PlayRecordMode : public AbstractMode
    {
        public: 
            PlayRecordMode(Cobot &myCobot, record::Recorder* recorder);

            virtual void init() override;

            virtual Mode process(RobotState& oldState, RobotState& newState) override;

            virtual ~PlayRecordMode() {};
        
        private:
            void updateVisualization();

            unsigned long m_lastRecordTime;
            bool m_playingRecord;
            unsigned int m_playingIndex;

            record::Recorder* m_recorder;

    };
}
