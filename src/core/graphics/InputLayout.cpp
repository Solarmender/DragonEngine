#include "InputLayout.h"
#include <stdexcept>

InputLayout::InputLayout(VertexShader* shader, GraphicsSystem* gfx)
{
	graphics = gfx;

	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HRESULT hr = graphics->getDevice()->CreateInputLayout(
		inputElementDesc,
		ARRAYSIZE(inputElementDesc),
		shader->getBlob()->GetBufferPointer(),
		shader->getBlob()->GetBufferSize(),
		&inputLayout
	);

	if(FAILED(hr))
	{
		throw std::runtime_error("Failed to create input layout");
	}
}

void InputLayout::set()
{
	graphics->getDeviceContext()->IASetInputLayout(inputLayout);
}
