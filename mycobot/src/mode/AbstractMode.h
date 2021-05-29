#pragma once
#include <MycobotBasic.h>
#include "State.h"
#include "Mode.h"

namespace cobot
{

    namespace color
    {
        class Color
        {
        public:
            byte R = 255;
            byte G = 255;
            byte B = 255;

            Color(byte r, byte g, byte b)
                : R(r),
                  G(g),
                  B(b)
            {
            }

            bool operator==(const Color &other)
            {
                return (R == other.R &&
                        G == other.G &&
                        B == other.B);
            }

            bool operator!=(const Color &other)
            {
                return !(*this == other);
            }
        };
        static const Color COLOR_RED(255, 0, 0);
        static const Color COLOR_BLUE(0, 0, 255);
        static const Color COLOR_WHITE(255, 255, 255);
        static const Color COLOR_ORANGE(255, 165, 0);

        // TODO: implement comperator
    }

    class AbstractMode : public IMode
    {
    public:
        // called after switching to the mode
        virtual void init() = 0;

        virtual void visualize();
        void forceNextVisualizationUpdate();
        virtual ~AbstractMode(){};
        
    protected:
        AbstractMode(MycobotBasic &myCobot);
        void setBigText(String text);
        void setButtonAText(String text);
        void setButtonBText(String text);
        void setButtonCText(String text);
        void setLEDColor(color::Color color);

        void visualizeLED();
        virtual void visualizeUI();
        void forceNextUIUpdate();
        void forceNextLEDUpdate();
    private:
        MycobotBasic m_mycobotBasic;

        bool m_visualizeUIUpdate;
        bool m_visualizeLEDUpdate;
        String m_bigText;
        String m_buttonAText;
        String m_buttonBText;
        String m_buttonCText;
        color::Color m_ledColor;
    };

}
