#ifndef ABSTRACT_MODE_H
#define ABSTRACT_MODE_H

#include "State.h"
#include "Mode.h"

namespace cobot
{

    class AbstractMode : public IMode
    {
    public:
        // called after switching to the mode
        AbstractMode();
        virtual void init() = 0;
        virtual void visualize();
        void forceNextVisualizationUpdate();
        virtual ~AbstractMode(){};

    protected: 
        void setBigText(String text);
        void setButtonAText(String text);
        void setButtonBText(String text);
        void setButtonCText(String text);

    private:
        bool m_visualizeUpdate;
        String m_bigText;
        String m_buttonAText;
        String m_buttonBText;
        String m_buttonCText;
    };

}

#endif