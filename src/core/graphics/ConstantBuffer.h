#ifndef DRAGONENGINE_SRC_CORE_GRAPHICS_CONSTANTBUFFER_H
#define DRAGONENGINE_SRC_CORE_GRAPHICS_CONSTANTBUFFER_H

#include "GraphicsSystem.h"
#include <d3d11.h>
#include <DirectXMath.h>

struct Constants
{
	DirectX::XMMATRIX modelMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
};

class ConstantBuffer
{
public:
	explicit ConstantBuffer(GraphicsSystem* gfx);

	void update(DirectX::XMMATRIX model, DirectX::XMMATRIX view, DirectX::XMMATRIX projection);
private:
	ID3D11Buffer* constantBuffer;

	GraphicsSystem* graphics;
};

#endif //DRAGONENGINE_SRC_CORE_GRAPHICS_CONSTANTBUFFER_H
