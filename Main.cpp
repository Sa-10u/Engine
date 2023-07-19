#include <Windows.h>
#include<cstdlib>
#include "D3D.h"
#include "Engine/DInput.h"
#include "Engine/MACRO.h"
#include "Engine/CAM.h"
#include "Engine/RootOBJ.h"
#include "Engine/Model.h"

#pragma comment(lib,"winmm.lib")

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

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
    wc.hInstance = hInstance;                   //インスタンスハンドル
    wc.lpszClassName = WIN::_NAME;            //ウィンドウクラス名
    wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
    wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
    wc.hIcon = LoadIcon(NULL, IDI_QUESTION); //アイコン
    wc.hIconSm = LoadIcon(NULL, IDI_QUESTION);   //小さいアイコン
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
    wc.lpszMenuName = NULL;                     //メニュー（なし）
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); //背景（白）

    RegisterClassEx(&wc);

    HWND hWnd = CreateWindow(
        WIN::_NAME,         //ウィンドウクラス名
        WIN::_BAR,     //タイトルバーに表示する内容
        WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
        CW_USEDEFAULT,       //表示位置左（おまかせ）
        CW_USEDEFAULT,       //表示位置上（おまかせ）
        winW,                 //ウィンドウ幅
        winH,                 //ウィンドウ高さ
        NULL,                //親ウインドウ（なし）
        NULL,                //メニュー（なし）
        hInstance,           //インスタンス
        NULL                 //パラメータ（なし）
    );

    ShowWindow(hWnd, nCmdShow);

    //---------------
    D3D::Initialize(WIN::_WIDTH,WIN::_HEIGHT,hWnd);
    CAM::Initialize();
    Input::Initialize(hWnd);
    
    RootOBJ* ROBJ = new RootOBJ(nullptr);
    ROBJ->Initialize();


    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        else
        {
            timeBeginPeriod(1);

            static unsigned long cnt_;
            static unsigned long starttime_ = timeGetTime();
            unsigned long nowtime_ = timeGetTime();
            static unsigned long lasttime_ = nowtime_;

            if ((nowtime_ - lasttime_) * 60.0 <= 1000.0f)
            {
                continue;
            }

            if (nowtime_ - starttime_ >= 1000)
            {
                char str[16];
                wsprintf(str, "%u", cnt_);
                SetWindowText(hWnd, str);

                starttime_ = nowtime_;
                cnt_ = 0;
            }

            lasttime_ = nowtime_;

            cnt_++;


            timeEndPeriod(1);


            D3D::BeginDraw();
            CAM::Update();
            Input::Update();

            ROBJ->UpdateALL();
            ROBJ->DrawALL();

            (ROBJ->*(ROBJ->IsDoDisposal[ROBJ->IsDisposal()]))();
            ROBJ->EndDisposal();

            D3D::EndDraw();

           
        }
    }


    Model::Release();
    D3D::Release();
    Input::Release();
    ROBJ->Release();
    SAFE_DELETE(ROBJ);

	return 0;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

