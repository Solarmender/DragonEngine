#include "VertexBuffer.h"
#include <stdexcept>

VertexBuffer::VertexBuffer(GraphicsSystem* gfx)
{
	graphics = gfx;

	// Pass this in from constructor
	float vertex_data_array[] = {
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
	};

	vertexStride = 3 * sizeof(float);
	vertexOffset = 0;

	D3D11_BUFFER_DESC vertexBuffDesc = { };
	vertexBuffDesc.ByteWidth = sizeof(vertex_data_array);
	vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sr_data = { };
	sr_data.pSysMem = vertex_data_array;

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
