#include "stdafx.h"

#include "Ray.h"
#include "Application.h"
#include "IRenderer.h"


Ray::Ray()
{
	m_emitter_position = 240;
	m_distanse = 500;
}

Ray::~Ray()
{
}

void Ray::Update()
{
}

void Ray::Render()
{
	IRenderer& renderer = Application::GetInstance().GetRenderer();

	renderer.RenderLine(Vector3D(100, m_emitter_position,0), Vector3D(m_distanse, m_emitter_position, 0), Color(255, 0, 0, 255), 5.0F);

}