#include "stdafx.h"

#include "Sensor.h"
#include "Application.h"
#include "IRenderer.h"
#include "Ray.h"

Sensor::Sensor()
	: mp_Ray(new Ray)
{
	m_emitter_position = 240;
	m_distanse = 500;
}

Sensor::~Sensor()
{
}

void Sensor::Update()
{
	mp_Ray->Update();
}

void Sensor::Render()
{
	IRenderer& renderer = Application::GetInstance().GetRenderer();

	//Emitter
	renderer.RenderRectangle(Vector3D(50, m_emitter_position, 0), 100, 50, Color(0, 250, 0, 250));
	renderer.RenderCircle(Vector3D(100, m_emitter_position, 0), 20, Color(250, 0, 0, 250));

	//Detector
	renderer.RenderRectangle(Vector3D(50 + m_distanse, m_emitter_position, 0), 100, 50, Color(0, 250, 0, 250));
	renderer.RenderRectangle(Vector3D(m_distanse, m_emitter_position, 0), 20, 20, Color(250, 0, 0, 250));

	mp_Ray->Render();
}