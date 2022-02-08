#ifndef DRAGONENGINE_LOGGER_H
#define DRAGONENGINE_LOGGER_H

#include "FileSink.h"
#include <string>

class Logger {
public:
    static void init();

    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

    static void logException(const std::string& message);

    enum class LogLevel
    {
        Debug,
        Info,
        Warn,
        Error
    };
private:
    Logger() = default;

    void logMessage(LogLevel level, const std::string& message);

    FileSink fileSink;

    static Logger& getSingleton();
};

#ifdef _DEBUG
#define LOGGER_DEBUG(message) Logger::debug(message)
#elif
#define LOGGER_DEBUG(message) {}
#endif

#endif //DRAGONENGINE_LOGGER_H