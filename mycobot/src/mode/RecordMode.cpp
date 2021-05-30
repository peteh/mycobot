#include "RecordMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>

namespace cobot
{
    RecordMode::RecordMode(Cobot &myCobot, record::Recorder *recorder)
        : AbstractMode(myCobot),
          m_lastRecordTime(millis()),
          m_mode(MAIN),
          m_recorder(recorder)
    {
    }

    void RecordMode::init()
    {
        setLEDColor(color::COLOR_WHITE);
        getCobot().getBase().stop();

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
            if (getCobot().getSuctionPump().isSucking())
            {
                setButtonBText("Unsuck");
            }
            else
            {
                setButtonBText("Suck");
            }
            setButtonCText("Save");
        }
        else if (m_mode == FREE_MOVE)
        {
            setLEDColor(color::COLOR_BLUE);
            setBigText("FREE MOVE");
            setButtonAText("Stop");
            if (getCobot().getSuctionPump().isSucking())
            {
                setButtonBText("Unsuck");
            }
            else
            {
                setButtonBText("Suck");
            }
            setButtonCText("");
        }
    }

    void RecordMode::stopRecording()
    {
        m_mode = MAIN;
        getCobot().getBase().stop();
        getCobot().getSuctionPump().unsuck();
        Log::infof("Saved frames: %d", m_recorder->getRecordNum());
        auto angles = m_recorder->getAngles(0);
        Log::infof("l1: %d, %d, %d, %d, %d, %d",
                   angles.joint_angle[0],
                   angles.joint_angle[1],
                   angles.joint_angle[2],
                   angles.joint_angle[3],
                   angles.joint_angle[4],
                   angles.joint_angle[5]);

        m_recorder->saveToFile();
        updateVisualization();
    }
    Mode RecordMode::process(RobotState &oldState, RobotState &newState)
    {

        if (m_mode == MAIN)
        {
            if (M5.BtnA.wasPressed())
            {
                m_mode = FREE_MOVE;
                getCobot().getBase().setFreeMove();
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
                getCobot().getBase().setFreeMove();
                m_recorder->reset();
                m_lastRecordTime = millis();
                updateVisualization();
            }
        }
        else if (m_mode == RECORDING)
        {
            // handle suction
            if (M5.BtnB.wasPressed())
            {
                if (getCobot().getSuctionPump().isSucking())
                {
                    getCobot().getSuctionPump().unsuck();
                }
                else
                {
                    getCobot().getSuctionPump().suck();
                }
                updateVisualization();
            }

            // stop recording
            if (M5.BtnC.wasPressed())
            {
                stopRecording();
            }
        }
        else if (m_mode == FREE_MOVE)
        {
            if (M5.BtnA.wasPressed())
            {
                getCobot().getBase().stop();
                m_mode = MAIN;
                updateVisualization();
            }

            // handle suction
            if (M5.BtnB.wasPressed())
            {
                if (getCobot().getSuctionPump().isSucking())
                {
                    getCobot().getSuctionPump().unsuck();
                }
                else
                {
                    getCobot().getSuctionPump().suck();
                }
                updateVisualization();
            }
        }

        if (m_mode == RECORDING)
        {
            record::JointAnglesEnc angles;
            angles.delay = millis() - m_lastRecordTime;
            m_lastRecordTime = millis();

            angles.pump = getCobot().getSuctionPump().isSucking();

            for (int i = 0; i < 6; i++)
            {
                bool wrongVal = true;
                // TODO: not sure if this is the best way
                // we retry 3 times to get a proper value, but
                // technically it should just be there
                for (int x = 0; x < 3 && wrongVal; x++)
                {
                    angles.joint_angle[i] = getCobot().getBase().getEncoder(i + 1);
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
                // buffer is full or we failed to write for other reason
                stopRecording();
            }
        }
        return MODE_THIS;
    }

}