#pragma once
#include <Arduino.h>

namespace cobot
{
    class Command
    {
        const uint8_t HEADER = 0xfe;
        const uint8_t FOOTER = 0xfa;

        enum State
        {
            FIND_HEADER1,
            FIND_HEADER2,
            READ_COMMAND_SIZE,
            READ_DATA,
            FIND_FOOTER,
            FINISHED
        };

    public:
    Command();
        void readByte(uint8_t data);
        bool isFinished();

    private:
        void findHeader1(uint8_t data);
        void findHeader2(uint8_t data);
        void readCommandSize(uint8_t data);
        void readData(uint8_t data);
        void findFooter(uint8_t data);

        State m_state;
        unsigned int m_commandSize;

        uint8_t m_buffer[255];
        unsigned int m_bufferIndex;
        
        
    };
}