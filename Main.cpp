#include <Windows.h>
#include "D3D.h"
#include "M_Quad.h"
#include "MACRO.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace WIN
{
    const char _BAR[] = "What is this?";
    const char _NAME[] = "SampleGame";

    const int _HEIGHT = 720 ;
    const int _WIDTH = 1260;
}



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{


    RECT winRect = { 0, 0, WIN::_WIDTH, WIN::_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     
    int winH = winRect.bottom - winRect.top;

  //create window class
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

  //create window
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

  //output window
    ShowWindow(hWnd, nCmdShow);

    //-----------
    
    
    HRESULT* hr = new HRESULT;
    *hr = E_FAIL;
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

  //message loop (waiting for order some )
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //メッセージなし
        else
        {
            //ゲームの処理
            D3D::BeginDraw();
            pQmodel_->Draw();

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
        PostQuitMessage(0);  //プログラム終了
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

