#include "Response.h"
#include <Log.h>

namespace cobot
{

    Response::Response()
        : m_state(FIND_HEADER1),
          m_commandSize(0),
          m_commandId(0),
          m_bufferIndex(0)
    {
    }

    void Response::readByte(uint8_t data)
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
        case READ_COMMAND_ID:
            readCommandId(data);
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

    void Response::findHeader1(uint8_t data)
    {
        if (data != HEADER)
        {
            //Log::errorf("H1: %c", data);
            // not matching, we continue to find header1
            m_state = FIND_HEADER1;
            return;
        }
        m_state = FIND_HEADER2;
    }

    void Response::findHeader2(uint8_t data)
    {
        if (data != HEADER)
        {
            //Log::error("Did not find header2");
            // second header byte not matched, we go back to step 1
            m_state = FIND_HEADER1;
            return;
        }
        m_state = READ_COMMAND_SIZE;
    }

    void Response::readCommandSize(uint8_t data)
    {
        // read the expected size
        m_commandSize = data;

        m_state = READ_COMMAND_ID;
    }

    void Response::readCommandId(uint8_t data)
    {
        // read the expected size
        m_commandId = data;
        // start to read data
        m_bufferIndex = 0;
        m_state = READ_DATA;
    }

    void Response::readData(uint8_t data)
    {
        // read one byte into the buffer
        m_buffer[m_bufferIndex++] = data;
        if (m_bufferIndex >= m_commandSize - 2)
        {
            m_state = FIND_FOOTER;
        }
    }

    void Response::findFooter(uint8_t data)
    {
        if (data != FOOTER)
        {
            Log::error("Did not find footer");
            // not matching, we reset everything and start from scratch
            m_state = FIND_HEADER1;
            return;
        }
        m_state = FINISHED;
    }

    void Response::forwardCommand(HardwareSerial serial)
    {
        serial.write(HEADER);
        serial.write(HEADER);
        serial.write(m_commandSize);
        serial.write(m_commandId);
        serial.write(m_buffer, m_commandSize - 2);
        serial.write(FOOTER);
    }

    bool Response::isFinished()
    {
        return m_state == FINISHED;
    }

}