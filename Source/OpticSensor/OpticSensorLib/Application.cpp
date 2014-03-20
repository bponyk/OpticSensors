#include "stdafx.h"

#include "Application.h"
#include "Controller.h"
#include "OpenGL_Renderer.h"
#include "IObject.h"
#include "Box.h"

#include <GL/glew.h>
#include <GL/wglew.h>

#include <cassert>
#include <functional>

namespace
{

	LRESULT	CALLBACK WndProc(HWND i_hwnd, UINT i_message, WPARAM i_wparam, LPARAM i_lparam)
	{
		Application& application = Application::GetInstance();
		switch (i_message)									// Check For Windows Messages
		{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			application.OnActivate(HIWORD(i_wparam));
			return 0;								// Return To The Message Loop
		}
		
		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (i_wparam)						// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			application.OnKeyDown(i_wparam, HIWORD(i_lparam), LOWORD(i_lparam));
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			application.OnKeyUp(i_wparam, HIWORD(i_lparam), LOWORD(i_lparam));
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			application.OnResize(LOWORD(i_lparam),HIWORD(i_lparam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(i_hwnd, i_message, i_wparam, i_lparam);
	}

} // namespace

///////////////////////////////////////////////////////////////
// construction

std::unique_ptr<Application>	Application::mg_instance = nullptr;

Application::Application()
	: m_fullscreen(false)
	, m_hDC(nullptr)
	, m_hInstance(nullptr)
	, m_hRC(nullptr)
	, m_hWnd(nullptr)
	, mp_box(nullptr)
{
}

Application& Application::GetInstance()
{
	if (!mg_instance)
		mg_instance.reset(new Application);
	return *mg_instance.get();
}

void Application::Start(const std::wstring& i_title, size_t i_width, size_t i_height, int i_bits, bool i_full_screen)
{
	MSG		msg;									// Windows Message Structure

	// Create Our OpenGL Window
	if (_Create(i_title, i_width, i_height, i_bits, i_full_screen) == FALSE)
		return;										// Quit If Window Was Not Created

	assert (mp_renderer);


	while(m_active)								// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				m_active = false;					// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else
		{
			//draw scene if we are active now
			mp_renderer->RenderScene();
			mp_controller->UpdateObjects();
		}
	}

	// Shutdown
	Destroy();										// Kill The Window
	return;											// Exit The Program
}

///////////////////////////////////////////////////////////////

BOOL Application::_Create(const std::wstring& i_title, size_t i_width, size_t i_height, int i_bits, bool i_full_screen)
{
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)i_width;		// Set Right Value To Requested i_width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)i_height;	// Set Bottom Value To Requested i_height

	m_fullscreen = i_full_screen;			// Set The Global Fullscreen Flag

	m_hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= m_hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= L"OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,L"Failed To Register The Window Class.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (m_fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= i_width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= i_height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= i_bits;				// Selected Bits Per Pixel
		dmScreenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",L"Optic sensor",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				m_fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,L"Program Will Now Close.",L"ERROR", MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (m_fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(m_hWnd=CreateWindowEx(	dwExStyle,						// Extended Style For The Window
								L"OpenGL",							// Class Name
								i_title.c_str(),					// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window i_width
								WindowRect.bottom-WindowRect.top,	// Calculate Window i_height
								NULL,								// No Parent Window
								NULL,								// No Menu
								m_hInstance,						// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		_ReleaseWindow();								// Reset The Display
		MessageBox(NULL,L"Window Creation Error.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	
	
	if (!(m_hDC=GetDC(m_hWnd)))						// Did We Get A Device Context?
	{
		_ReleaseWindow();							// Reset The Display
		MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	mp_renderer.reset(new OpenGL_Renderer(m_hWnd, m_hDC));

	if (!mp_renderer->Initialize())									// Initialize Our Newly Created GL Window
	{
		_ReleaseWindow();								// Reset The Display
		MessageBox(NULL,L"Initialization Failed.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(m_hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(m_hWnd);					// Slightly Higher Priority
	SetFocus(m_hWnd);								// Sets Keyboard Focus To The Window
	OnResize(i_width, i_height);					// Set Up Our Perspective GL Screen

	mp_controller.reset(new Controller);
	mp_box = static_cast<Box*>(mp_controller->AddObject(ObjectType::OT_BOX).get());
	mp_box->AccessCenter() = Vector3D(320, 450, 0);
	mp_box->AccessWidth() = 50;
	mp_box->AccessHeight() = 50;

	mp_controller->AddObject(ObjectType::OT_SENSOR);

	std::function<void()> draw_function = std::bind(&Controller::RenderObjects, mp_controller.get());
	mp_renderer->SetDrawSceneFunction(draw_function);

	m_active = true;
	return TRUE;									// Success
}

void Application::Destroy()
{
	_ReleaseWindow();
}

IRenderer& Application::GetRenderer()
{
	return *mp_renderer;
}

///////////////////////////////////////////////////////////////

void Application::OnResize(int i_width, int i_height)
{
	if (!mp_renderer)
		return;
	if (i_height == 0)									// Prevent A Divide By Zero By
	{
		i_height = 1;									// Making Height Equal One
	}

	mp_renderer->Reshape(i_width, i_height);
}

void Application::OnActivate(BOOL i_value)
{
}

void Application::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (mp_box == nullptr)
		return;
	switch (nChar)
	{
	case 0x57: // W
	case VK_UP:
		mp_box->AccessCenter()[1] -= 5;
		break;

	case 0x41: // A
	case VK_LEFT:
		mp_box->AccessCenter()[0] -= 5;
		break;

	case 0x53: // S
	case VK_DOWN:
		mp_box->AccessCenter()[1] += 5;
		break;

	case 0x44: // D
	case VK_RIGHT:
		mp_box->AccessCenter()[0] += 5;
		break;
	}
}

void Application::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_ESCAPE:
		m_active = false;
		break;
	}
}

void Application::_ReleaseWindow()
{
	if (m_fullscreen)									// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (m_hRC)											// Do We Have A Rendering Context?
	{
		if (mp_renderer)
			mp_renderer->Release();
		m_hRC=NULL;										// Set RC To NULL
	}

	if (m_hDC && !ReleaseDC(m_hWnd, m_hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		m_hDC=NULL;										// Set DC To NULL
	}

	if (m_hWnd && !DestroyWindow(m_hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,L"Could Not Release hWnd.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass(L"OpenGL",m_hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,L"Could Not Unregister Class.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hInstance=NULL;									// Set hInstance To NULL
	}
}