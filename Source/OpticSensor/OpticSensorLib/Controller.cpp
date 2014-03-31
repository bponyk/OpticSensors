#include "stdafx.h"

#include "Controller.h"
#include "IObject.h"
#include "IObjectFactory.h"
#include "Box.h"
#include "Emitter.h"
#include "Detector.h"
#include "Ray.h"

#include <algorithm> 
#include <exception>

namespace
{
	class DefaultObjectFactory : public IObjectFactory
	{
		virtual std::shared_ptr<IObject> CreateObject(ObjectType i_type) override
		{
			switch(i_type)
			{
			case ObjectType::OT_BOX:
				return std::make_shared<Box>();

			case ObjectType::OT_EMITTER:
				return std::make_shared<Emitter>();

			case ObjectType::OT_DETECTOR:
				return std::make_shared<Detector>();

			case ObjectType::OT_RAY:
				return std::make_shared<Ray>();

			default:
				return nullptr;
			};
			return nullptr;
		}
	};
}


Controller::Controller()
	: m_factory(new DefaultObjectFactory())
{
}

Controller::~Controller()
{
}

void Controller::SetObjectFactory(std::shared_ptr<IObjectFactory> i_factory)
{
	m_factory = i_factory;
}

std::shared_ptr<IObject> Controller::AddObject(ObjectType i_type)
{
	std::shared_ptr<IObject> object = m_factory->CreateObject(i_type);
	if (object)
	{
		m_new_objects.push_back(object);
		return m_new_objects.back();
	}
	throw std::exception("Factory has not requested type");
}

void Controller::UpdateObjects(long i_elapsed_time)
{
  auto it_end = std::remove_if(m_objects.begin(), m_objects.end(), [](ObjectPtr i_object)
    {
    return i_object->ToDelete();
    });

  if (it_end != m_objects.end())
    m_objects.erase(it_end, m_objects.end());

	std::for_each(m_objects.begin(), m_objects.end(), [i_elapsed_time](const std::shared_ptr<IObject>& i_object)
		{
			i_object->Update(i_elapsed_time);
	  }); 

  while (!m_new_objects.empty())
    {
    m_objects.push_back(m_new_objects.back());
    m_new_objects.pop_back();
    }

  m_collision_manager.Update();
}

void Controller::RenderObjects()
{
	std::for_each(m_objects.begin(), m_objects.end(), [](const std::shared_ptr<IObject>& i_object)
		{
			i_object->Render();
	}); 
}

std::vector<ObjectPtr>& Controller::GetObjects()
  {
  return m_objects;
  }