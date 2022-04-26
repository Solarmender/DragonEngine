#ifndef DRAGONENGINE_GRAPHICSSYSTEM_H
#define DRAGONENGINE_GRAPHICSSYSTEM_H

#include <d3d11.h>

class DragonEngine;

class GraphicsSystem
{
public:
    explicit GraphicsSystem(DragonEngine* parentEngine);
    ~GraphicsSystem();

    void clearScreen();
    void presentFrame();

    void onResize();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
private:
    void initDevice();
    void cleanupDevice();

    void initRenderTarget();
    void cleanupRenderTarget();

	void initDepthStencil();
	void cleanupDepthStencil();

    void setViewport();

    IDXGISwapChain* swapchain;
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    ID3D11RenderTargetView* renderTarget;
	ID3D11DepthStencilView* depthStencil;

    DragonEngine* engine;
};

#endif //DRAGONENGINE_GRAPHICSSYSTEM_H
