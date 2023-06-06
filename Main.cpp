#include <Windows.h>
#include "D3D.h"
#include "M_Quad.h"
#include "MACRO.h"
#include "CAM.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace WIN
{
    const char _BAR[] = "What is this?";
    const char _NAME[] = "SampleGame";

    const int _HEIGHT = 600 ;
    const int _WIDTH = 800;
}



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{


    RECT winRect = { 0, 0, WIN::_WIDTH, WIN::_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     
    int winH = winRect.bottom - winRect.top;

  //create window class
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
    wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
    wc.lpszClassName = WIN::_NAME;            //�E�B���h�E�N���X��
    wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
    wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
    wc.hIcon = LoadIcon(NULL, IDI_QUESTION); //�A�C�R��
    wc.hIconSm = LoadIcon(NULL, IDI_QUESTION);   //�������A�C�R��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
    wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); //�w�i�i���j

    RegisterClassEx(&wc);

  //create window
    HWND hWnd = CreateWindow(
        WIN::_NAME,         //�E�B���h�E�N���X��
        WIN::_BAR,     //�^�C�g���o�[�ɕ\��������e
        WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
        CW_USEDEFAULT,       //�\���ʒu���i���܂����j
        CW_USEDEFAULT,       //�\���ʒu��i���܂����j
        winW,                 //�E�B���h�E��
        winH,                 //�E�B���h�E����
        NULL,                //�e�E�C���h�E�i�Ȃ��j
        NULL,                //���j���[�i�Ȃ��j
        hInstance,           //�C���X�^���X
        NULL                 //�p�����[�^�i�Ȃ��j
    );

  //output window
    ShowWindow(hWnd, nCmdShow);

    //-----------
    
    
    HRESULT* hr = new HRESULT;
    *hr = E_FAIL;
    CAM::Initialize();
    *hr = D3D::Initialize(WIN::_WIDTH, WIN::_HEIGHT, hWnd);

    if (*hr != S_OK)
    {
        PostQuitMessage(0);
    }

    M_Quad* pQmodel_ = new M_Quad();
    *hr = pQmodel_->Initialize();


    if (*hr != S_OK)
    {
        PostQuitMessage(0);
    }

        delete hr;

        XMMATRIX matG =
        {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1,
        };

        XMMATRIX matS =
        {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1,
        };

        float i = 0;

  //message loop (waiting for order some )
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //���b�Z�[�W�Ȃ�
        else
        {
          i =  fmod(i+=0.02, XM_PI);

            XMMATRIX matR =
            {
                sinf((i+ - XM_PI) / 3),cosf((i + -XM_PI) / 3),0,0,
                -cosf((i + -XM_PI) / 3),sinf((i + -XM_PI) / 3),0,0,
                0,0,1,0,
                0,0,0,1,
            };

            XMMATRIX mat = matG * matR * matS;
            //�Q�[���̏���

            CAM::Update();
            D3D::BeginDraw();
            pQmodel_->Draw(&mat);

            D3D::EndDraw();
        }
    }

    SAFE_RELEASE(pQmodel_);
    SAFE_DELETE(pQmodel_);

    D3D::Release();

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  //�v���O�����I��
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

