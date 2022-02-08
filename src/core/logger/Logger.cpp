#include "Logger.h"
#include <filesystem>
#include <sstream>
#include <chrono>

std::string getTimeString()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);

    tm localTime{ };
    localtime_s(&localTime, &tt);

    std::stringstream stream;
    stream << "[" << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec << "]";

    return stream.str();
}

void Logger::init()
{
    getSingleton();
}

void Logger::debug(const std::string& message)
{
    getSingleton().logMessage(LogLevel::Debug, message);
}

void Logger::info(const std::string& message)
{
    getSingleton().logMessage(LogLevel::Info, message);
}

void Logger::warn(const std::string& message)
{
    getSingleton().logMessage(LogLevel::Warn, message);
}

void Logger::error(const std::string& message)
{
    getSingleton().logMessage(LogLevel::Error, message);
}

void Logger::logException(const std::string& message)
{
    try
    {
        if(message.empty())
        {
            Logger::error("An unknown exception has occurred");
        }
        else
        {
            Logger::error("An exception has occurred: " + message);
        }
    }
    catch(...)
    {
        // Ummmmmmmmmmm
    }
}

void Logger::logMessage(LogLevel level, const std::string& message)
{
    std::stringstream stream;

    stream << getTimeString() << " ";

    switch(level)
    {
        case LogLevel::Debug:
            stream << "[Debug] ";
            break;
        case LogLevel::Info:
            stream << "[Info] ";
            break;
        case LogLevel::Warn:
            stream << "[Warn] ";
            break;
        case LogLevel::Error:
            stream << "[Error] ";
            break;
    }

    stream << message;

    fileSink.write(stream.str());
}

Logger& Logger::getSingleton()
{
    static Logger logger;
    return logger;
}