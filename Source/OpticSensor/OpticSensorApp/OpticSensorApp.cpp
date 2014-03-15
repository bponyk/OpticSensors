// OpticSensorApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <OpticSensorLib\Application.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	Application app;
	app.Start();
	app.Release();
	return 0;
}

