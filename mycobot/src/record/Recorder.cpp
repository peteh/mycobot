#include "Recorder.h"

namespace cobot
{
    namespace record
    {
        Recorder::Recorder()
            : m_recordNum(0),
            m_currentIndex(0)
        {
        }

        bool Recorder::record(JointAnglesEnc joints)
        {
            if(m_currentIndex >= MAX_RECORDS)
            {
                return false;
            }
            m_jointAnglesRecord[m_currentIndex] = joints;
            m_currentIndex++;
            m_recordNum = m_currentIndex;
            return true;
        }

        JointAnglesEnc Recorder::getAngles(unsigned int index)
        {
            // TODO: out of bounds check
            return m_jointAnglesRecord[index];
        }

        unsigned int Recorder::getRecordNum()
        {
            return m_recordNum;
        }

        void Recorder::reset()
        {
            m_currentIndex = 0;
            m_recordNum = 0;
        }
    }
}
