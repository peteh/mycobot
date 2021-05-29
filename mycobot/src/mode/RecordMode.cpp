#include "RecordMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>

namespace cobot
{
    RecordMode::RecordMode(MycobotBasic &myCobot, record::Recorder *recorder)
        : AbstractMode(myCobot),
          m_mycobotBasic(myCobot),
          m_lastRecordTime(millis()),
          m_mode(MAIN),
          m_recorder(recorder)
    {
    }

    void RecordMode::init()
    {
        setLEDColor(color::COLOR_WHITE);
        m_mycobotBasic.stop();

        m_mode = MAIN;

        updateVisualization();
    }
    void RecordMode::updateVisualization()
    {
        if (m_mode == MAIN)
        {
            setLEDColor(color::COLOR_WHITE);
            setBigText("Waiting");
            setButtonAText("Free Move");
            setButtonBText("Main");
            setButtonCText("Record");
        }
        else if (m_mode == RECORDING)
        {
            setLEDColor(color::COLOR_ORANGE);
            setBigText("Recording");
            setButtonAText("");
            setButtonBText("");
            setButtonCText("Save");
        }
        else if (m_mode == FREE_MOVE)
        {
            setLEDColor(color::COLOR_BLUE);
            setBigText("FREE MOVE");
            setButtonAText("Stop");
            setButtonBText("");
            setButtonCText("");
        }
    }

    Mode RecordMode::process(RobotState &oldState, RobotState &newState)
    {

        if (m_mode == MAIN)
        {
            if (M5.BtnA.wasPressed())
            {
                m_mode = FREE_MOVE;
                m_mycobotBasic.setFreeMove();
                updateVisualization();
            }

            if (M5.BtnB.wasPressed())
            {
                return MODE_MAIN;
            }

            // start recording
            if (M5.BtnC.wasPressed())
            {
                m_mode = RECORDING;
                m_mycobotBasic.setFreeMove();
                m_recorder->reset();
                m_lastRecordTime = millis();
                updateVisualization();
            }
        }
        else if (m_mode == RECORDING)
        {
            // stop recording
            if (M5.BtnC.wasPressed())
            {
                m_mode = MAIN;
                m_mycobotBasic.stop();
                Log::infof("Saved frames: %d", m_recorder->getRecordNum());
                auto angles = m_recorder->getAngles(0);
                Log::infof("l1: %d, %d, %d, %d, %d, %d",
                           angles.joint_angle[0],
                           angles.joint_angle[1],
                           angles.joint_angle[2],
                           angles.joint_angle[3],
                           angles.joint_angle[4],
                           angles.joint_angle[5]);
                updateVisualization();
            }
        }
        else if (m_mode == FREE_MOVE)
        {
            if (M5.BtnA.wasPressed())
            {
                m_mycobotBasic.stop();
                m_mode = MAIN;
                updateVisualization();
            }
        }

        if (m_mode == RECORDING)
        {
            record::JointAnglesEnc angles;
            angles.delay = millis() - m_lastRecordTime;
            m_lastRecordTime = millis();
            for (int i = 0; i < 6; i++)
            {
                bool wrongVal = true;
                // TODO: not sure if this is the best way
                // we retry 3 times to get a proper value, but
                // technically it should just be there
                for (int x = 0; x < 3 && wrongVal; x++)
                {
                    angles.joint_angle[i] = m_mycobotBasic.getEncoder(i + 1);
                    if (angles.joint_angle[i] != -1)
                    {
                        wrongVal = false;
                    }
                }
                if (wrongVal)
                {
                    Log::errorf("No val for ax %d", i);
                }
            }
            if (m_recorder->record(angles))
            {
                delay(REC_TIME_DELAY - SEND_DATA_GAP);
            }
            else
            {
                m_mode = MAIN;
                m_mycobotBasic.stop();
                updateVisualization();
            }
        }
        return MODE_THIS;
    }

}