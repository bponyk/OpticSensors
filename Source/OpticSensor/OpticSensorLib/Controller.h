#pragma once

#include "CollisionManager.h"

#include <map>
#include <memory>

class IObject;
class IObjectFactory;

enum class ObjectType : char;

typedef std::shared_ptr<IObject> ObjectPtr;

class Controller 
{
private:
  CollisionManager            m_collision_manager;
	std::vector<ObjectPtr>			m_objects;

  std::vector<ObjectPtr>      m_new_objects;

	std::shared_ptr<IObjectFactory>	m_factory;

public:
	Controller();
	~Controller();

	void						          SetObjectFactory(std::shared_ptr<IObjectFactory> i_factory);
	std::shared_ptr<IObject>	AddObject(ObjectType i_type);

	void						          UpdateObjects(long i_elapsed_time);
	void						          RenderObjects();
  std::vector<ObjectPtr>&   GetObjects();
};