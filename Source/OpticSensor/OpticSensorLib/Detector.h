#pragma once

#include "IObject.h"
#include "IRenderer.h"

enum class DetectorState : char
{
	DS_Passive,		//Ray was detected
	DS_Active,		//Ray wasn't detected
	DS_Undefined
};

class Detector : public IObject
{
private:
	Vector3D	m_body_center;
	Color		m_body_color;
	size_t		m_body_width;
	size_t		m_body_hight;

	Vector3D	m_detector_center;
	Color		m_detector_color;
	size_t		m_detector_width;
	size_t		m_detector_hight;

	DetectorState	m_detector_state;

	std::unique_ptr<Box3D>		mp_bbox;
  long m_elapsed_time;

	void	ProcessState();

public:
	Detector();
	~Detector();	
	
	void Update(long i_elpsed_time) override;
	void Render() override;
	Box3D GetBBox() const override;
  void  CollisionDetected(const std::set<std::shared_ptr<IObject>>& i_objects) override;
};