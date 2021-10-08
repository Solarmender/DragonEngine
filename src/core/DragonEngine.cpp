#include "DragonEngine.h"
#include "logger/Logger.h"

DragonEngine::DragonEngine() : mainWindow(this)
{
    continueRunning = true;

    Logger::init();
}

DragonEngine::~DragonEngine()
{

}

void DragonEngine::start()
{
    while(continueRunning)
    {
        if(Window::processMessages())
        {
            return;
        }

        if( input.isPressed( 'A' ))
        {
            throw std::exception();
        }

        // Other loop things
    }
}

Window* DragonEngine::getWindow()
{
    return &mainWindow;
}

InputSystem* DragonEngine::getInput()
{
    return &input;
}