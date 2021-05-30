#include "SuctionPump.h"

namespace cobot
{
    namespace tools
    {
        SuctionPump::SuctionPump()
            : m_isSucking(false)
        {
        }

        void SuctionPump::setup()
        {
            pinMode(SUCTION_PUMP_MOTOR_IO, OUTPUT);
            pinMode(SUCTION_PUMP_SOLENOID_IO, OUTPUT);
            digitalWrite(SUCTION_PUMP_SOLENOID_IO, HIGH);
            digitalWrite(SUCTION_PUMP_MOTOR_IO, HIGH);
            m_isSucking = false;
        }

        void SuctionPump::suck()
        {
            digitalWrite(SUCTION_PUMP_SOLENOID_IO, LOW);
            digitalWrite(SUCTION_PUMP_MOTOR_IO, LOW);
            m_isSucking = true;
        }

        void SuctionPump::unsuck()
        {
            digitalWrite(SUCTION_PUMP_SOLENOID_IO, HIGH);
            digitalWrite(SUCTION_PUMP_MOTOR_IO, HIGH);
            m_isSucking = false;
        }

        bool SuctionPump::isSucking()
        {
            return m_isSucking;
        }
    }
}