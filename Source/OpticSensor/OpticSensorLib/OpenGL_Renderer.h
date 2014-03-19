#pragma once

#include "IRenderer.h"

#include "FreeType.h"


class OpenGL_Renderer : public IRenderer
  {
  private:
    HWND		m_hWND;

    int         m_pixel_format;
    HGLRC       m_hrc;
    HDC         m_hdc;

    freetype::font_data m_font_data;

	int m_width, m_height;

  public:
    OpenGL_Renderer(HWND i_parent, HDC i_hdc);
    virtual ~OpenGL_Renderer();

    virtual BOOL Initialize() override;
    virtual void Release() override;
    virtual void Reshape(int i_width, int i_height) override;

    virtual void RenderLine(const Vector3D& i_first_point, const Vector3D& i_second_point, Color i_color, float i_width = 1.0) override;
    virtual void RenderRectangle(const Vector3D& i_center, double i_width, double i_height, Color i_color) override;
    virtual void RenderCircle(const Vector3D& i_center, double i_radius, Color i_color) override;
    virtual void RenderText(const Vector3D& i_position, const std::wstring& i_text, Color i_color) override;
    virtual void RenderText(const Vector3D& i_position, const std::string& i_text, Color i_color) override;

    virtual void RenderScene() override;
  };