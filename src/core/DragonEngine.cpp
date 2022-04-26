#include "DragonEngine.h"
#include "logger/Logger.h"
#include "graphics/cube/Cube.h"
#include "graphics/sphere/Sphere.h"
#include "entities/Camera.h"

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
	Camera playerCamera(this);
	gameScene->addEntity(&playerCamera);
	gameScene->setCamera(&playerCamera);

	Cube gameCube(this);
    Cube gameCube2(this);
    gameCube2.getTransform().moveAbsolute(5, 0, 0);
    Cube gameCube3(this);
    gameCube3.getTransform().moveAbsolute(0, -5, 0);

    Sphere gameSphere(this);
    gameSphere.getTransform().moveAbsolute(0, 0, 5);

	gameScene->addEntity(&gameCube);
    gameScene->addEntity(&gameCube2);
    gameScene->addEntity(&gameCube3);
    gameScene->addEntity(&gameSphere);

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

Scene* DragonEngine::getScene()
{
	return gameScene;
}