#include "DInput.h"

namespace Input
{
    LPDIRECTINPUT8   pDInput = nullptr;
    LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
    char keyState[256] = {};
    char prev_keyState[256] = {};

    HRESULT Input::Initialize(HWND hWnd)
    {
        DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
        
        pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
        pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
        pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
  

        if (pDInput != nullptr && pKeyDevice != nullptr)
        {
            return S_OK;
        }

        return E_FAIL;
    }

    void Input::Update()
    {
        memcpy(prev_keyState, keyState, sizeof(keyState));

        pKeyDevice->Acquire();
        pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
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
}