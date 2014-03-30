#pragma once

#include "IObject.h"
#include "IRenderer.h"

#include <memory>

class Emitter : public IObject
{
private:
	Vector3D	m_body_center;
	Color		m_body_color;
	size_t		m_body_width;
	size_t		m_body_hight;

	Vector3D	m_emitter_center;
	Color		m_emitter_color;
	size_t		m_emitter_radius;

	std::unique_ptr<Box3D>		mp_bbox;

public:
	Emitter();
	~Emitter();	
	
	void Update(long i_elpsed_time) override;
	void Render() override;
	Box3D GetBBox() const override;

	void SendRay();

};