#include "AbstractMode.h"
#include "ModeLogger.h"

#include <M5Stack.h>

namespace cobot
{
    AbstractMode::AbstractMode(Cobot &myCobot)
        : m_myCobot(myCobot),
          m_visualizeUIUpdate(true),
          m_visualizeLEDUpdate(true),
          m_buttonAText(""),
          m_buttonBText(""),
          m_buttonCText(""),
          m_ledColor(color::COLOR_WHITE)
    {
    }

    Cobot& AbstractMode::getCobot()
    {
        return m_myCobot;
    }
    void AbstractMode::forceNextVisualizationUpdate()
    {
        forceNextLEDUpdate();
        forceNextUIUpdate();
    }
    void AbstractMode::forceNextLEDUpdate()
    {
        m_visualizeLEDUpdate = true;
    }
     
    void AbstractMode::forceNextUIUpdate()
    {
        m_visualizeUIUpdate = true;
    }

    void AbstractMode::visualize()
    {
        visualizeLED();
        visualizeUI();
    }

    void AbstractMode::visualizeLED()
    {
        if (!m_visualizeLEDUpdate)
        {
            return;
        }
        delay(50);
        m_myCobot.getBase().setLEDRGB(m_ledColor.R, m_ledColor.G, m_ledColor.B);
        delay(50);
        m_visualizeLEDUpdate = false;
    }

    void AbstractMode::visualizeUI()
    {
        // TODO: do we need button feebdack?
        //if(M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed())
        //{
        //    M5.Speaker.tone(400, 10); 
        //}
        
        if (!m_visualizeUIUpdate && !ModeLogger::needsRefresh())
        {
            return;
        }
        /*
        TFT_eSprite spr = TFT_eSprite(&M5.Lcd);
        spr.createSprite(100, 100);

        spr.fillSprite(TFT_BLACK);
        spr.setTextSize(5);
        spr.setCursor(100, 100);
        spr.print(m_bigText);
        spr.setTextSize(2);
        if(!m_buttonAText.isEmpty())
        {
            spr.setCursor(30, 210);
            spr.print(m_buttonAText);
        }
        if(!m_buttonBText.isEmpty())
        {
            spr.setCursor(120, 210);
            spr.print(m_buttonBText);
        }
        if(!m_buttonCText.isEmpty())
        {
            spr.setCursor(230, 210);
            spr.print(m_buttonCText);
        }

        spr.setCursor(0, 0);

        // TODO: do this more dynamically
        spr.print(ModeLogger::getLines().c_str());
        spr.pushSprite(0,0);
        */
        M5.Lcd.clear(BLACK);

        int16_t screenWidth = M5.Lcd.width();
        int16_t screenHeight = M5.Lcd.height();
        if (!m_bigText.isEmpty())
        {
            M5.Lcd.setTextSize(5);
            M5.Lcd.setTextDatum(MC_DATUM);
            M5.Lcd.drawString(m_bigText, screenWidth / 2, screenHeight / 2);
        }
        M5.Lcd.setTextSize(2);
        if (!m_buttonAText.isEmpty())
        {
            M5.Lcd.setTextDatum(BC_DATUM);
            M5.Lcd.drawString(m_buttonAText, 60, screenHeight);
        }
        if (!m_buttonBText.isEmpty())
        {
            M5.Lcd.setTextDatum(BC_DATUM);
            M5.Lcd.drawString(m_buttonBText, 160, screenHeight);
        }
        if (!m_buttonCText.isEmpty())
        {
            M5.Lcd.setTextDatum(BC_DATUM);
            M5.Lcd.drawString(m_buttonCText, 260, screenHeight);
        }

        M5.Lcd.setCursor(0, 0);

        // TODO: do this more dynamically
        M5.Lcd.print(ModeLogger::getLines().c_str());

        m_visualizeUIUpdate = false;
        ModeLogger::resetNeedsRefresh();
    }

    void AbstractMode::setBigText(String text)
    {
        if (m_bigText.compareTo(text) == 0)
        {
            return;
        }
        m_bigText = text;
        forceNextUIUpdate();
    }

    void AbstractMode::setButtonAText(String text)
    {
        if (m_buttonAText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonAText = text;
        forceNextUIUpdate();
    }

    void AbstractMode::setButtonBText(String text)
    {
        if (m_buttonBText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonBText = text;
        forceNextUIUpdate();
    }

    void AbstractMode::setButtonCText(String text)
    {
        if (m_buttonCText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonCText = text;
        forceNextUIUpdate();
    }

    void AbstractMode::setLEDColor(color::Color color)
    {
        if (m_ledColor == color)
        {
            return;
        }
        m_ledColor = color;
        forceNextLEDUpdate();
    }
}