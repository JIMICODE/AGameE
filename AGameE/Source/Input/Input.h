#pragma once
#ifndef INPUT_H_
#define INPUT_H_

#include<Xinput.h>
#include<d3d12.h>

#pragma comment(lib, "xinput.lib")

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

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

#endif // !INPUT_H_
