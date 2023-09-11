#include "DInput.h"
#include <string>

namespace Input
{
    LPDIRECTINPUT8   pDInput = nullptr;
    LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
    char keyState[256] = {};
    char prev_keyState[256] = {};

    LPDIRECTINPUTDEVICE8 mouseDevice;
    DIMOUSESTATE mouseState;
    DIMOUSESTATE prev_mouseState;
    XMFLOAT3 mousePosition;

    HRESULT Input::Initialize(HWND hWnd)
    {
        DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
        
        pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
        pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
        pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
  

        if (!(pDInput != nullptr && pKeyDevice != nullptr))
        {
            return E_FAIL;
        }

        pDInput->CreateDevice(GUID_SysMouse, &mouseDevice, nullptr);
        mouseDevice->SetDataFormat(&c_dfDIMouse);
        mouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

        return S_OK;
    }

    void Input::Update()
    {
        memcpy(prev_keyState, keyState, sizeof(keyState));
        pKeyDevice->Acquire();
        pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

        memcpy(&prev_mouseState, &mouseState, sizeof(mouseState));
        mouseDevice->Acquire();
        mouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
    }

    bool Input::IsKey(int code)
    {
        return static_cast<bool>(keyState[code] & 0b10000000);
    }

    bool IsKeyDown(int code)
    {
        return static_cast<bool>((keyState[code] & 0b10000000) & (~(prev_keyState[code]) & 0b10000000));
    }

    bool IsKeyUp(int code)
    {
        return static_cast<bool>(~(keyState[code] & 0b10000000) & ((prev_keyState[code]) & 0b10000000));
    }

    void Input::Release()
    {
        SAFE_RELEASE(pDInput);
        SAFE_RELEASE(pKeyDevice);
    }
    bool IsMouseButton(int code)
    {
        return  static_cast<bool>(mouseState.rgbButtons[code] & 0b10000000);
    }
    bool IsMouseButtonDown(int code)
    {
        return static_cast<bool>((mouseState.rgbButtons[code] & 0b10000000) & (~(prev_mouseState.rgbButtons[code]) & 0b10000000));
    }
    bool IsMouseButtonUp(int code)
    {
        return static_cast<bool>(~(mouseState.rgbButtons[code] & 0b10000000) & ((prev_mouseState.rgbButtons[code]) & 0b10000000));
    }
    XMFLOAT3 GetMousePosition()
    {
        return mousePosition;
    }
    XMFLOAT3 GetMouseMove()
    {
        XMFLOAT3 result = XMFLOAT3((float)mouseState.lX, (float)mouseState.lY, (float)mouseState.lZ);
        return result;
    }
    void SetMousePosition(XMFLOAT3 pos)
    {
        mousePosition = pos;
        mousePosition.z = 0;
    }
    void SetMousePosition(int x, int y)
    {
        mousePosition.x = x;
        mousePosition.y = y;
        mousePosition.z = 0;

       // std::string str = std::to_string(mousePosition.x) + ',' + std::to_string(mousePosition.y) + "\n";

       // OutputDebugString(str.c_str());
    }
}