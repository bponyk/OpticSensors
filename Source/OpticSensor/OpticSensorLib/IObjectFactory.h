#pragma once

class IObject;
enum class ObjectType : char;

class IObjectFactory
{
public:
	virtual ~IObjectFactory(){}

	virtual std::unique_ptr<IObject> CreateObject(ObjectType i_type) = 0;
};