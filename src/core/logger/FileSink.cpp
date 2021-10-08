#include "FileSink.h"
#include <sstream>
#include <filesystem>
#include <chrono>

std::string getLogFileName()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);

    tm localTime{ };
    localtime_s(&localTime, &tt);

    std::stringstream stream;
    stream << "./logs/" << localTime.tm_year + 1900 << "-" << localTime.tm_mon + 1 << "-" << localTime.tm_mday;

    for(int i = 1; i < 1000; i++)
    {
        std::string fileName = stream.str() + "-" + std::to_string(i) + ".log";

        if(!std::filesystem::exists(fileName))
        {
            return fileName;
        }
    }

    return "";
}

FileSink::FileSink()
{
    if(!std::filesystem::exists("./logs/"))
    {
        std::filesystem::create_directory("./logs/");
    }

    logFile.open(getLogFileName(), std::ios::out);
    if(!logFile)
    {
        throw std::exception();
    }
}

FileSink::~FileSink()
{
    logFile.close();
}

void FileSink::write(const std::string& message)
{
    logFile << message << std::endl;
}