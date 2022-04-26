#include "IndexBuffer.h"
#include <stdexcept>

IndexBuffer::IndexBuffer(GraphicsSystem* gfx)
{
	graphics = gfx;

	WORD indices[] =
		{
			3,1,0,
			2,1,3,

			0,5,4,
			1,5,0,

			3,4,7,
			0,4,3,

			1,6,5,
			2,6,1,

			2,7,6,
			3,7,2,

			6,4,5,
			7,4,6,
		};

	indexCount = 36;

	D3D11_BUFFER_DESC indexBuffDesc = { };
	indexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBuffDesc.ByteWidth = sizeof(indices);
	indexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBuffDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData = { };
	InitData.pSysMem = indices;

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
