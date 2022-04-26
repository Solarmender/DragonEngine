#ifndef DRAGONENGINE_SRC_CORE_GRAPHICS_CUBE_H
#define DRAGONENGINE_SRC_CORE_GRAPHICS_CUBE_H

#include "../entities/Entity.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Topology.h"

class Cube : public Entity
{
public:
	explicit Cube(DragonEngine* parent);

	void update() override;
	void render() override;
private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	InputLayout* inputLayout;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	Topology* topology;
};

#endif //DRAGONENGINE_SRC_CORE_GRAPHICS_CUBE_H
