#include "core/DragonEngine.h"
#include "core/logger/Logger.h"
#include "core/windows/MinWindows.h"
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
        MessageBoxA(nullptr, e.what(), "DragonEngine Error", MB_ICONERROR);
        Logger::logException(e.what());

        return 1;
    }
    catch(...)
    {
        MessageBoxA(nullptr, "An unknown exception has occurred", "DragonEngine Error", MB_ICONERROR);
        Logger::logException("");

        return 1;
    }
}