#include "PixelShader.h"
#include <d3dcompiler.h>
#include <stdexcept>

PixelShader::PixelShader(const std::wstring& fileName, GraphicsSystem* gfx)
{
	pixelShader = nullptr;
	pixelShaderBlob = nullptr;
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
		"ps_main",
		"ps_5_0",
		flags,
		0,
		&pixelShaderBlob,
		&error_blob
	);

	if(FAILED(hr))
	{
		if(error_blob)
		{
			OutputDebugStringA((char*)error_blob->GetBufferPointer());
			error_blob->Release();
		}

		if(pixelShaderBlob)
		{
			pixelShaderBlob->Release();
		}

		throw std::runtime_error("Failed to compile pixel shader");
	}

	hr = graphics->getDevice()->CreatePixelShader(
		pixelShaderBlob->GetBufferPointer(),
		pixelShaderBlob->GetBufferSize(),
		nullptr,
		&pixelShader
	);

	if(FAILED(hr))
	{
		throw std::runtime_error("Failed to create pixel shader");
	}
}

void PixelShader::set()
{
	graphics->getDeviceContext()->PSSetShader(pixelShader,nullptr,0u);
}

ID3DBlob* PixelShader::getBlob()
{
	return pixelShaderBlob;
}
