#pragma once

#ifndef INITMAIN_H_
#define INITMAIN_H_

#include<Windows.h>
#include<windowsx.h>
#include<string>
#include"..\Common\Utility.h"
#include"..\Sound\Sound.h"
#include"..\Input\Input.h"

class InitEngine
{
public:
	InitEngine(HINSTANCE Instance);
	//Set width and height befor the InitMainWindow() has been used.
	void SetAspectRatio(UINT Width, UINT Height);

	//Intializations function
	void Initialization();
	bool InitMainWindow();
	bool InitSoundSys();
	bool InitInput();
	//bool InitOutput();

	void SoundSys_Shutdown();
	int Run();
	//process window message.
	virtual LRESULT MsgProc(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);


public:
	HINSTANCE GetMainIns()const;
	HWND GetMainHwnd()const;
	float GetASpectRatio()const;
	
	static InitEngine* GetEMainIns();

protected:

	static InitEngine* pEMainIns;
	
	HINSTANCE mhMainIns = nullptr; //Application instance handle.
	HWND m_hMainwnd = nullptr;	  //Main window handle.
	float mAspectRatio = 0.0f;	  //Aspect ratio of window.
	UINT mWidth = 800;
	UINT mHeight = 600;

	SoundSys m_Sound;
	Input m_Input;

	std::wstring mMainWndCaption = L"Main Window";

protected:
	virtual void OnMouseMove(WPARAM BtnState, int X, int Y);
	virtual void OnMouseUp(WPARAM BtnState, int X, int Y);
	virtual void OnMouseDown(WPARAM BtnState, int X, int Y);

};



#endif // INIT_H_