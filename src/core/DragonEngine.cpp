#include "DragonEngine.h"
#include "logger/Logger.h"

DragonEngine::DragonEngine() : mainWindow(this), graphics(this)
{
    continueRunning = true;

    Logger::init();
}

DragonEngine::~DragonEngine()
{

}

void DragonEngine::start()
{
    // Setup game

    while(continueRunning)
    {
        if(Window::processMessages())
        {
            return;
        }

        graphics.clearScreen();

        gameScene.update();

        gameScene.render();

        graphics.presentFrame();
    }
}

Window* DragonEngine::getWindow()
{
    return &mainWindow;
}

GraphicsSystem* DragonEngine::getGraphics()
{
    return &graphics;
}

InputSystem* DragonEngine::getInput()
{
    return &input;
}