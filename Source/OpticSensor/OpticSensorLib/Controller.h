#pragma once

#include <memory>
#include <vector>

class IObject;
class IObjectFactory;
enum class ObjectType : char;

class Controller 
{
	typedef std::shared_ptr<IObject> ObjectPtr;
private:
	std::vector<ObjectPtr>			m_objects;
	std::shared_ptr<IObjectFactory>	m_factory;

public:
	Controller();
	~Controller();

	void						SetObjectFactory(std::shared_ptr<IObjectFactory> i_factory);
	std::shared_ptr<IObject>	AddObject(ObjectType i_type);

	void						UpdateObjects();
	void						RenderObjects();
};