#include "stdafx.h"

#include "Controller.h"
#include "IObject.h"
#include "IObjectFactory.h"

#include <algorithm> 
#include <exception>

namespace
{
	class DefaultObjectFactory : public IObjectFactory
	{
		virtual std::unique_ptr<IObject> CreateObject(ObjectType i_type) override
		{
			std::unique_ptr<IObject> object;
			switch(i_type)
			{
			default:
				return nullptr;
			};
			return std::move(object);
		}
	};

	void CallObjectUpdate(const std::unique_ptr<IObject>& object)
	{
		object->Update();
	}

	void CallObjectRender(const std::unique_ptr<IObject>& object)
	{
		object->Render();
	}
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

IObject& Controller::AddObject(ObjectType i_type)
{
	std::unique_ptr<IObject> object = m_factory->CreateObject(i_type);
	if (object)
	{
		m_objects.push_back(std::move(object));
		return *m_objects.back().get();
	}
	throw std::exception("Factory has not requested type");
}

void Controller::UpdateObjects()
{
	std::for_each(m_objects.begin(), m_objects.end(), [](const std::unique_ptr<IObject>& i_object)
		{
			i_object->Update();
	}); 
}

void Controller::RenderObjects()
{
	std::for_each(m_objects.begin(), m_objects.end(), [](const std::unique_ptr<IObject>& i_object)
		{
			i_object->Render();
	}); 
}

