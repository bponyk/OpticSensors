#include "stdafx.h"

#include "Application.h"
#include "Controller.h"
#include "Emitter.h"
#include "IRenderer.h"
#include "Ray.h"

const long DELTA_TIME = 100;

Emitter::Emitter()
  : m_elapsed_time(0)
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
  m_elapsed_time += i_elpsed_time;
  if (m_elapsed_time >= DELTA_TIME)
    {
    SendRay();
    m_elapsed_time = 0;
    }
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
  Ray& ray = static_cast<Ray&>(*Application::GetInstance().GetController().AddObject(ObjectType::OT_RAY).get());
  ray.SetStartPoint(Vector3D(m_emitter_center[0] + m_emitter_radius + 1, m_emitter_center[1], 0));
  ray.SetDirection(Vector3D(1,0,0));
}

void Emitter::CollisionDetected(const std::set<std::shared_ptr<IObject>>& i_objects)
  {

  }