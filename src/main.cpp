#include "core/DragonEngine.h"
#include "core/Windows/MinWindows.h"
#include <exception>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    try
    {
        DragonEngine engine;
        engine.start();

        return 0;
    }
    catch(std::exception& e)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }
}