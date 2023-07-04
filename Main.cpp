#include <Windows.h>
#include "D3D.h"
#include "DInput.h"
#include "Sprite.h"
#include "MACRO.h"
#include "CAM.h"
#include "Dice.h"
#include "Sprite.h"
#include "FBX.h"

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

    *hr =  Input::Initialize(hWnd);

    if (*hr != S_OK)
    {
        PostQuitMessage(0);
    }

    //----------------------------------------
  //  M_Quad* pQmodel_ = new Sprite();
  //  *hr = pQmodel_->Initialize();
   //   Dice* dice = new Dice();
    // *hr = dice->Initialize();
  //  Sprite* spr = new Sprite;
  //  *hr = spr->Initialize(winW,winH);
    Fbx* model = new Fbx;
    model->Load("Assets/Sphere.fbx");

    Fbx* sub= new Fbx;
    sub->Load("Assets/O-DEN.fbx");

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
            2,0,0,0,
            0,2,0,0,
            0,0,2,0,
            0,0,0,1,
        };

        float i = 1;
        float j = fmod(i,360) + 1;

        int cnt = 0;

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
         i =  fmod(i+=0.0008, XM_PI*2);

         j = fmod(j += 0.0004, XM_PI * 2);

         XMFLOAT4 WorldLight(1.5, 1.5, 2.0, 0);
         XMFLOAT4 WorldLightPos(sinf(i), 0,-0.5, 0);

            XMMATRIX matRZ =
            {
                sinf((i) ),cosf((i) ),0,0,
                -cosf((i) ),sinf((i) ),0,0,
                0,0,1,0,
                0,0,0,1,
            };

            XMMATRIX matRY =
            {
                cosf(j),0,-sinf(j),0,
                0,1,0,0,
                sinf(j),0,cosf(j),0,
                0,0,0,1,
            };

            Trans trans;
            trans.rot = XMFLOAT3(0, 3.14/2, 0);
            trans.pos = XMFLOAT3(cosf(i) * 3, -1, 0);
            trans.size = XMFLOAT3(0.5, 0.5, 0.5);

            Trans sptra;
            sptra.rot = XMFLOAT3(0, 3.14/2, 0);
            sptra.pos = XMFLOAT3(-2, -1, 0);
            sptra.size = XMFLOAT3(0.5, 0.5, 0.5);

           // XMMATRIX mat = matRY * matRZ *matG  * matS; 
            //�Q�[���̏���

            CAM::Update();
            D3D::BeginDraw();

          // pQmodel_->Draw(&matRY , &WorldLight);
            model->Draw(&trans, WorldLight , WorldLightPos);
            model->Draw(&sptra, WorldLight, WorldLightPos);
            Input::Update();

            if (Input::IsKeyUp(DIK_ESCAPE))
            {
                cnt++;
              
                if (cnt >= 3)      PostQuitMessage(0);
            }
            

            D3D::EndDraw();
        }
    }

  //  SAFE_RELEASE(pQmodel_);
   // SAFE_DELETE(pQmodel_);
   // SAFE_RELEASE(dice);
   // SAFE_DELETE(dice);
   // SAFE_RELEASE(spr);
  //  SAFE_DELETE(spr);

    D3D::Release();
    Input::Release();

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

