#ifndef DRAGONENGINE_DRAGONENGINE_H
#define DRAGONENGINE_DRAGONENGINE_H

#include "windows/Window.h"
#include "graphics/GraphicsSystem.h"
#include "input/InputSystem.h"
#include "entities/Scene.h"

class DragonEngine {
public:
    DragonEngine();
    ~DragonEngine();

    void start();

    Window* getWindow();
    GraphicsSystem* getGraphics();
    InputSystem* getInput();
	Scene* getScene();
private:
    bool continueRunning;

    Window* mainWindow;
    GraphicsSystem* graphics;
    InputSystem* input;
    Scene* gameScene;
};

#endif //DRAGONENGINE_DRAGONENGINE_H