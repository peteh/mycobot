#include "PlayRecordMode.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <Log.h>

namespace cobot
{
    PlayRecordMode::PlayRecordMode(Cobot &myCobot, record::Recorder *recorder)
        : AbstractMode(myCobot),
          m_lastRecordTime(millis()),
          m_playingRecord(false),
          m_playingIndex(0),
          m_recorder(recorder)
    {
    }

    void PlayRecordMode::init()
    {
        m_playingRecord = false;
        m_playingIndex = 0;

        getCobot().getBase().jogStop();
        updateVisualization();
    }
    void PlayRecordMode::updateVisualization()
    {
        if(m_playingRecord)
        {
            setLEDColor(color::COLOR_BLUE);
            setBigText("Replaying");
            setButtonAText("Stop");
            setButtonBText("");
        }
        else
        {
            setLEDColor(color::COLOR_WHITE);
            setBigText("Waiting");
            setButtonAText("Replay");
            setButtonBText("Main");
        }
    }

    Mode PlayRecordMode::process(RobotState &oldState, RobotState &newState)
    {

        if(m_playingRecord)
        {
            // stop playing
            if(M5.BtnA.wasPressed())
            {
                m_playingRecord = false;
                getCobot().getBase().jogStop();
                getCobot().getSuctionPump().unsuck();
                updateVisualization();
            }
        }
        else
        {
            // start playing
            if(M5.BtnA.wasPressed())
            {
                m_playingRecord = true;
                m_playingIndex = 0;
                updateVisualization();
            }

            if(M5.BtnB.wasPressed())
            {
                return MODE_MAIN;
            }
        }

        if (m_playingRecord)
        {
            if(m_playingIndex < m_recorder->getRecordNum() )
            {
                record::JointAnglesEnc angles = m_recorder->getAngles(m_playingIndex);
                delay(angles.delay);

                if(getCobot().getSuctionPump().isSucking() != angles.pump)
                {
                    if(angles.pump)
                    {
                        getCobot().getSuctionPump().suck();
                    }
                    else
                    {
                        getCobot().getSuctionPump().unsuck();
                    }
                }
                Angles encoders;
                for (int i = 0; i < 6; i++){
                    encoders[i] = angles.joint_angle[i];
                }
                getCobot().getBase().setEncoders(encoders, 80);
                
                m_playingIndex++;
            }
            else
            {
                m_playingRecord = false;
                updateVisualization();
            }
            
        }
        return MODE_THIS;
    }

}