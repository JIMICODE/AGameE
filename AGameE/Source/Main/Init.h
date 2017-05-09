#pragma once

#ifndef INITMAIN_H_
#define INITMAIN_H_

#include<Windows.h>
#include<windowsx.h>
#include<string>
#include"..\Common\Utility.h"

class EngineMain
{
public:
	EngineMain(HINSTANCE Instance);
	//Set width and height befor the InitMainWindow() has been used.
	void SetAspectRatio(UINT Width, UINT Height);
	bool InitMainWindow();
	int Run();
	//process window message.
	virtual LRESULT MsgProc(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);


public:
	HINSTANCE GetMainIns()const;
	HWND GetMainHwnd()const;
	float GetASpectRatio()const;
	
	static EngineMain* GetEMainIns();

protected:

	static EngineMain* pEMainIns;
	
	HINSTANCE mhMainIns = nullptr; //Application instance handle.
	HWND mhMainwnd = nullptr;	  //Main window handle.
	float mAspectRatio = 0.0f;	  //Aspect ratio of window.
	UINT mWidth = 800;
	UINT mHeight = 600;

	std::wstring mMainWndCaption = L"Main Window";

protected:
	virtual void OnMouseMove(WPARAM BtnState, int X, int Y);
	virtual void OnMouseUp(WPARAM BtnState, int X, int Y);
	virtual void OnMouseDown(WPARAM BtnState, int X, int Y);

};



#endif // INIT_H_