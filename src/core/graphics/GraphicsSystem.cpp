#include "GraphicsSystem.h"
#include "../DragonEngine.h"
#include <stdexcept>

GraphicsSystem::GraphicsSystem(DragonEngine* parentEngine)
{
    engine = parentEngine;

    swapchain = nullptr;
    device = nullptr;
    deviceContext = nullptr;
    backbuffer = nullptr;

    RECT clientRect{ };
    if(!GetClientRect(engine->getWindow()->getWindow(), &clientRect))
    {
        throw std::runtime_error("Failed to get window size");
    }
    clientWidth = clientRect.right - clientRect.left;
    clientHeight = clientRect.bottom - clientRect.top;

    initDevice();
    initBackbuffer();
    setViewport();
}

GraphicsSystem::~GraphicsSystem()
{
    cleanupBackbuffer();
    cleanupDevice();
}

void GraphicsSystem::clearScreen()
{
    const float color[] = { 0.0f, 0.2f, 0.4f, 1.0f};
    deviceContext->ClearRenderTargetView(backbuffer, color);
}

void GraphicsSystem::presentFrame()
{
    swapchain->Present(0, 0);
}

void GraphicsSystem::initDevice()
{
    DXGI_SWAP_CHAIN_DESC swapDesc{ };
    swapDesc.BufferCount = 1;
    swapDesc.BufferDesc.Width = clientWidth;
    swapDesc.BufferDesc.Height = clientHeight;
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.OutputWindow = engine->getWindow()->getWindow();
    swapDesc.SampleDesc.Count = 1;
    swapDesc.SampleDesc.Quality = 0;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapDesc.Windowed = TRUE;

    const D3D_FEATURE_LEVEL featureLevelRequest[1] = { D3D_FEATURE_LEVEL_11_0 };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevelRequest, ARRAYSIZE(featureLevelRequest), D3D11_SDK_VERSION, &swapDesc, &swapchain, &device, nullptr, &deviceContext);
    if(FAILED(hr))
    {
        throw std::runtime_error("Failed to create device/swapchain");
    }
}

void GraphicsSystem::cleanupDevice()
{
    swapchain->Release();
    device->Release();
    deviceContext->Release();
}

void GraphicsSystem::initBackbuffer()
{
    ID3D11Texture2D* tempBackbuffer = nullptr;

    HRESULT hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&tempBackbuffer);
    if(FAILED(hr))
    {
        throw std::runtime_error("Failed to get backbuffer");
    }

    hr = device->CreateRenderTargetView(tempBackbuffer, nullptr, &backbuffer);
    if(FAILED(hr))
    {
        throw std::runtime_error("Failed to get backbuffer");
    }

    tempBackbuffer->Release();

    deviceContext->OMSetRenderTargets(1, &backbuffer, nullptr);
}

void GraphicsSystem::cleanupBackbuffer()
{
    backbuffer->Release();
}

void GraphicsSystem::setViewport()
{
    RECT rect;
    GetWindowRect( engine->getWindow()->getWindow(), &rect);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    D3D11_VIEWPORT viewport{ };
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    viewport.Width = (float)windowWidth;
    viewport.Height = (float)windowHeight;

    deviceContext->RSSetViewports(1, &viewport);
}