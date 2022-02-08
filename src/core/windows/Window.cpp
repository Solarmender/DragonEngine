#include "Window.h"
#include "../DragonEngine.h"
#include "../logger/Logger.h"
#include <stdexcept>

Window::Window(DragonEngine* parentEngine)
{
    engine = parentEngine;

    windowHandle = CreateWindowExW(
            0,
            WindowsApp::getClassName(),
            L"DragonEngine",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr,
            nullptr,
            WindowsApp::getModule(),
            this
    );

    if(windowHandle == nullptr)
    {
        throw std::runtime_error("Failed to create window");
    }

    ShowWindow(windowHandle, SW_SHOW);
}

Window::~Window()
{
    DestroyWindow(windowHandle);
}

bool Window::processMessages()
{
    MSG msg;
    while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if(msg.message == WM_QUIT)
        {
            LOGGER_DEBUG("WM_QUIT Received");
            return true;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return false;
}

HWND Window::getWindow()
{
    return windowHandle;
}

RECT Window::getWindowSize()
{
    RECT clientRect{ };
    if(!GetClientRect(engine->getWindow()->getWindow(), &clientRect))
    {
        throw std::runtime_error("Failed to get window size");
    }

    return clientRect;
}

LRESULT Window::messageSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if(msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::messageForwarder));

        pWnd->windowHandle = hwnd;
        return pWnd->messageHandler(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT Window::messageForwarder(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    return pWnd->messageHandler(hwnd, msg, wParam, lParam);
}

LRESULT Window::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch(msg)
    {
        case WM_SIZE:
            if(engine->getGraphics())
            {
                engine->getGraphics()->onResize();
            }
            break;
        case WM_CLOSE:
            LOGGER_DEBUG("WM_CLOSE Received");
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            engine->getInput()->keyPressed(wParam);
            break;
        case WM_KEYUP:
            engine->getInput()->keyReleased(wParam);
            break;
        case WM_GETMINMAXINFO:
            MINMAXINFO* info = reinterpret_cast<MINMAXINFO*>(lParam);
            info->ptMinTrackSize.x = 320;
            info->ptMinTrackSize.y = 200;
            break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

WindowsApp::WindowsApp()
{
    appModule = GetModuleHandleW(nullptr);

    WNDCLASSEXW wcex{ };
    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = 0;
    wcex.lpfnWndProc = Window::messageSetup;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = appModule;
    wcex.hIcon = nullptr;
    wcex.hCursor = nullptr;
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = className;
    wcex.hIconSm = nullptr;

    RegisterClassExW(&wcex);
}

WindowsApp::~WindowsApp()
{
    UnregisterClassW(className, appModule);
}

HMODULE WindowsApp::getModule()
{
    return getSingleton().appModule;
}

const wchar_t* WindowsApp::getClassName()
{
    return className;
}

WindowsApp& WindowsApp::getSingleton()
{
    static WindowsApp appInstance;
    return appInstance;
}