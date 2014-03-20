#pragma once

#include "IObject.h"
#include <MathBase\math\Vector3D.h>

class Box : public IObject
{
private:
	Vector3D m_Center;
	size_t	 m_size[2];

public:
	Box();
	Box(const Vector3D& i_center, size_t i_width, size_t i_height);
	~Box();

	virtual void Update() override;
	virtual void Render() override;
};