#ifndef DRAGONENGINE_DRAGONENGINE_H
#define DRAGONENGINE_DRAGONENGINE_H

#include "windows/Window.h"
#include "graphics/GraphicsSystem.h"
#include "input/InputSystem.h"

class DragonEngine {
public:
    DragonEngine();
    ~DragonEngine();

    void start();

    Window* getWindow();
    GraphicsSystem* getGraphics();
    InputSystem* getInput();
private:
    bool continueRunning;

    Window mainWindow;
    GraphicsSystem graphics;
    InputSystem input;
};

#endif //DRAGONENGINE_DRAGONENGINE_H