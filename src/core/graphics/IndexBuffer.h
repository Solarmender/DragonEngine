#ifndef DRAGONENGINE_SRC_CORE_GRAPHICS_INDEXBUFFER_H
#define DRAGONENGINE_SRC_CORE_GRAPHICS_INDEXBUFFER_H

#include "GraphicsSystem.h"
#include "d3d11.h"

class IndexBuffer
{
public:
	explicit IndexBuffer(GraphicsSystem* gfx);

	void set();

	UINT getIndexCount() const;
private:
	UINT indexCount;

	ID3D11Buffer* indexBuffer;

	GraphicsSystem* graphics;
};

#endif //DRAGONENGINE_SRC_CORE_GRAPHICS_INDEXBUFFER_H
