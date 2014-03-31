#pragma once

#include "IObject.h"
#include <MathBase\math\Vector3D.h>
#include <MathBase\math\Box3D.h>

class Box : public IObject
{
private:
	Vector3D m_Center;
	size_t	 m_size[2];

	std::unique_ptr<Box3D>		mp_bbox;

public:
	Box();
	Box(const Vector3D& i_center, size_t i_width, size_t i_height);
	virtual ~Box();

	virtual void	Update(long i_elpsed_time) override;
	virtual void	Render() override;

	Vector3D		GetCenter() const;
	size_t			GetWidth() const;
	size_t			GetHeight() const;
	
	Vector3D&		AccessCenter();
	size_t&			AccessWidth();
	size_t&			AccessHeight();

	Box3D       GetBBox() const override;
  void        CollisionDetected(const std::set<std::shared_ptr<IObject>>& i_objects) override;
};