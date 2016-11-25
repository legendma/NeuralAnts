#pragma once

class Graphics : public Singleton<Graphics>
{
	friend class Singleton < Graphics > ;
	Graphics();

public:
	~Graphics();

	void Clear();
	void PopRaster();
	void Present();
	void PushRaster();
	void Shutdown();
	void Startup();
	void Reset();
	void Resize(int width, int height);

	/* raster operations */
	CD3D11_RASTERIZER_DESC & GetRaster() { return(m_raster_desc); }


	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice();
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> * GetContext();

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

	/* raster members */
	Microsoft::WRL::ComPtr<ID3D10RasterizerState>   m_raster;               //DX::ThrowIfFailed(m_d3dDevice->CreateRasterizerState( &rastDesc,
                                                                            //                  m_raster.ReleaseAndGetAddressOf() ));
	CD3D11_RASTERIZER_DESC                          m_raster_desc;
	std::stack<CD3D11_RASTERIZER_DESC>              m_raster_stack;
	
	void CreateDevice();
	void CreateResources();
};

