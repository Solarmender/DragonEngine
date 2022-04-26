#include "ConstantBuffer.h"
#include <stdexcept>

ConstantBuffer::ConstantBuffer(GraphicsSystem *gfx)
{
	graphics = gfx;

	D3D11_BUFFER_DESC constantBufferDesc = { };
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(Constants);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = graphics->getDevice()->CreateBuffer(
		&constantBufferDesc,
		nullptr,
		&constantBuffer
	);

	if(FAILED(hr))
	{
		throw std::runtime_error("Failed to create index buffer");
	}
}

void ConstantBuffer::update(DirectX::XMMATRIX model, DirectX::XMMATRIX view, DirectX::XMMATRIX projection)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	graphics->getDeviceContext()->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	Constants* constants = (Constants*)(mappedSubresource.pData);

	constants->modelMatrix = model;
	constants->viewMatrix = view;
	constants->projectionMatrix = projection;

	graphics->getDeviceContext()->Unmap(constantBuffer, 0);

	graphics->getDeviceContext()->VSSetConstantBuffers(0, 1, &constantBuffer);
}
