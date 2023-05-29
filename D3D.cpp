#include<d3d11.h>
#include<d3dcompiler.h>
#include "D3D.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace D3D
{
	ID3D11Device* pDevice;		//�f�o�C�X
	ID3D11DeviceContext* pContext;		//�f�o�C�X�R���e�L�X�g
	IDXGISwapChain* pSwapChain;		//�X���b�v�`�F�C��
	ID3D11RenderTargetView* pRenderTargetView;

    ID3D11VertexShader* pVertexShader = nullptr;	//���_�V�F�[�_�[
    ID3D11PixelShader* pPixelShader = nullptr;		//�s�N�Z���V�F�[�_�[
    ID3D11InputLayout* pVertexLayout = nullptr;

    ID3D11RasterizerState* pRasterizerState = nullptr;
}

void D3D::Initialize(int winW ,int winH,HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC scDesc;

    //�Ƃ肠�����S��0
    ZeroMemory(&scDesc, sizeof(scDesc));

    //�`���̃t�H�[�}�b�g
    scDesc.BufferDesc.Width = winW;		//��ʕ�
    scDesc.BufferDesc.Height = winH;	//��ʍ���
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

    //FPS�i1/60�b��1��j
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;

    //���̑�
    scDesc.Windowed = TRUE;			//�E�B���h�E���[�h���t���X�N���[����
    scDesc.OutputWindow = hwnd;		//�E�B���h�E�n���h��
    scDesc.BufferCount = 1;			//�o�b�N�o�b�t�@�̖���
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�o�b�N�o�b�t�@�̎g��������ʂɕ`�悷�邽�߂�
    scDesc.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
    scDesc.SampleDesc.Quality = 0;		//�@�V

    //------
    D3D_FEATURE_LEVEL level;
    D3D11CreateDeviceAndSwapChain(
        nullptr,				// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr��
        D3D_DRIVER_TYPE_HARDWARE,		// �h���C�o�̃^�C�v��n���B�ӂ���HARDWARE
        nullptr,				// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵�Ȃ�������nullptr
        0,					// ���炩�̃t���O���w�肷��B�i�f�o�b�O����D3D11_CREATE_DEVICE_DEBUG�H�j
        nullptr,				// �f�o�C�X�A�R���e�L�X�g�̃��x����ݒ�Bnullptr�ɂ��Ƃ���OK
        0,					// ��̈����Ń��x�������w�肵����
        D3D11_SDK_VERSION,			// SDK�̃o�[�W�����B�K�����̒l
        &scDesc,				// ��ł��낢��ݒ肵���\����
        &pSwapChain,				// ������������SwapChain�̃A�h���X���Ԃ��Ă���
        &pDevice,				// ������������Device�A�h���X���Ԃ��Ă���
        &level,					// ������������Device�AContext�̃��x�����Ԃ��Ă���
        &pContext);

    //-----
    ID3D11Texture2D* pBackBuffer;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    //�����_�[�^�[�Q�b�g�r���[���쐬
    pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

    //�ꎞ�I�Ƀo�b�N�o�b�t�@���擾���������Ȃ̂ŉ��
    pBackBuffer->Release();

    //-----
    D3D11_VIEWPORT vp;
    vp.Width = (float)winW;	//��
    vp.Height = (float)winH;//����
    vp.MinDepth = 0.0f;	//��O
    vp.MaxDepth = 1.0f;	//��
    vp.TopLeftX = 0;	//��
    vp.TopLeftY = 0;	//��

    //�f�[�^����ʂɕ`�悷�邽�߂̈�ʂ�̐ݒ�i�p�C�v���C���j
    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // �f�[�^�̓��͎�ނ��w��
    pContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);            // �`����ݒ�
    pContext->RSSetViewports(1, &vp);

    Shader_Initialize();
}

void D3D::BeginDraw()
{
    float clearColor[4] = { 0.4f, 0.6f, 0.3f, 0.2f };//R,G,B,A

    //��ʂ��N���A
    pContext->ClearRenderTargetView(pRenderTargetView, clearColor);


    //�`�揈��


    //�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
    pSwapChain->Present(0, 0);
}

void D3D::EndDraw()
{
}

void D3D::Release()
{
	pRenderTargetView->Release();
	pSwapChain->Release();
	pContext->Release();
	pDevice->Release();
    pVertexShader->Release();
    pVertexLayout->Release();
    pPixelShader->Release();
    pRasterizerState->Release();
}

void D3D::Shader_Initialize()
{
    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);
   
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�ʒu
    };
    pDevice->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);

    pCompileVS->Release();

    //-----

    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
    pCompilePS->Release();

    D3D11_RASTERIZER_DESC rdc = {};
    rdc.CullMode = D3D11_CULL_BACK;
    rdc.FillMode = D3D11_FILL_SOLID;
    rdc.FrontCounterClockwise = FALSE;
    pDevice->CreateRasterizerState(&rdc, &pRasterizerState);
}
