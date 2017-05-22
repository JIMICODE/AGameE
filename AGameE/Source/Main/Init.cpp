#include "Init.h"

InitEngine* InitEngine::pEMainIns = nullptr;

InitEngine* InitEngine::GetEMainIns()
{
	return pEMainIns;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return InitEngine::GetEMainIns()->MsgProc(hwnd, msg, wParam, lParam);
}

InitEngine::InitEngine(HINSTANCE Instance):m_Sound(), m_Input()
{
	assert(pEMainIns == nullptr);
	pEMainIns = this;
}

void InitEngine::SetAspectRatio(UINT Width, UINT Height)
{
	mWidth = Width;
	mHeight = Height;
}

void InitEngine::Initialization()
{
	ThrowIfFailed(InitMainWindow());
	ThrowIfFailed(InitSoundSys());
	ThrowIfFailed(InitInput());
}

bool InitEngine::InitMainWindow()
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

	m_hMainwnd = CreateWindow(L"MainWnd", mMainWndCaption.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, 0, mhMainIns, nullptr);

	if (!m_hMainwnd)
	{
		MessageBox(0, L"CreateWubdiw Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainwnd, SW_SHOW);
	UpdateWindow(m_hMainwnd);

	return true;
}

bool InitEngine::InitSoundSys()
{
	
	return m_Sound.DirectSound_Init(m_hMainwnd);
}

bool InitEngine::InitInput()
{
	return (m_Input.DirectInput_Init(m_hMainwnd)&&m_Input.XInput_Init());
}

void InitEngine::SoundSys_Shutdown()
{
	m_Sound.DirectSound_Shutdown();
}

int InitEngine::Run()
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

HINSTANCE InitEngine::GetMainIns() const
{
	return mhMainIns;
}

HWND InitEngine::GetMainHwnd() const
{
	return m_hMainwnd;
}

float InitEngine::GetASpectRatio() const
{
	return mAspectRatio;
}

/*EngineMain * EngineMain::GetEMainIns()
{
	return pEMainIns;
}*/

LRESULT InitEngine::MsgProc(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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

void InitEngine::OnMouseMove(WPARAM BtnState, int X, int Y)
{
	//To do...
}

void InitEngine::OnMouseUp(WPARAM BtnState, int X, int Y)
{
	//TO do...
}

void InitEngine::OnMouseDown(WPARAM BtnState, int X, int Y)
{
	//To do...
}
