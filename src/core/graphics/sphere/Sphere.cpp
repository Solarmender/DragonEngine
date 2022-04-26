#include "Sphere.h"
#include "../../DragonEngine.h"

Sphere::Sphere(DragonEngine* parent) : Entity(parent)
{
    sphereMesh = createCube();

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
    GraphicsSystem* gfx = engine->getGraphics();

    vertexBuffer->set();

    inputLayout->set();

    indexBuffer->set();

    topology->set();

    vertexShader->set();

    DirectX::XMMATRIX worldMatrix = transform.getTranslationMatrix();
    DirectX::XMMATRIX viewMatrix = engine->getScene()->getCamera()->getViewMatrix();
    DirectX::XMMATRIX projectionMatrix = engine->getScene()->getCamera()->getProjectionMatrix();

    constantBuffer->update(worldMatrix, viewMatrix, projectionMatrix);

    pixelShader->set();

    gfx->getDeviceContext()->DrawIndexed(indexBuffer->getIndexCount(), 0, 0);
}

void Sphere::render()
{

}
