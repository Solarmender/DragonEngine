#include "Cube.h"
#include "../DragonEngine.h"
#include <stdexcept>

Cube::Cube(DragonEngine* parent) : Entity(parent)
{
	vertexShader = new VertexShader(L"cubeshader.hlsl", parent->getGraphics());
	pixelShader = new PixelShader(L"cubeshader.hlsl", parent->getGraphics());
	inputLayout = new InputLayout(vertexShader, parent->getGraphics());
	vertexBuffer = new VertexBuffer(parent->getGraphics());
	indexBuffer = new IndexBuffer(parent->getGraphics());
	constantBuffer = new ConstantBuffer(parent->getGraphics());
	topology = new Topology(parent->getGraphics());
}

void Cube::update()
{
}

void Cube::render()
{
	GraphicsSystem* gfx = engine->getGraphics();

	vertexBuffer->set();

	inputLayout->set();

	indexBuffer->set();

	topology->set();

	vertexShader->set();

	DirectX::XMMATRIX worldMatrix = getTranslationMatrix();
	DirectX::XMMATRIX viewMatrix = engine->getScene()->getCamera()->getViewMatrix();
	DirectX::XMMATRIX projectionMatrix = engine->getScene()->getCamera()->getProjectionMatrix();

	constantBuffer->update(worldMatrix, viewMatrix, projectionMatrix);

	pixelShader->set();

	gfx->getDeviceContext()->DrawIndexed(indexBuffer->getIndexCount(), 0, 0);
}
