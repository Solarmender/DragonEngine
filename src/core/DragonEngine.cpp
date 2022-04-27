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
	planet.orbit(0, 0, 0, 10, 3);
	gameScene->addEntity(&planet);

	Sphere planet2(this);
	planet2.getTransform().setPosition(0, 0, -15);
	planet2.getTransform().setScale(1, 1, 1);
	planet2.orbit(0, 0, 0, 25, 2);
	gameScene->addEntity(&planet2);

	Sphere planet3(this);
	planet3.getTransform().setPosition(0, 0, -15);
	planet3.getTransform().setScale(1, 1, 1);
	planet3.orbit(0, 0, 0, 40, 1);
	gameScene->addEntity(&planet3);

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