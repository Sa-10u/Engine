#include "D3D.h"
#include "MACRO.h"
#include<cassert>

namespace D3D
{
    ID3D11Device* pDevice_;
	ID3D11DeviceContext* pContext_;		//デバイスコンテキスト
	IDXGISwapChain* pSwapChain_;		//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView_;
    ID3D11Texture2D* pDepth_;
    ID3D11DepthStencilView* pDepthView_;

    struct SHADER_BUNDLE
    {
        ID3D11VertexShader* vs = nullptr;
        ID3D11PixelShader* ps = nullptr;
        ID3D11InputLayout* lo = nullptr;
        ID3D11RasterizerState* rs = nullptr;
    }shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_AMMOUNT)];
}



HRESULT D3D::Initialize(int winW ,int winH,HWND hwnd)
{
    HRESULT hr = E_FAIL;
    

    DXGI_SWAP_CHAIN_DESC scDesc;

    //とりあえず全部0
    ZeroMemory(&scDesc, sizeof(scDesc));

    //描画先のフォーマット
    scDesc.BufferDesc.Width = winW;		//画面幅
    scDesc.BufferDesc.Height = winH;	//画面高さ
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 何色使えるか

    //FPS（1/60秒に1回）
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;

    //その他
    scDesc.Windowed = TRUE;			//ウィンドウモードかフルスクリーンか
    scDesc.OutputWindow = hwnd;		//ウィンドウハンドル
    scDesc.BufferCount = 1;			//バックバッファの枚数
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//バックバッファの使い道＝画面に描画するために
    scDesc.SampleDesc.Count = 1;		//MSAA（アンチエイリアス）の設定
    scDesc.SampleDesc.Quality = 0;		//　〃

    //------
    D3D_FEATURE_LEVEL level;
    D3D11CreateDeviceAndSwapChain(
        nullptr,				// どのビデオアダプタを使用するか？既定ならばnullptrで
        D3D_DRIVER_TYPE_HARDWARE,		// ドライバのタイプを渡す。ふつうはHARDWARE
        nullptr,				// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しないかぎりnullptr
        0,					// 何らかのフラグを指定する。（デバッグ時はD3D11_CREATE_DEVICE_DEBUG？）
        nullptr,				// デバイス、コンテキストのレベルを設定。nullptrにしとけばOK
        0,					// 上の引数でレベルを何個指定したか
        D3D11_SDK_VERSION,			// SDKのバージョン。必ずこの値
        &scDesc,				// 上でいろいろ設定した構造体
        &pSwapChain_,				// 無事完成したSwapChainのアドレスが返ってくる
        &pDevice_,				// 無事完成したDeviceアドレスが返ってくる
        &level,					// 無事完成したDevice、Contextのレベルが返ってくる
        &pContext_);

    //-----
    ID3D11Texture2D* pBackBuffer;
    hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (hr != S_OK)
    {
        MessageBox(nullptr, "SwapChain ungot Buffer", "ERROR", MB_OK);
        return hr;
    }

    //レンダーターゲットビューを作成
    hr = pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_);
    if (hr != S_OK)
    {
        MessageBox(nullptr, "Cannot Create RTV", "ERROR", MB_OK);
        return hr;
    }

    //一時的にバックバッファを取得しただけなので解放
    SAFE_RELEASE(pBackBuffer);

    //-----
    D3D11_VIEWPORT vp;
    vp.Width = (float)winW;	//幅
    vp.Height = (float)winH;//高さ
    vp.MinDepth = 0.0f;	//手前
    vp.MaxDepth = 1.0f;	//奥
    vp.TopLeftX = 0;	//左
    vp.TopLeftY = 0;	//上

    //深度ステンシルビューの作成
    D3D11_TEXTURE2D_DESC descDepth;
    descDepth.Width = winW;
    descDepth.Height = winH;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D32_FLOAT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    pDevice_->CreateTexture2D(&descDepth, NULL, &pDepth_);
    pDevice_->CreateDepthStencilView(pDepth_, NULL, &pDepthView_);


    //データを画面に描画するための一通りの設定（パイプライン）
    pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // データの入力種類を指定
    pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthView_);            // 描画先を設定
    pContext_->RSSetViewports(1, &vp);

    Shader_Initialize2D();
    Shader_Initialize3D();
    Shader_InitializePoint3D();

    return S_OK;
}

void D3D::BeginDraw()
{
    

    float clearColor[4] = { 0.4f, 0.6f, 0.5f, 0.2f };//R,G,B,A

    //画面をクリア
    pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);

    pContext_->ClearDepthStencilView(pDepthView_, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3D::EndDraw()
{
    if (S_OK != pSwapChain_->Present(0, 0))
    {
        MessageBox(nullptr, "SwapChainner is not work", "ERROR", MB_OK);
        PostQuitMessage(0);
    }
}

void D3D::Release()
{
    SAFE_RELEASE(pRenderTargetView_);
    SAFE_RELEASE(pSwapChain_);
    SAFE_RELEASE(pContext_);
    SAFE_RELEASE(pDevice_);

    for (int i = 0; i < static_cast<int>(SHADER_TYPE::SHADER_AMMOUNT); i++) {

        SAFE_RELEASE(shader_bundle[i].vs);
        SAFE_RELEASE(shader_bundle[i].ps);
        SAFE_RELEASE(shader_bundle[i].lo);
        SAFE_RELEASE(shader_bundle[i].rs);
    }
}

void D3D::Shader_Initialize2D()
{
    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    assert(pCompileVS != nullptr);
    pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_2D)].vs);

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
        {"TEXCOORD" ,0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::XMVECTOR) , D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    pDevice_->CreateInputLayout(layout, (sizeof(layout) / sizeof(layout[0])), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_2D)].lo);

    SAFE_RELEASE(pCompileVS);

    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    assert(pCompilePS != nullptr);
    pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_2D)].ps);
    SAFE_RELEASE(pCompilePS);

    {
        D3D11_RASTERIZER_DESC rdc = {};
        rdc.CullMode = D3D11_CULL_NONE;     //CULL_MODE
        rdc.FillMode = D3D11_FILL_SOLID;
        rdc.FrontCounterClockwise = FALSE;
        pDevice_->CreateRasterizerState(&rdc, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_2D)].rs);
    }
}

void D3D::Shader_Initialize3D()
{
    HRESULT hr = S_OK;

   
    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    assert(pCompileVS != nullptr);
    pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_3D)].vs);

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
        {"TEXCOORD" ,0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::XMVECTOR) , D3D11_INPUT_PER_VERTEX_DATA, 0},
          { "NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(DirectX::XMVECTOR) * 2 ,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
 
     pDevice_->CreateInputLayout(layout, (sizeof(layout) / sizeof(layout[0])), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_3D)].lo);

    SAFE_RELEASE(pCompileVS);


    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    assert(pCompilePS != nullptr);
    pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_3D)].ps);
    SAFE_RELEASE(pCompilePS);

    {
        D3D11_RASTERIZER_DESC rdc = {};
        rdc.CullMode = D3D11_CULL_BACK;     //CULL_MODE
        rdc.FillMode = D3D11_FILL_SOLID;
        rdc.FrontCounterClockwise = FALSE;
        pDevice_->CreateRasterizerState(&rdc, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_3D)].rs);
    }
 }

void D3D::Shader_InitializePoint3D()
{
    HRESULT hr = S_OK;


    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"Point3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    assert(pCompileVS != nullptr);
    pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_POINT3D)].vs);

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
        {"TEXCOORD" ,0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::XMVECTOR) , D3D11_INPUT_PER_VERTEX_DATA, 0},
          { "NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(DirectX::XMVECTOR) * 2 ,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    pDevice_->CreateInputLayout(layout, (sizeof(layout) / sizeof(layout[0])), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_POINT3D)].lo);

    SAFE_RELEASE(pCompileVS);


    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"Point3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    assert(pCompilePS != nullptr);
    pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_POINT3D)].ps);
    SAFE_RELEASE(pCompilePS);

    {
        D3D11_RASTERIZER_DESC rdc = {};
        rdc.CullMode = D3D11_CULL_BACK;     //CULL_MODE
        rdc.FillMode = D3D11_FILL_SOLID;
        rdc.FrontCounterClockwise = FALSE;
        pDevice_->CreateRasterizerState(&rdc, &shader_bundle[static_cast<int>(SHADER_TYPE::SHADER_POINT3D)].rs);
    }
}

void D3D::SetShader(SHADER_TYPE type)
{
    pContext_->VSSetShader(shader_bundle[static_cast<int>(type)].vs,NULL, 0);	//頂点シェーダー
    pContext_->PSSetShader(shader_bundle[static_cast<int>(type)].ps, NULL, 0);	//ピクセルシェーダー
    pContext_->IASetInputLayout(shader_bundle[static_cast<int>(type)].lo);	//頂点インプットレイアウト
    pContext_->RSSetState(shader_bundle[static_cast<int>(type)].rs);		//ラスタライザー
}
