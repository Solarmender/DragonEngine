#ifndef DRAGONENGINE_SRC_CORE_GRAPHICS_VERTEXSHADER_H
#define DRAGONENGINE_SRC_CORE_GRAPHICS_VERTEXSHADER_H

#include "GraphicsSystem.h"
#include <d3d11.h>
#include <string>

class VertexShader
{
public:
	VertexShader(const std::wstring& fileName, GraphicsSystem* gfx);

	void set();

	ID3DBlob* getBlob();
private:
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderBlob;

	GraphicsSystem* graphics;
};

#endif //DRAGONENGINE_SRC_CORE_GRAPHICS_VERTEXSHADER_H
