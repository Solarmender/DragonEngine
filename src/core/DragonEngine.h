#ifndef DRAGONENGINE_DRAGONENGINE_H
#define DRAGONENGINE_DRAGONENGINE_H

#include "windows/Window.h"
#include "input/InputSystem.h"

class DragonEngine {
public:
    DragonEngine();
    ~DragonEngine();

    void start();

    Window* getWindow();
    InputSystem* getInput();
private:
    bool continueRunning;

    Window mainWindow;
    InputSystem input;
};

#endif //DRAGONENGINE_DRAGONENGINE_H