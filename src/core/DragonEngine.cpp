#include "DragonEngine.h"
#include "logger/Logger.h"

DragonEngine::DragonEngine()
{
    continueRunning = true;

    mainWindow = nullptr;
    graphics = nullptr;
    input = nullptr;
    gameScene = nullptr;

    mainWindow = new Window(this);
    graphics = new GraphicsSystem(this);
    input = new InputSystem();
    gameScene = new Scene();

    Logger::init();
}

DragonEngine::~DragonEngine()
{
    delete gameScene;
    delete input;
    delete graphics;
    delete mainWindow;
}

void DragonEngine::start()
{
    // Setup game

    while(continueRunning)
    {
        if(Window::processMessages())
        {
            continueRunning = false;
            break;
        }

        graphics->clearScreen();

        gameScene->update();

        gameScene->render();

        graphics->presentFrame();
    }
}

Window* DragonEngine::getWindow()
{
    return mainWindow;
}

GraphicsSystem* DragonEngine::getGraphics()
{
    return graphics;
}

InputSystem* DragonEngine::getInput()
{
    return input;
}