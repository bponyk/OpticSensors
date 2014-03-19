// OpticSensorApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <OpticSensorLib\Application.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	bool fullscreen = FALSE;

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,L"Would You Like To Run In Fullscreen Mode?", L"Start FullScreen?",MB_YESNO|MB_ICONQUESTION) == IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}
	Application::GetInstance().Start(L"Optic sensor", 640, 480, 16, fullscreen);
	return 0;
}

