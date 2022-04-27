#include "Sphere.h"
#include "../../DragonEngine.h"

Sphere::Sphere(DragonEngine* parent) : Entity(parent)
{
    sphereMesh = createSphere();

    vertexShader = new VertexShader(L"simple.hlsl", parent->getGraphics());
    pixelShader = new PixelShader(L"simple.hlsl", parent->getGraphics());
    inputLayout = new InputLayout(vertexShader, parent->getGraphics());
    vertexBuffer = new VertexBuffer(sphereMesh, parent->getGraphics());
    indexBuffer = new IndexBuffer(sphereMesh, parent->getGraphics());
    constantBuffer = new ConstantBuffer(parent->getGraphics());
    topology = new Topology(parent->getGraphics());
}

void Sphere::update()
{
}

void Sphere::render()
{
	GraphicsSystem* gfx = engine->getGraphics();

	vertexBuffer->set();

	inputLayout->set();

	indexBuffer->set();

	topology->set();

	vertexShader->set();

	DirectX::XMMATRIX worldMatrix = transform.getTranslationMatrix();
	DirectX::XMMATRIX viewMatrix = engine->getScene()->getCamera()->getViewMatrix();
	DirectX::XMMATRIX projectionMatrix = engine->getScene()->getCamera()->getProjectionMatrix();

	if(shouldOrbit)
	{
		orbitAngle += orbitSpeed * engine->getScene()->deltaTime;
		if (orbitAngle > 360.f)
		{
			orbitAngle -= 360.f;
		}

		DirectX::XMVECTOR rotaxis = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMMATRIX Rotation = DirectX::XMMatrixRotationAxis( rotaxis, orbitAngle);
		DirectX::XMMATRIX Translation = DirectX::XMMatrixTranslation( radius, 0.0f, 0.0f );

		worldMatrix = worldMatrix * Translation * Rotation;
	}

	constantBuffer->update(worldMatrix, viewMatrix, projectionMatrix);

	pixelShader->set();

	gfx->getDeviceContext()->DrawIndexed(indexBuffer->getIndexCount(), 0, 0);
}

void Sphere::orbit(float x, float y, float z, float r, float a)
{
	orbitSpeed = a;
	radius = r;
	shouldOrbit = true;
}
