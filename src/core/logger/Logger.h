#ifndef DRAGONENGINE_LOGGER_H
#define DRAGONENGINE_LOGGER_H

#include "FileSink.h"
#include <string>

class Logger {
public:
    ~Logger() = default;

    static void init();

    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

    static void logException(const std::string& message);

    enum class LogLevel
    {
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

#endif //DRAGONENGINE_LOGGER_H