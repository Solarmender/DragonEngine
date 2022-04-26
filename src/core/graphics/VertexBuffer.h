#ifndef DRAGONENGINE_SRC_CORE_GRAPHICS_VERTEXBUFFER_H
#define DRAGONENGINE_SRC_CORE_GRAPHICS_VERTEXBUFFER_H

#include "GraphicsSystem.h"
#include "d3d11.h"
#include "../entities/Mesh.h"

class VertexBuffer
{
public:
    VertexBuffer(Mesh* mesh, GraphicsSystem* gfx);

	void set();
private:
	UINT vertexStride;
	UINT vertexOffset;
	UINT vertexCount;

	ID3D11Buffer* vertexBuffer;

	GraphicsSystem* graphics;
};

#endif //DRAGONENGINE_SRC_CORE_GRAPHICS_VERTEXBUFFER_H
