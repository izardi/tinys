#include "Logger.h"
#include <cstring>
#include <ctime>
#include <cstdarg>
#include <cerrno>
#include <stdexcept>

using namespace tinys::utility;

const char* Logger::s_level[LEVEL_COUNT] {
    "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

Logger* Logger::m_instance = nullptr;

Logger* Logger::instance() { // 可以用once_flag改写
    if (m_instance == nullptr)
        m_instance = new Logger();
    return m_instance;
}


void Logger::log(Level l, const char *file, int line, const char *format, ...) {
    if (m_logos.fail())
        throw std::logic_error("open error" + m_logfilename);
    
    time_t tmt = time(nullptr);
    struct tm* ltm = localtime(&tmt);
    char timestamp[32];
    bzero(timestamp, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ltm);
    
    char BUF[1024];
    int len = snprintf(BUF, sizeof(BUF), "%s [%s] %s : %d",timestamp, s_level[l], file, line);
    BUF[len] = '\0'; 
    m_logos << BUF;
    m_loglen += len;
    
    va_list arg_ptr;
    va_start(arg_ptr, format);
    len = vsnprintf
}

void Logger::open(const string &filename) {
    m_logfilename = filename;
    m_logos.open(filename.c_str(), ios::app);
    if (m_logos.fail()) 
        throw std::logic_error("open error" + filename);
    m_logos.seekp(0, ios::end);
    m_loglen = m_logos.tellp();
}

void Logger::close() {
    m_logos.close();
}