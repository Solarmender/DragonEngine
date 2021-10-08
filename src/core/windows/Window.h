#ifndef DRAGONENGINE_WINDOW_H
#define DRAGONENGINE_WINDOW_H

#include "MinWindows.h"

class Window {
public:
    Window();
    ~Window();

    static bool processMessages();

    HWND getWindow();
private:
    HWND hWnd;

    static LRESULT CALLBACK messageSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK messageForwarder(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    friend class WindowsApp;
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