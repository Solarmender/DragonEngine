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
private:
    void initDevice();
    void cleanupDevice();

    void initBackbuffer();
    void cleanupBackbuffer();

    void setViewport();

    IDXGISwapChain* swapchain;
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    ID3D11RenderTargetView* backbuffer;

    DragonEngine* engine;
};

#endif //DRAGONENGINE_GRAPHICSSYSTEM_H
