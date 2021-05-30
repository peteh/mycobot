#include "Recorder.h"
#include <Arduino.h>
#include <Log.h>
#include <FS.h>
#include <SPIFFS.h>

#define FORMAT_SPIFFS_IF_FAILED true

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
            if (m_currentIndex >= MAX_RECORDS)
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

        bool Recorder::saveToFile()
        {
            return saveToFile(DEFAULT_FILENAME);
        }

        bool Recorder::saveToFile(const char *fileName)
        {
            // TODO: move this to main initialization
            if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
            {
                Log::error("SPIFFS Mount Failed");
                return false;
            }

            File file = SPIFFS.open(fileName, FILE_WRITE);

            // TODO: some error handling
            for (int data_index = 0; data_index < m_recordNum; data_index++)
            {
                String data_output = "";
                for (int i = 0; i < 6; i++)
                {
                    data_output += m_jointAnglesRecord[data_index].joint_angle[i];
                    data_output += ",";
                }
                data_output += m_jointAnglesRecord[data_index].pump;
                data_output += ",";
                data_output += m_jointAnglesRecord[data_index].delay;
                data_output += ",";
                data_output += "\n";
                file.print(data_output);
            }
            file.close();
            return true;
        }

        JointAnglesEnc Recorder::processStringIntoInts(String string_input)
        {
            JointAnglesEnc sae;
            int data_index = 0;
            String data_angle_string = "";
            for (int i = 0; string_input[i] != '\n'; i++)
            {

                if (string_input[i] == ',')
                {
                    if ((data_index < 6) && (i > 1))
                    {
                        sae.joint_angle[data_index] = data_angle_string.toInt();
                    }
                    else if(data_index == 6)
                    {
                        sae.pump = data_angle_string.toInt() > 0;
                    }
                    else if(data_index == 7)
                    {
                        sae.delay = data_angle_string.toInt();
                    }
                    else
                    {
                        break;
                    }
                    data_angle_string = "";
                    data_index++;
                    continue;
                }
                else
                {
                    data_angle_string += string_input[i];
                }
            }
            return sae;
        }

        bool Recorder::loadFromFile()
        {
            return loadFromFile(DEFAULT_FILENAME);
        }

        bool Recorder::loadFromFile(const char *fileName)
        {

            if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
            {
                Log::error("SPIFFS Mount Failed");
                return false;
            }

            Log::infof("Reading file: %s\r\n", fileName);
            File file = SPIFFS.open(fileName);
            if (!file || file.isDirectory())
            {
                Log::errorf("Failed to open file: %s", fileName);
                return false;
            }
            String this_line = "";
            int index = 0;
            while (file.available() && index < MAX_RECORDS)
            {
                char this_char = char(file.read());
                this_line += this_char;
                if (this_char == '\n')
                {
                    JointAnglesEnc sae_this;
                    sae_this = processStringIntoInts(this_line);

                    m_jointAnglesRecord[index] = sae_this;

                    index++;
                    this_line = "";
                }
            }
            m_recordNum = index;
            Log::infof("read %d", m_recordNum);
            if (m_recordNum > 0)
            {
                auto angles = getAngles(0);
                Log::infof("l1: %d, %d, %d, %d, %d, %d",
                           angles.joint_angle[0],
                           angles.joint_angle[1],
                           angles.joint_angle[2],
                           angles.joint_angle[3],
                           angles.joint_angle[4],
                           angles.joint_angle[5]);
            }
            file.close();
            return true;
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
