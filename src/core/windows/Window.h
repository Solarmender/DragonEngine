#ifndef DRAGONENGINE_WINDOW_H
#define DRAGONENGINE_WINDOW_H

#include "MinWindows.h"

class DragonEngine;

class Window {
public:
    explicit Window(DragonEngine* parentEngine);
    ~Window();

    static bool processMessages();

    HWND getWindow();

    RECT getWindowSize();

    static LRESULT CALLBACK messageSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    static LRESULT CALLBACK messageForwarder(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
    HWND windowHandle;

    DragonEngine* engine;
};

// Singleton that represents win32 app
class WindowsApp {
public:
    ~WindowsApp();

    static HMODULE getModule();
    static const wchar_t* getClassName();
private:
    WindowsApp();

    HMODULE appModule;
    static constexpr const wchar_t* className = L"DragonEngineClass";

    static WindowsApp& getSingleton();
};

#endif //DRAGONENGINE_WINDOW_H