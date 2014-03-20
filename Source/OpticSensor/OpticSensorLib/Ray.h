#pragma once

#include "IObject.h"
#include "MathBase\math\Vector3D.h"

class Ray : public IObject
{
private:
	size_t   m_emitter_position;
	size_t	 m_distanse;

public:
	Ray();
	~Ray();

	void SetEmitterPosition(const Vector3D& i_position);
	void SetDetectorPosition(const Vector3D& i_position);

	virtual void Update() override;
	virtual void Render() override;
};