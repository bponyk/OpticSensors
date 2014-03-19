#pragma once

enum class ObjectType : char
{
	OT_BOX,
	OT_SENSOR,
	OT_RAY
};

class IObject
{
public:
	virtual ~IObject(){}

	virtual void Update() = 0;
	virtual void Render() = 0;
};