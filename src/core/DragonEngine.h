#ifndef DRAGONENGINE_DRAGONENGINE_H
#define DRAGONENGINE_DRAGONENGINE_H

#include "Windows/Window.h"

class DragonEngine {
public:
    DragonEngine();
    ~DragonEngine();

    void start();
private:
    bool continueRunning;

    Window mainWindow;
};

#endif //DRAGONENGINE_DRAGONENGINE_H