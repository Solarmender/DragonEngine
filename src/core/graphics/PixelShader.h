#ifndef DRAGONENGINE_SRC_CORE_GRAPHICS_PIXELSHADER_H
#define DRAGONENGINE_SRC_CORE_GRAPHICS_PIXELSHADER_H

#include "GraphicsSystem.h"
#include <d3d11.h>
#include <string>

class PixelShader
{
public:
	PixelShader(const std::wstring& fileName, GraphicsSystem* gfx);

	void set();

	ID3DBlob* getBlob();
private:
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderBlob;

	GraphicsSystem* graphics;
};

#endif //DRAGONENGINE_SRC_CORE_GRAPHICS_PIXELSHADER_H
