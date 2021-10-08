#include "Window.h"
#include <exception>

Window::Window()
{
    HWND hwnd = CreateWindowExW(
            0,
            WindowsApp::getClassName(),
            L"DragonEngine",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr,
            nullptr,
            WindowsApp::getModule(),
            nullptr
    );

    if(hwnd == nullptr)
    {
        // TODO: Handle Window Errors
        throw std::exception();
    }

    ShowWindow(hwnd, SW_SHOW);
}

Window::~Window()
{
    DestroyWindow(hWnd);
}

bool Window::processMessages()
{
    MSG msg;
    while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if( msg.message == WM_QUIT )
        {
            return true;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return false;
}

HWND Window::getWindow()
{
    return hWnd;
}

LRESULT Window::messageSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::messageForwarder));

        return pWnd->messageHandler(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT Window::messageForwarder(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    return pWnd->messageHandler(hwnd, msg, wParam, lParam);
}

LRESULT Window::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch( msg )
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

WindowsApp::WindowsApp()
{
    appModule = GetModuleHandleW(nullptr);

    WNDCLASSW wc{ };
    wc.lpfnWndProc = Window::messageSetup;
    wc.hInstance = appModule;
    wc.lpszClassName = className;

    RegisterClassW(&wc);
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
