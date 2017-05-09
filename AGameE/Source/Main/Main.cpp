#include"..\Common\Utility.h"
#include"..\Debug\Debugger.h"
#include<Windows.h>
#include"Init.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR lpCmdLine, int nCmdShow)
{
	EngineMain* theTest = new EngineMain(hInstance);

	if (theTest)
	{
		if (theTest->InitMainWindow())
			theTest->Run();
	}

	return 0;
}
