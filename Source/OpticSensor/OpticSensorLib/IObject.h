#pragma once

#include <MathBase\math\Box3D.h>

enum class ObjectType : char
{
	OT_BOX,
	OT_EMITTER,
	OT_DETECTOR,
	OT_RAY
};

class IObject
{
public:
	virtual ~IObject(){}

	virtual void Update(long i_elpsed_time) = 0;
	virtual void Render() = 0;

	virtual Box3D GetBBox() const = 0;
};