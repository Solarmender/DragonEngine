#ifndef DRAGONENGINE_FILESINK_H
#define DRAGONENGINE_FILESINK_H

#include <fstream>
#include <string>

class FileSink {
public:
    FileSink();
    ~FileSink();

    void write(const std::string& message);
private:
    std::ofstream logFile;
};

#endif //DRAGONENGINE_FILESINK_H