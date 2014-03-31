#include "stdafx.h"

#include "Ray.h"
#include "Application.h"
#include "Controller.h"
#include "IRenderer.h"

const float MOVEMENT_SPEED = 10.f;

const long DELTA_TIME = 50;

Ray::Ray()
  : m_elapsed_time(0)
{
}

Ray::~Ray()
{
}

void Ray::Update(long i_elapsed_time)
{
  m_elapsed_time += i_elapsed_time;
  if (m_elapsed_time >= DELTA_TIME)
    {
    m_bbox.SetMin(m_start_point);
    m_start_point += m_direction*MOVEMENT_SPEED;
    m_bbox.SetMax(m_start_point);
    }
}

void Ray::Render()
{
	IRenderer& renderer = Application::GetInstance().GetRenderer();

  Vector3D start_point(m_bbox.GetMin());
  Vector3D end_point(m_bbox.GetMax());
  end_point[0] += 5;
  
	renderer.RenderLine(Vector3D(start_point[0], start_point[1], 0), Vector3D(end_point[0], end_point[1], 0), Color(255, 0, 0, 255), 3.0F);

}

Box3D Ray::GetBBox() const
{
	return m_bbox;
}

void Ray::SetStartPoint(const Vector3D& i_start_point)
  {
  m_start_point = i_start_point;
  m_bbox.SetMin(m_start_point);
  m_bbox.SetMax(Vector3D(m_start_point[0]+1, m_start_point[1]+2, 0));
  }

void Ray::SetDirection(const Vector3D& i_direction)
  {
  m_direction = i_direction;
  m_direction.Normalize();
  }

void Ray::CollisionDetected(const std::set<std::shared_ptr<IObject>>& i_objects)
  {
  this->m_to_delete = true;
  }