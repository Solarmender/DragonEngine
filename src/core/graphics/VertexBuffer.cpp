#include "VertexBuffer.h"
#include <stdexcept>

VertexBuffer::VertexBuffer(Mesh* mesh, GraphicsSystem* gfx)
{
	graphics = gfx;

	vertexStride = 3 * sizeof(float);
	vertexOffset = 0;

	D3D11_BUFFER_DESC vertexBuffDesc = { };
	vertexBuffDesc.ByteWidth = uint64_t(mesh->vertices.size()) * uint64_t(vertexStride);
	vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sr_data = { };
	sr_data.pSysMem = mesh->vertices.data();

	HRESULT hr = graphics->getDevice()->CreateBuffer(
		&vertexBuffDesc,
		&sr_data,
		&vertexBuffer
	);

	if(FAILED(hr))
	{
		throw std::runtime_error("Failed to create vertex buffer");
	}
}

void VertexBuffer::set()
{
	graphics->getDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &vertexOffset);
}
