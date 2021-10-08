#include "DragonEngine.h"
#include "logger/Logger.h"

DragonEngine::DragonEngine()
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

        // Other loop things
    }
}