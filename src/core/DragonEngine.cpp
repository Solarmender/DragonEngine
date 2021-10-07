#include "DragonEngine.h"

DragonEngine::DragonEngine()
{
    continueRunning = true;
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