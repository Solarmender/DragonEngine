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
private:
    DragonEngine* engine;

    unsigned int clientWidth;
    unsigned int clientHeight;

    void initDevice();
    void cleanupDevice();

    void initBackbuffer();
    void cleanupBackbuffer();

    void setViewport();

    IDXGISwapChain* swapchain;
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    ID3D11RenderTargetView* backbuffer;
};

#endif //DRAGONENGINE_GRAPHICSSYSTEM_H
