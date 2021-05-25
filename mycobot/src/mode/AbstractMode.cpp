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
    void AbstractMode::visualize()
    {
        if(!m_visualizeUpdate && !ModeLogger::needsRefresh())
        {
            return;
        }
        M5.Lcd.clear(BLACK);
        M5.Lcd.setTextSize(5);
        M5.Lcd.setCursor(100, 100);
        M5.Lcd.print(m_bigText);
        M5.Lcd.setTextSize(2);
        if(!m_buttonAText.isEmpty())
        {
            M5.Lcd.setCursor(30, 210);
            M5.Lcd.print(m_buttonAText);
        }
        if(!m_buttonBText.isEmpty())
        {
            M5.Lcd.setCursor(120, 210);
            M5.Lcd.print(m_buttonBText);
        }
        if(!m_buttonCText.isEmpty())
        {
            M5.Lcd.setCursor(230, 210);
            M5.Lcd.print(m_buttonCText);
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
        m_visualizeUpdate = true;
    }

    void AbstractMode::setButtonAText(String text)
    {
        if(m_buttonAText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonAText = text;
        m_visualizeUpdate = true;
    }

    void AbstractMode::setButtonBText(String text)
    {
        if(m_buttonBText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonBText = text;
        m_visualizeUpdate = true;
    }

    void AbstractMode::setButtonCText(String text)
    {
        if(m_buttonCText.compareTo(text) == 0)
        {
            return;
        }
        m_buttonCText = text;
        m_visualizeUpdate = true;
    }
}