#include "Input.h"

bool Input::XInput_Init(int contNum)
{
	XINPUT_CAPABILITIES caps;
	ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
	XInputGetCapabilities(contNum, XINPUT_FLAG_GAMEPAD, &caps);

	if (caps.Type != XINPUT_DEVTYPE_GAMEPAD)
		return false;

	return true;
}

void Input::XInput_Vibrate(int contNum, int left, int right)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = left;
	vibration.wRightMotorSpeed = right;
	XInputSetState(contNum, &vibration);
}

void Input::XInput_Update()
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

bool Input::DirectInput_Init(HWND hwnd)
{
	//initialize DirectInput object;
	HRESULT r = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_DInput,
		NULL
	);

	//initialize the keyboard
	m_DInput->CreateDevice(GUID_SysKeyboard, &m_DIKeyboard, NULL);
	m_DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	m_DIKeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	m_DIKeyboard->Acquire();

	//initialize the mouse
	m_DInput->CreateDevice(GUID_SysMouse, &m_DIMouse, NULL);
	m_DIMouse->SetDataFormat(&c_dfDIMouse);
	m_DIMouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	m_DIMouse->Acquire();

	return true;
}

void Input::DirectInput_Update()
{
	//update mouse
	m_DIMouse->GetDeviceState(sizeof(m_MouseSTate), (LPVOID)&m_MouseSTate);
	//update keyboard
	m_DIKeyboard->GetDeviceState(sizeof(m_Keys), (LPVOID)&m_Keys);
}

void Input::DirectInput_Shutdown()
{
	if (m_DIKeyboard)
	{
		m_DIKeyboard->Unacquire();
		m_DIKeyboard->Release();
		m_DIKeyboard = NULL;
	}
	if (m_DIMouse)
	{
		m_DIMouse->Unacquire();
		m_DIMouse->Release();
		m_DIMouse = NULL;
	}
}
