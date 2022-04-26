#ifndef DRAGONENGINE_SRC_CORE_GRAPHICS_INPUTLAYOUT_H
#define DRAGONENGINE_SRC_CORE_GRAPHICS_INPUTLAYOUT_H

#include "VertexShader.h"
#include "GraphicsSystem.h"
#include "d3d11.h"

class InputLayout
{
public:
	InputLayout(VertexShader* shader, GraphicsSystem* gfx);

	void set();
private:
	ID3D11InputLayout* inputLayout;
	GraphicsSystem* graphics;
};

#endif //DRAGONENGINE_SRC_CORE_GRAPHICS_INPUTLAYOUT_H
