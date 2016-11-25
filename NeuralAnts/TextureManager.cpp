#include "pch.h"

#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

#include "Config.h"
#include "Graphics.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::SetTexture(const char *name)
{
	auto search = m_textures.find(std::string(name));
	if (search == m_textures.end())
	{
		LoadTexture(name);
	}

	auto device = Graphics::Instance().GetDevice();

}

void TextureManager::Shutdown()
{
	for(auto it : m_textures)
	{
		it.second.tex.Reset();
	}

}

void TextureManager::Startup()
{
}

void TextureManager::LoadTexture(const char *name)
{
	using namespace DirectX;
	using namespace Microsoft::WRL;

	auto texture = ComPtr < ID3D11ShaderResourceView >();
	auto &paths = Config::Instance().GetResourcePaths();
	auto found_it = false;

	/* check if texture is DDS */
	auto name_str = std::string(name);
	auto is_dds = Utils::GetFileExtension(name_str) == std::string("dds");
	
	ComPtr<ID3D11Resource> resource;
	for(auto it : paths)
	{
		auto full_name = Utils::ToWide( it + name_str );
		auto result = S_OK;
		if(is_dds)
		{
			result = CreateDDSTextureFromFile(Graphics::Instance().GetDevice().Get(), full_name.c_str(), resource.GetAddressOf(), texture.ReleaseAndGetAddressOf());
		}
		else
		{
			result = CreateWICTextureFromFile(Graphics::Instance().GetDevice().Get(), full_name.c_str(), resource.GetAddressOf(), texture.ReleaseAndGetAddressOf());
		}

		if(SUCCEEDED(result))
		{
			found_it = true;
			break;
		}
	}
	
	if(!found_it)
	{
		throw std::exception();
	}

	/* Get the texture descriptor */
	ComPtr<ID3D11Texture2D> texture2d;
	DX::ThrowIfFailed(resource.As(&texture2d));
	CD3D11_TEXTURE2D_DESC desc;
	texture2d->GetDesc(&desc);
	

	/* create the record and add to our loaded list */
	TextureRecord record;
	record.tex    = texture;
	record.width  = desc.Width;
	record.height = desc.Height;

	m_textures.insert(std::make_pair(std::string(name), record));
}