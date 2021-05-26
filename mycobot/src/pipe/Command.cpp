#include "Command.h"
#include <Log.h>

namespace cobot
{

    Command::Command()
        : m_state(FIND_HEADER1),
          m_commandSize(0),
          m_bufferIndex(0)
    {
    }

    void Command::readByte(uint8_t data)
    {
        // TODO: add error logging to all functions
        switch (m_state)
        {
        case FIND_HEADER1:
            findHeader1(data);
            break;
        case FIND_HEADER2:
            findHeader2(data);
            break;
        case READ_COMMAND_SIZE:
            readCommandSize(data);
            break;
        case READ_DATA:
            readData(data);
            break;
        case FIND_FOOTER:
            findFooter(data);
            break;
        case FINISHED:
            Log::error("Reading command already finished, don't read new bytes into it");
            break;
        default:
            Log::errorf("Unexpected case for Command state reading: %d", m_state);
            break;
        }
    }

    void Command::findHeader1(uint8_t data)
    {
        if (data != 0xfe)
        {
            // not matching, we continue to find header1
            m_state = FIND_HEADER1;
            return;
        }
        m_state = FIND_HEADER2;
    }

    void Command::findHeader2(uint8_t data)
    {
        if (data != 0xfe)
        {
            // second header byte not matched, we go back to step 1
            m_state = FIND_HEADER1;
            return;
        }
        m_state = READ_COMMAND_SIZE;
    }

    void Command::readCommandSize(uint8_t data)
    {
        // read the expected size
        m_commandSize = data;
        m_bufferIndex = 0;
        // start to read data
        m_state = READ_DATA;
    }

    void Command::readData(uint8_t data)
    {
        // read one byte into the buffer
        m_buffer[m_bufferIndex++] = data;
        if (m_bufferIndex >= m_commandSize)
        {
            m_state = FIND_FOOTER;
        }
    }

    void Command::findFooter(uint8_t data)
    {
        if (data != FOOTER)
        {
            // not matching, we reset everything and start from scratch
            m_state = FIND_HEADER1;
            return;
        }
        m_state = FINISHED;
    }

    bool Command::isFinished()
    {
        return m_state == FINISHED;
    }

}