#pragma once
#include <Arduino.h>
namespace cobot
{
    namespace tools
    {
        const static uint SUCTION_PUMP_SOLENOID_IO = G2;
        const static uint SUCTION_PUMP_MOTOR_IO = G5;

        class SuctionPump
        {
        public:
            SuctionPump();
            void setup();
            void suck();
            void unsuck();
            bool isSucking();

        private:
            bool m_isSucking;
        };
    }
}
