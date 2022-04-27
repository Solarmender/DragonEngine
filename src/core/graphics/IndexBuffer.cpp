#include "IndexBuffer.h"
#include <stdexcept>

IndexBuffer::IndexBuffer(Mesh* mesh, GraphicsSystem* gfx)
{
	graphics = gfx;

	indexCount = mesh->indices.size();

	D3D11_BUFFER_DESC indexBuffDesc{ };
	indexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBuffDesc.ByteWidth = uint64_t(mesh->indices.size()) * uint64_t(sizeof(unsigned short));
	indexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBuffDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData{ };
	InitData.pSysMem = mesh->indices.data();

	HRESULT hr = graphics->getDevice()->CreateBuffer(
		&indexBuffDesc,
		&InitData,
		&indexBuffer
	);

	if(FAILED(hr))
	{
		throw std::runtime_error("Failed to create index buffer");
	}
}

void IndexBuffer::set()
{
	graphics->getDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
}

UINT IndexBuffer::getIndexCount() const
{
	return indexCount;
}
