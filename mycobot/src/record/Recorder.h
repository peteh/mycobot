#pragma once
#include <Arduino.h>

namespace cobot
{
    namespace record
    {
        const static char DEFAULT_FILENAME[] = "/Angles.txt";

        typedef struct
        {
            int joint_angle[6];
            bool pump;
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

            bool saveToFile();
            bool saveToFile(const char *fileName);
            bool loadFromFile();
            bool loadFromFile(const char *fileName);

        private:
            JointAnglesEnc processStringIntoInts(String string_input);

            unsigned int m_recordNum;
            unsigned int m_currentIndex;

            const static unsigned int MAX_RECORDS = 1000;
            JointAnglesEnc m_jointAnglesRecord[MAX_RECORDS];

            
        };

    }
}