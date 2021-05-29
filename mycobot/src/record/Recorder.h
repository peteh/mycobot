#pragma once

namespace cobot
{
    namespace record
    {
        typedef struct
        {
            int joint_angle[6];
            long delay;
        } JointAnglesEnc;

        class Recorder
        {

        public:
            Recorder();
            void reset();
            bool record(JointAnglesEnc joints);
            unsigned int getRecordNum();
            JointAnglesEnc getAngles(unsigned int index);

        private:
            unsigned int m_recordNum;
            unsigned int m_currentIndex;

            const static unsigned int MAX_RECORDS = 1000;
            JointAnglesEnc m_jointAnglesRecord[MAX_RECORDS];
        };

    }
}