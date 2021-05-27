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
        void forwardCommand(HardwareSerial serial);

        Command& operator=(Command other)
    {
        //std::cout << "copy assignment of A\n";
        std::swap(m_commandSize, other.m_commandSize);
        std::swap(m_state, other.m_state);
        std::swap(m_bufferIndex, other.m_bufferIndex);

        // TODO: does this work properly?
        std::swap(m_buffer, other.m_buffer);
        return *this;
    }

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