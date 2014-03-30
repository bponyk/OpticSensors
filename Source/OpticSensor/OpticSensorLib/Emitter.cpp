#include "stdafx.h"

#include "Emitter.h"
#include "Application.h"
#include "IRenderer.h"

Emitter::Emitter()
{
	RECT rect;
	::GetClientRect(Application::GetInstance().GetHWND(), &rect);

	m_body_width = 100;
	m_body_hight = 50;

	m_body_center = Vector3D(m_body_width/2, rect.bottom/2, 0);
	m_body_color = Color(0, 250, 250, 250);


	m_emitter_center = Vector3D(m_body_width, (rect.bottom - rect.top)/2, 0);
	m_emitter_color = Color(250, 0, 250, 250);
	m_emitter_radius = 20;

	Vector3D min_vec(0, m_body_center[1] - m_body_hight/2, 0);
	Vector3D max_vec(m_body_width + m_emitter_radius, m_body_center[1] + m_body_hight/2, 0);

	mp_bbox.reset(new Box3D(min_vec, max_vec));
}

Emitter::~Emitter()
{
}

void Emitter::Update(long i_elpsed_time)
{
	SendRay();
}

void Emitter::Render()
{
	IRenderer& renderer = Application::GetInstance().GetRenderer();

	renderer.RenderRectangle(m_body_center, m_body_width, m_body_hight, m_body_color);
	renderer.RenderCircle(m_emitter_center, m_emitter_radius, m_emitter_color);
}

Box3D Emitter::GetBBox() const
{
	return *mp_bbox.get();
}

void Emitter::SendRay()
{
}