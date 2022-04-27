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
	playerCamera.getTransform().setPosition(0, 0, -100);
	gameScene->addEntity(&playerCamera);
	gameScene->setCamera(&playerCamera);

    Sphere sun(this);
	sun.getTransform().setScale(3, 3, 3);
    gameScene->addEntity(&sun);

	Sphere planet(this);
	planet.getTransform().setPosition(0, 0, -15);
	planet.getTransform().setScale(1, 1, 1);
	planet.orbit(0, 0, 0);
	gameScene->addEntity(&planet);

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