#pragma once

using namespace DirectX;

typedef struct
{
	
	bool                   enable;
	SimpleMath::Vector4    direction;
	SimpleMath::Vector4    diffuse;
	SimpleMath::Vector4    specular;
} Light;

class Graphics : public Singleton<Graphics>, public IEffectMatrices, public IEffectLights, public IEffectFog
{
	friend class Singleton < Graphics > ;
public:
	Graphics();
	~Graphics();

	void Clear();
	void PopRaster();
	void Present();
	void PushRaster();
	void Shutdown();
	void Startup();
	void Reset();
	void Resize(int width, int height);

	static void CALLBACK UpdateEffects(IEffect *effect);
	void __UpdateEffects(IEffect *effect);

	/* raster operations */
	CD3D11_RASTERIZER_DESC & GetRaster() { return(m_raster_desc); }

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice();
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext();
	IEffectFactory & GetEffectsFactory();
	CommonStates & GetRenderStates();

	/* camera settings */
	void XM_CALLCONV SetWorld(FXMMATRIX value) override;
	void XM_CALLCONV SetView(FXMMATRIX value) override;
	void XM_CALLCONV SetProjection(FXMMATRIX value) override;
	void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

	/* light settings */
	void __cdecl SetLightingEnabled(bool value) override;
	void __cdecl SetPerPixelLighting(bool value) override;
	void XM_CALLCONV SetAmbientLightColor(FXMVECTOR value) override;

	void __cdecl SetLightEnabled(int whichLight, bool value) override;
	void XM_CALLCONV SetLightDirection(int whichLight, FXMVECTOR value) override;
	void XM_CALLCONV SetLightDiffuseColor(int whichLight, FXMVECTOR value) override;
	void XM_CALLCONV SetLightSpecularColor(int whichLight, FXMVECTOR value) override;

	/* fog settings */
	void __cdecl SetFogEnabled(bool value) override;
	void __cdecl SetFogStart(float value) override;
	void __cdecl SetFogEnd(float value) override;
	void XM_CALLCONV SetFogColor(FXMVECTOR value) override;


private:
	D3D_FEATURE_LEVEL                               m_featureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;
	Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;

	int                                             m_outputWidth;
	int                                             m_outputHeight;

	/* camera properties */
	SimpleMath::Matrix                              m_mat_world;
	SimpleMath::Matrix                              m_mat_view;
	SimpleMath::Matrix                              m_mat_projection;

	/* lighting properties */
	bool                                            m_enable_lighting;
	bool                                            m_enable_pixel_lighting;
	SimpleMath::Vector4                             m_light_color_ambient;
	std::vector<Light>                              m_direction_lights;

	/* fog properties */
	bool                                            m_enable_fog;
	SimpleMath::Vector4                             m_fog_color;
	std::pair<float, float>                         m_fog_planes;

	/* raster members */
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>   m_raster;               
                                                                            
	CD3D11_RASTERIZER_DESC                          m_raster_desc;
	std::stack<CD3D11_RASTERIZER_DESC>              m_raster_stack;
	std::unique_ptr<EffectFactory>                  m_effects_factory;
	std::unique_ptr<CommonStates>                   m_render_states;
	
	void CreateDevice();
	void CreateResources();
	void UpdateRaster();

	/* not implemented */
	void __cdecl EnableDefaultLighting() override {};
};

