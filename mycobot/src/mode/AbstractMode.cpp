#include "AbstractMode.h"
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
        if(!m_visualizeUpdate)
        {
            return;
        }
        M5.Lcd.clear(BLACK);
        M5.Lcd.setTextSize(5);
        M5.Lcd.setCursor(100, 100);
        M5.Lcd.print("test");
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
        m_visualizeUpdate = false;
    }

    void AbstractMode::setButtonAText(String text)
    {
        m_buttonAText = text;
        m_visualizeUpdate = true;
    }

    void AbstractMode::setButtonBText(String text)
    {
        m_buttonBText = text;
        m_visualizeUpdate = true;
    }

    void AbstractMode::setButtonCText(String text)
    {
        m_buttonCText = text;
        m_visualizeUpdate = true;
    }
}