#pragma once

typedef struct
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> tex;
	int width;
	int height;
} TextureRecord;

typedef std::map < std::string, TextureRecord > TextureMap;

class TextureManager : public Singleton<TextureManager>
{
	friend class Singleton < TextureManager > ;
public:
	TextureManager();
	~TextureManager();

	void SetTexture(const char *name);
	void Shutdown();
	void Startup();

private:
	typedef HRESULT(*load_proc)(ID3D11Device*, const wchar_t*, ID3D11Resource**, ID3D11ShaderResourceView**);
	TextureMap                                    m_textures;
	std::map < std::wstring, load_proc >          m_loaders;

	void LoadTexture(const char *name);
};

