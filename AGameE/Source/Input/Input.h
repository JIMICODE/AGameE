#pragma once
#ifndef INPUT_H_
#define INPUT_H_

#include<Xinput.h>
#include<d3d12.h>
#include<dinput.h>

#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dinput8.lib")

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

LPDIRECTINPUT8 gDInput;
LPDIRECTINPUTDEVICE8 gDIMouse;
LPDIRECTINPUTDEVICE8 gDIKeyboard;
DIMOUSESTATE gMouseSTate;
XINPUT_GAMEPAD gControllers[4];
char gKey[256];

//Initialize XInput and any connected controllers
bool XInput_Init(int contNum = 0)
{
	XINPUT_CAPABILITIES caps;
	ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
	XInputGetCapabilities(contNum, XINPUT_FLAG_GAMEPAD, &caps);

	if (caps.Type != XINPUT_DEVTYPE_GAMEPAD)
		return false;

	return true;
}

//Cause the controller to vibrate
void XInput_Vibrate(int contNum = 0, int left = 65535, int right = 65535)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = left;
	vibration.wRightMotorSpeed = right;
	XInputSetState(contNum, &vibration);
}

//Checks the state of the controller
void XInput_Update()
{
	XINPUT_STATE state;

	for (int i = 0; i < 4; ++i)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		//get the state of the controller
		DWORD result = XInputGetState(i, &state);

		//is controller connected?
		if (result == 0)
		{
			if (state.Gamepad.bLeftTrigger)
				break;
			else if (state.Gamepad.bRightTrigger)
				break;
			else if (state.Gamepad.sThumbLX < -10000 || state.Gamepad.sThumbLX > 10000)
				break;
			else if (state.Gamepad.sThumbRX < -10000 || state.Gamepad.sThumbRX > 10000)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				break;
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
				break;
		}
	}
}

bool DirectInput_Init(HWND hwnd)
{
	//initialize DirectInput object;
	HRESULT r = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&gDInput,
		NULL
	);

	//initialize the keyboard
	gDInput->CreateDevice(GUID_SysKeyboard, &gDIKeyboard, NULL);
	gDIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	gDIKeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	gDIKeyboard->Acquire();

	//initialize the mouse
	gDInput->CreateDevice(GUID_SysMouse, &gDIMouse, NULL);
	gDIMouse->SetDataFormat(&c_dfDIMouse);
	gDIMouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	gDIMouse->Acquire();
	
	return true;
}

void DirectInput_Update()
{
	//update mouse
	gDIMouse->GetDeviceState(sizeof(gMouseSTate), (LPVOID)&gMouseSTate);
	//update keyboard
	gDIKeyboard->GetDeviceState(sizeof(gKey), (LPVOID)&gKey);
}

//return mouse x movement
int MouseX()
{
	return gMouseSTate.lX;
}
//return mouse y movement
int MouseY()
{
	return gMouseSTate.lY;
}
//return mouse button state
int MouseButton(int button)
{
	return gMouseSTate.rgbButtons[button] & 0x80;
}
//return key press state
int KeyDown(int key)
{
	return (gKey[key] & 0x80);
}
//DirectInput shutdown
void DirectInput_Shutdown()
{
	if (gDIKeyboard)
	{
		gDIKeyboard->Unacquire();
		gDIKeyboard->Release();
		gDIKeyboard = NULL;
	}
	if (gDIMouse)
	{
		gDIMouse->Unacquire();
		gDIMouse->Release();
		gDIMouse = NULL;
	}
}

#endif // !INPUT_H_
