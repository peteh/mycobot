#include "AbstractMode.h"
#include "ModeLogger.h"

#include <M5Stack.h>

namespace cobot
{
    AbstractMode::AbstractMode()
        : m_visualizeUpdate(true),
        m_buttonAText(""),
          m_buttonBText(""),
          m_buttonCText("")
          
    {
    }


    void AbstractMode::forceNextVisualizationUpdate()
    {
        m_visualizeUpdate = true;
    }

    void AbstractMode::visualize()
    {
        if(!m_visualizeUpdate && !ModeLogger::needsRefresh())
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
        if(!m_bigText.isEmpty())
        {
            M5.Lcd.setTextSize(5);
            M5.Lcd.setTextDatum(MC_DATUM);
            M5.Lcd.drawString(m_bigText, screenWidth / 2 , screenHeight / 2 );
        }
        M5.Lcd.setTextSize(2);
        if(!m_buttonAText.isEmpty())
        {
            M5.Lcd.setTextDatum(BC_DATUM);
            M5.Lcd.drawString(m_buttonAText, 60, screenHeight);
        }
        if(!m_buttonBText.isEmpty())
        {
            M5.Lcd.setTextDatum(BC_DATUM);
            M5.Lcd.drawString(m_buttonBText, 160, screenHeight);
        }
        if(!m_buttonCText.isEmpty())
        {
            M5.Lcd.setTextDatum(BC_DATUM);
            M5.Lcd.drawString(m_buttonCText, 260, screenHeight);
        }

        M5.Lcd.setCursor(0, 0);

        // TODO: do this more dynamically
        M5.Lcd.print(ModeLogger::getLines().c_str());    
       
        m_visualizeUpdate = false;
        ModeLogger::resetNeedsRefresh();
    }

    void AbstractMode::setBigText(String text)
    {
        if(m_bigText.compareTo(text) == 0)
        {
            return;
        }
        m_bigText = text;
        forceNextVisualizationUpdate();
    }

    void AbstractMode::setButtonAText(String text)
    {
        if(m_buttonAText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonAText = text;
        forceNextVisualizationUpdate();
    }

    void AbstractMode::setButtonBText(String text)
    {
        if(m_buttonBText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonBText = text;
        forceNextVisualizationUpdate();
    }

    void AbstractMode::setButtonCText(String text)
    {
        if(m_buttonCText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonCText = text;
        forceNextVisualizationUpdate();
    }
}