#include "stdafx.h"

#include "Box.h"
#include "Application.h"
#include "IRenderer.h"

//#include <MathBase\math\Box3D.h>

Box::Box()
{
	m_size[0] = 0;
	m_size[1] = 0;

	Vector3D min_vec(0, 0, 0);
	Vector3D max_vec(0, 0, 0);
	
	mp_bbox.reset(new Box3D(min_vec, max_vec));
}

Box::Box(const Vector3D& i_center, size_t i_width, size_t i_height)
	: m_Center(i_center)
{
	m_size[0] = i_width;
	m_size[1] = i_height;

	Vector3D min_vec(i_center[0] - m_size[0]/2, i_center[1] - m_size[1]/2, 0);
	Vector3D max_vec(i_center[0] + m_size[0]/2, i_center[1] + m_size[1]/2, 0);
	
	mp_bbox.reset(new Box3D(min_vec, max_vec));
}

Box::~Box()
{
}

void Box::Update(long i_elpsed_time)
{
}

void Box::Render()
{
	Application::GetInstance().GetRenderer().RenderRectangle(m_Center, m_size[0], m_size[1], Color(255, 255, 255, 255));
}

Box3D Box::GetBBox() const
{
	return *mp_bbox.get();
}

Vector3D Box::GetCenter() const
{
	return m_Center;
}

size_t	 Box::GetWidth() const
{
	return m_size[0];
}

size_t	 Box::GetHeight() const
{
	return m_size[1];
}

Vector3D& Box::AccessCenter()
{
	return m_Center;
}

size_t&	 Box::AccessWidth()
{
	return m_size[0];
}

size_t&	 Box::AccessHeight()
{
	return m_size[1];
}