#include "VertexShader.h"
#include <d3dcompiler.h>
#include <stdexcept>

VertexShader::VertexShader(const std::wstring& fileName, GraphicsSystem* gfx)
{
	vertexShader = nullptr;
	vertexShaderBlob = nullptr;
	graphics = gfx;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* error_blob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		(LPCWSTR)fileName.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"vs_main",
		"vs_5_0",
		flags,
		0,
		&vertexShaderBlob,
		&error_blob
		);

	if(FAILED(hr))
	{
		if(error_blob)
		{
			MessageBoxA(nullptr, (char*)error_blob->GetBufferPointer(), "Test", MB_OK);
			OutputDebugStringA((char*)error_blob->GetBufferPointer());
			error_blob->Release();
		}

		if(vertexShaderBlob)
		{
			vertexShaderBlob->Release();
		}

		throw std::runtime_error("Failed to compile vertex shader");
	}

	hr = graphics->getDevice()->CreateVertexShader(
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(),
		nullptr,
		&vertexShader
		);

	if(FAILED(hr))
	{
		throw std::runtime_error("Failed to create vertex shader");
	}
}

void VertexShader::set()
{
	graphics->getDeviceContext()->VSSetShader(vertexShader,nullptr,0u);
}

ID3DBlob* VertexShader::getBlob()
{
	return vertexShaderBlob;
}
