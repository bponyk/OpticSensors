#include "stdafx.h"

#include "Application.h"
#include "Detector.h"
#include "IRenderer.h"
#include "Ray.h"

#include <algorithm>

const long DELTA_TIME = 100;

Detector::Detector()
  : m_elapsed_time(0)
{
	RECT rect;
	::GetClientRect(Application::GetInstance().GetHWND(), &rect);

	m_body_width = 100;
	m_body_hight = 50;
	m_body_center = Vector3D(rect.right-m_body_width/2, rect.bottom/2, 0);
  m_body_color = Color(0, 250, 250, 250);

	m_detector_center = Vector3D(rect.right - m_body_width, rect.bottom/2, 0);
	m_detector_color = Color(250, 0, 250, 250);
	m_detector_width = 10;
	m_detector_hight = 20;

	m_detector_state = DetectorState::DS_Undefined;

	Vector3D min_vec(m_body_center[0] - m_body_width/2 - m_detector_width, m_body_center[1] - m_body_hight/2, 0);
	Vector3D max_vec(m_body_center[0] + m_body_width/2, m_body_center[1] + m_body_hight/2, 0);

	mp_bbox.reset(new Box3D(min_vec, max_vec));
}

Detector::~Detector()
{
}

void Detector::Update(long i_elpsed_time)
{
  if (m_detector_state == DetectorState::DS_Active)
    {
    m_elapsed_time += i_elpsed_time;
    ProcessState();
    }
}

void Detector::Render()
{
	IRenderer& renderer = Application::GetInstance().GetRenderer();

	renderer.RenderRectangle(m_body_center, m_body_width, m_body_hight, m_body_color);
	renderer.RenderRectangle(m_detector_center, m_detector_width, m_detector_hight, m_detector_color);
}

Box3D Detector::GetBBox() const
{
	return *mp_bbox.get();
}

void Detector::ProcessState()
{
  if (m_detector_state == DetectorState::DS_Active && m_elapsed_time >= DELTA_TIME)
    {
    m_detector_state = DetectorState::DS_Passive;
    m_body_color = Color(0, 250, 250, 250);
    return;
    }
}

void Detector::CollisionDetected(const std::set<std::shared_ptr<IObject>>& i_objects)
  {
  std::for_each(i_objects.cbegin(), i_objects.cend(), [this](ObjectPtr i_object)
    {
    if (typeid(*i_object.get()) == typeid(Ray))
      {
      m_detector_state = DetectorState::DS_Active;
      m_elapsed_time = 0;
      m_body_color = Color(250, 0, 0, 250);
      }
    });
  }