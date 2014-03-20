#include "stdafx.h"

#include "Box.h"
#include "Application.h"
#include "IRenderer.h"

Box::Box()
{
	m_size[0] = 0;
	m_size[1] = 0;
}

Box::Box(const Vector3D& i_center, size_t i_width, size_t i_height)
	: m_Center(i_center)
{
	m_size[0] = i_width;
	m_size[1] = i_height;
}

Box::~Box()
{
}

void Box::Update()
{
}

void Box::Render()
{
	Application::GetInstance().GetRenderer().RenderRectangle(m_Center, m_size[0], m_size[1], Color(255, 255, 255, 255));
}