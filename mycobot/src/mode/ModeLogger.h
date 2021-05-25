#ifndef MODE_LOGGER_H
#define MODE_LOGGER_H
#include <Log.h>
#include "Deque.h"

class ModeLogger : public ILogger
{
public:
    ModeLogger()
        : m_maxLines(5), 
        m_logs()
          
    {
        m_instance = this;
    }
    void debug(const char *str) override
    {
        addLine("[DEBUG] " + String(str));
    }

    void info(const char *str) override
    {
        addLine("[INFO] " + String(str));
    }

    void warn(const char *str) override
    {
        addLine("[WARN] " + String(str));
    }

    void error(const char *str) override
    {
        addLine("[ERROR] " + String(str));
    }

    void addLine(String str)
    {
        m_logs.push_back(str);
        while (m_logs.count() > m_maxLines)
        {
            m_logs.pop_front();
        }
        m_needsRefresh = true;
    }

    static bool isInitialized()
    {
        return m_instance != nullptr;
    }

    static String getLines()
    {
        if(!isInitialized())
        {
            return "";
        }
        String ret = "";
        for(int i = 0; i < m_instance->m_logs.count(); i++)
        {
            ret += m_instance->m_logs[i] + "\n";
        }
        return ret;
    }

    static bool needsRefresh()
    {
        return m_needsRefresh;
    }

    static void resetNeedsRefresh()
    {
        m_needsRefresh = false;
    }

private:
    unsigned int m_maxLines;
    Deque<String> m_logs;
    static ModeLogger *m_instance;
    static bool m_needsRefresh;
};

#endif