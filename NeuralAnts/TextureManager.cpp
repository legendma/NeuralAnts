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
	auto dds_loader = [](ID3D11Device *v1, const wchar_t *v2, ID3D11Resource**v3, ID3D11ShaderResourceView**v4) -> HRESULT { return(CreateDDSTextureFromFile(v1, v2, v3, v4)); };
	auto wic_loader = [](ID3D11Device *v1, const wchar_t *v2, ID3D11Resource**v3, ID3D11ShaderResourceView**v4) -> HRESULT { return(CreateWICTextureFromFile(v1, v2, v3, v4)); };

	m_loaders.insert(std::make_pair(std::wstring(L".dds"), dds_loader));
	m_loaders.insert(std::make_pair(std::wstring(L".jpg"), wic_loader));
	m_loaders.insert(std::make_pair(std::wstring(L".bmp"), wic_loader));
	m_loaders.insert(std::make_pair(std::wstring(L".png"), wic_loader));
	m_loaders.insert(std::make_pair(std::wstring(L".gif"), wic_loader));
	m_loaders.insert(std::make_pair(std::wstring(L".tif"), wic_loader));
	m_loaders.insert(std::make_pair(std::wstring(L".tff"), wic_loader));
}

void TextureManager::LoadTexture(const char *name)
{
	using namespace DirectX;
	using namespace Microsoft::WRL;

	auto texture   = ComPtr < ID3D11ShaderResourceView >();
	auto &filename = Config::Instance().GetFileResourcePath(name);
	
	ComPtr<ID3D11Resource> resource;
	m_loaders[Utils::GetFileExtension(Utils::ToWide(name))](Graphics::Instance().GetDevice().Get(), filename.c_str(), resource.GetAddressOf(), texture.ReleaseAndGetAddressOf());

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