#pragma once

#include <memory>

#include <string>

class IRenderer;
class Controller;
class Box;

class Application
{
private:
	bool		m_fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default
	HDC			m_hDC;			// Private GDI Device Context
	HGLRC		m_hRC;			// Permanent Rendering Context
	HWND		m_hWnd;			// Holds Our Window Handle
	HINSTANCE	m_hInstance;	// Holds The Instance Of The Application

	static std::unique_ptr<Application>	mg_instance;
	bool								m_active;
	std::unique_ptr<IRenderer>			mp_renderer;
	std::unique_ptr<Controller>			mp_controller;
	
	Box*					mp_box;

private:
	Application();

	void				_ReleaseWindow();

	BOOL				_Create(const std::wstring& i_title, size_t i_width, size_t i_height, int i_bits, bool i_full_screen);

public:
	void				Start(const std::wstring& i_title, size_t i_width, size_t i_height, int i_bits, bool i_full_screen);
	void				Destroy();

	void				OnResize(int i_width, int i_height);
	void				OnActivate(BOOL i_value);
	void				OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void				OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	inline HWND			GetHWND() const;

	IRenderer&			        GetRenderer();
  inline Controller&      GetController();

	static Application& GetInstance();
};

//////////////////////////////////////////////////////////////////////////

HWND Application::GetHWND() const
{
	return m_hWnd;
}

Controller& Application::GetController()
  {
  return *mp_controller.get();
  }