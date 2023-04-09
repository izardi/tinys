#ifndef _LOGGER_H__
#define _LOGGER_H__

#include <strings.h>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

namespace tinys {
namespace utility {
    
    
#define debug(format, ...) \
    Logger::instance()->log(Logger::DEUBG, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define info(format, ...) \
    Logger::instance()->log(Logger::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define warn(format, ...) \
    Logger::instance()->log(Logger::WARN, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define error(format, ...) \
    Logger::instance()->log(Logger::ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define fatal(format, ...) \
    Logger::instance()->log(Logger::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

class Logger {
public:
    enum Level{
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LEVEL_COUNT
    };

    void open(const string &filename) {
        m_logfilename = filename;
        m_logos.open(m_logfilename.c_str(), ios::app);
        if (m_logos.fail()) { perror("open m_logfilename failed"); exit(1); }

        m_logos.seekp(0, ios::end);
        m_loglen = m_logos.tellp();
    }

    void close() {
        m_logos.close();
    }
    
    void log(Level l, const char* file, int line, const char* format, ...) {
        if (l < m_level) return; // 只记录>= m_level的日志信息

        time_t ticks = time(NULL);      
        struct tm* ltm = localtime(&ticks);
        char timestamp[32];
        bzero(&timestamp, sizeof(timestamp));
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ltm);



    }
    
    void level(int level) {
        m_level = level;
    }

    static Logger* instance() { // 可以用once_flag改写
        if (m_instance == nullptr)
            m_instance = new Logger();
        return m_instance;
    }

private:
    static Logger* m_instance;

    const char* s_level[LEVEL_COUNT] {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

    string m_logfilename;
    ofstream m_logos;
    int m_loglen;
    int m_level;
};

Logger* Logger::m_instance = nullptr;

}
}

#endif