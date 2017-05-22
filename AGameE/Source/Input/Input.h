#pragma once
#ifndef INPUT_H_
#define INPUT_H_

#include<Xinput.h>
#include<d3d12.h>
#include<dinput.h>

#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dinput8.lib")

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

class Input
{
	friend class InitEngine;
private:
	//constructor
	Input();
public:
	//Initialize XInput and any connected controllers
	bool XInput_Init(int contNum = 0);
	//Cause the controller to vibrate
	void XInput_Vibrate(int contNum = 0, int left = 65535, int right = 65535);
	//Checks the state of the controller
	void XInput_Update();

	bool DirectInput_Init(HWND hwnd);
	void DirectInput_Update();
	//DirectInput shutdown
	void DirectInput_Shutdown();

	//return mouse x movement
	int MouseX()	{ return m_MouseSTate.lX; }
	//return mouse y movement
	int MouseY()	{ return m_MouseSTate.lY; }
	//return mouse button state
	int MouseButton(int button)	{ return m_MouseSTate.rgbButtons[button] & 0x80; }
	//return key press state
	int KeyDown(int key)	{ return (m_Keys[key] & 0x80); }

	Input(Input& rhs) = delete;
	Input operator=(Input& rhs) = delete;

	~Input();
private:
	LPDIRECTINPUT8 m_DInput;
	LPDIRECTINPUTDEVICE8 m_DIMouse;
	LPDIRECTINPUTDEVICE8 m_DIKeyboard;
	DIMOUSESTATE m_MouseSTate;
	XINPUT_GAMEPAD m_Controllers[4];
	char m_Keys[256];
};
#endif // !INPUT_H_
