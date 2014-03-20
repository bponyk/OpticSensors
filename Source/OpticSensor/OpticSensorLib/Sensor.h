#pragma once

#include "IObject.h"

#include <memory>

class Ray;

class Sensor : public IObject
{
private:
	size_t	 m_emitter_position;
	size_t	 m_distanse;

	std::unique_ptr<Ray> mp_Ray;

public:
	Sensor();
	~Sensor();

	virtual void Update() override;
	virtual void Render() override;
};