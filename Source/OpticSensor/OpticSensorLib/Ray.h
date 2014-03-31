#pragma once

#include "IObject.h"
#include "MathBase\math\Vector3D.h"

class Ray : public IObject
{
private:
	Vector3D m_start_point;
  Vector3D m_direction;

  // simplified variant: we suppose that ray will be 
  // parallel to x axis, to we need not implement rotation matrices
  Box3D m_bbox;

  long m_elapsed_time;

public:
	Ray();
	~Ray();

	void SetStartPoint(const Vector3D& i_start_point);
	void SetDirection(const Vector3D& i_direction);

	virtual void Update(long i_elpsed_time) override;
	virtual void Render() override;
	Box3D GetBBox() const override;
  void  CollisionDetected(const std::set<std::shared_ptr<IObject>>& i_objects) override;
};