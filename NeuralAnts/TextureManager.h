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
	TextureMap             m_textures;

	void LoadTexture(const char *name);
};

