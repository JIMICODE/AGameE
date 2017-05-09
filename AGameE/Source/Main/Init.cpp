#include "Init.h"

EngineMain* EngineMain::pEMainIns = nullptr;

EngineMain* EngineMain::GetEMainIns()
{
	return pEMainIns;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return EngineMain::GetEMainIns()->MsgProc(hwnd, msg, wParam, lParam);
}

EngineMain::EngineMain(HINSTANCE Instance)
{
	assert(pEMainIns == nullptr);
	pEMainIns = this;
}

void EngineMain::SetAspectRatio(UINT Width, UINT Height)
{
	mWidth = Width;
	mHeight = Height;
}

bool EngineMain::InitMainWindow()
{
	WNDCLASS wc;
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mhMainIns;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MainWnd";

	if (!RegisterClass(&wc))
	{
		MessageBox(nullptr, L"RegisterClass Failed.", nullptr, 0);
		return false;
	}

	//COmpute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mWidth, mHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	mhMainwnd = CreateWindow(L"MainWnd", mMainWndCaption.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, 0, mhMainIns, nullptr);

	if (!mhMainwnd)
	{
		MessageBox(0, L"CreateWubdiw Failed.", 0, 0);
		return false;
	}

	ShowWindow(mhMainwnd, SW_SHOW);
	UpdateWindow(mhMainwnd);

	return true;
}

int EngineMain::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		//If there are Window message then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Otherwise , do animation/game stuff
		{
			//To do...
		}
	}

	return (int)msg.wParam;
}

HINSTANCE EngineMain::GetMainIns() const
{
	return mhMainIns;
}

HWND EngineMain::GetMainHwnd() const
{
	return mhMainwnd;
}

float EngineMain::GetASpectRatio() const
{
	return mAspectRatio;
}

/*EngineMain * EngineMain::GetEMainIns()
{
	return pEMainIns;
}*/

LRESULT EngineMain::MsgProc(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_ACTIVATE:
		return 0;
	case WM_SIZE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(Hwnd, Msg, wParam, lParam);
}

void EngineMain::OnMouseMove(WPARAM BtnState, int X, int Y)
{
	//To do...
}

void EngineMain::OnMouseUp(WPARAM BtnState, int X, int Y)
{
	//TO do...
}

void EngineMain::OnMouseDown(WPARAM BtnState, int X, int Y)
{
	//To do...
}
