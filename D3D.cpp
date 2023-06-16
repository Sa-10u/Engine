#include "D3D.h"
#include "MACRO.h"
#include<cassert>

namespace D3D
{
    ID3D11Device* pDevice_;
	ID3D11DeviceContext* pContext_;		//デバイスコンテキスト
	IDXGISwapChain* pSwapChain_;		//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView_;

    ID3D11VertexShader* pVertexShader = nullptr;	//頂点シェーダー
    ID3D11PixelShader* pPixelShader = nullptr;		//ピクセルシェーダー
    ID3D11InputLayout* pVertexLayout = nullptr;

    ID3D11RasterizerState* pRasterizerState = nullptr;
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

    //データを画面に描画するための一通りの設定（パイプライン）
    pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // データの入力種類を指定
    pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);            // 描画先を設定
    pContext_->RSSetViewports(1, &vp);

    Shader_Initialize();

    return S_OK;
}

void D3D::BeginDraw()
{
    

    float clearColor[4] = { 0.4f, 0.6f, 0.5f, 0.2f };//R,G,B,A

    //画面をクリア
    pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);
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
    SAFE_RELEASE(pVertexShader);
    SAFE_RELEASE(pVertexLayout);
    SAFE_RELEASE(pPixelShader);
    SAFE_RELEASE(pRasterizerState);
}

void D3D::Shader_Initialize()
{
    HRESULT hr = S_OK;

    //--------------------------------3D
    //ID3DBlob* pCompilePS = nullptr;
    //D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    //assert(pCompilePS != nullptr);
    //pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
    //SAFE_RELEASE(pCompilePS);

    //{
    //    D3D11_RASTERIZER_DESC rdc = {};
    //    rdc.CullMode = D3D11_CULL_BACK;     //CULL_MODE
    //    rdc.FillMode = D3D11_FILL_SOLID;
    //    rdc.FrontCounterClockwise = FALSE;
    //    pDevice_->CreateRasterizerState(&rdc, &pRasterizerState);
    //}

    //ID3DBlob* pCompilePS = nullptr;
    //D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    //assert(pCompilePS != nullptr);
    //pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
    //SAFE_RELEASE(pCompilePS);

    //{
    //    D3D11_RASTERIZER_DESC rdc = {};
    //    rdc.CullMode = D3D11_CULL_BACK;     //CULL_MODE
    //    rdc.FillMode = D3D11_FILL_SOLID;
    //    rdc.FrontCounterClockwise = FALSE;
    //    pDevice_->CreateRasterizerState(&rdc, &pRasterizerState);
    //}

    //----------------------------------------2D

    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    assert(pCompileVS != nullptr);
    pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
        {"TEXCOORD" ,0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::XMVECTOR) , D3D11_INPUT_PER_VERTEX_DATA, 0},
       };
    pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);

    SAFE_RELEASE(pCompileVS);

    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    assert(pCompilePS != nullptr);
    pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
    SAFE_RELEASE(pCompilePS);

    {
        D3D11_RASTERIZER_DESC rdc = {};
        rdc.CullMode = D3D11_CULL_BACK;     //CULL_MODE
        rdc.FillMode = D3D11_FILL_SOLID;
        rdc.FrontCounterClockwise = FALSE;
        pDevice_->CreateRasterizerState(&rdc, &pRasterizerState);
    }



    pContext_->VSSetShader(pVertexShader, NULL, 0);	//頂点シェーダー
    pContext_->PSSetShader(pPixelShader, NULL, 0);	//ピクセルシェーダー
    pContext_->IASetInputLayout(pVertexLayout);	//頂点インプットレイアウト
    pContext_->RSSetState(pRasterizerState);		//ラスタライザー
}
