#include "GraphicsSystem.h"
#include "../DragonEngine.h"
#include "../logger/Logger.h"
#include <stdexcept>

GraphicsSystem::GraphicsSystem(DragonEngine* parentEngine)
{
    engine = parentEngine;

    initDevice();
	initRenderTarget();
	initDepthStencil();
    setViewport();
}

GraphicsSystem::~GraphicsSystem()
{
	cleanupDepthStencil();
	cleanupRenderTarget();
    cleanupDevice();
}

void GraphicsSystem::clearScreen()
{
    const float color[] = { 0.0f, 0.2f, 0.4f, 1.0f};
    deviceContext->ClearRenderTargetView(renderTarget, color);

	deviceContext->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0);

	deviceContext->OMSetRenderTargets(1, &renderTarget, depthStencil);
}

void GraphicsSystem::presentFrame()
{
    HRESULT hr = swapchain->Present(0, 0);
	if(FAILED(hr))
	{
		throw std::runtime_error("Failed to present frame");
	}

}

void GraphicsSystem::onResize()
{
	if(swapchain)
	{
		deviceContext->OMSetRenderTargets(0, nullptr, nullptr);

		cleanupDepthStencil();
		cleanupRenderTarget();

		HRESULT hr = swapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		if(FAILED(hr))
		{
			throw std::runtime_error("Failed to resize swapchain");
		}

		initRenderTarget();
		initDepthStencil();

		deviceContext->OMSetRenderTargets(1, &renderTarget, depthStencil);

		setViewport();
	}
}

ID3D11Device* GraphicsSystem::getDevice()
{
	return device;
}

ID3D11DeviceContext* GraphicsSystem::getDeviceContext()
{
	return deviceContext;
}

void GraphicsSystem::initDevice()
{
    RECT clientRect = engine->getWindow()->getWindowSize();

    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;

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
    deviceContext->Release();
    device->Release();
}

void GraphicsSystem::initRenderTarget()
{
	ID3D11Texture2D* backBuffer;

	HRESULT hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	if(FAILED(hr))
	{
		throw std::runtime_error("Failed to get swapchain backbuffer");
	}

    hr = device->CreateRenderTargetView(backBuffer, nullptr, &renderTarget);
    if(FAILED(hr))
    {
        throw std::runtime_error("Failed to create backbuffer");
    }

	backBuffer->Release();
}

void GraphicsSystem::cleanupRenderTarget()
{
	deviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	renderTarget->Release();

	deviceContext->Flush();
}

void GraphicsSystem::initDepthStencil()
{
	RECT rect;
	GetWindowRect( engine->getWindow()->getWindow(), &rect);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	D3D11_TEXTURE2D_DESC depthStencilDesc{ };
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Width = windowWidth;
	depthStencilDesc.Height = windowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D* tempDepthBuffer;
	device->CreateTexture2D(&depthStencilDesc, nullptr, &tempDepthBuffer);

	device->CreateDepthStencilView(tempDepthBuffer, nullptr, &depthStencil);

	tempDepthBuffer->Release();

	ID3D11DepthStencilState* depthStencilState;

	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc{ };
	depthStencilStateDesc.DepthEnable = TRUE;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;

	device->CreateDepthStencilState(&depthStencilStateDesc, &depthStencilState);
	deviceContext->OMSetDepthStencilState(depthStencilState, 0);

	ID3D11RasterizerState* rasterizerState;

	D3D11_RASTERIZER_DESC rasterizerStateDesc{ };
	rasterizerStateDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerStateDesc.CullMode = D3D11_CULL_BACK;
	rasterizerStateDesc.FrontCounterClockwise = TRUE;

	device->CreateRasterizerState(&rasterizerStateDesc, &rasterizerState);
	deviceContext->RSSetState(rasterizerState);
}

void GraphicsSystem::cleanupDepthStencil()
{
	deviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	depthStencil->Release();

	deviceContext->Flush();
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
