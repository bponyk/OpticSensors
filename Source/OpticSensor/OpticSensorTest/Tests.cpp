#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <OpticSensorLib\Controller.h>
#include <OpticSensorLib\IObject.h>
#include <OpticSensorLib\IObjectFactory.h>

class MockObject : public IObject
{
public:
	MOCK_METHOD1(Update, void(long));
	MOCK_METHOD0(Render, void());
	MOCK_CONST_METHOD0(GetBBox, Box3D());
};

class TestObjectFactory : public IObjectFactory
{
	public:
		virtual std::shared_ptr<IObject> CreateObject(ObjectType i_type) override
		{
			return std::make_shared<MockObject>();
		}
};

TEST(Controller, AddObject_ReturnsIObjectRef)
{
	Controller controller;
	controller.SetObjectFactory(std::make_shared<TestObjectFactory>());

	ASSERT_NO_THROW(controller.AddObject((ObjectType)255));
}

TEST(Controller, AddObject_ThrowsIfNoFactoryForObject)
{
	Controller controller;

	ASSERT_THROW(controller.AddObject((ObjectType)255), std::exception);
}

TEST(Controller, UpdateObjects)
{
	Controller controller;
	controller.SetObjectFactory(std::make_shared<TestObjectFactory>());
	MockObject* object = static_cast<MockObject*>(controller.AddObject((ObjectType)255).get());
	EXPECT_CALL(*object, Update(0))
		.Times(1);

	controller.UpdateObjects(0);
}

TEST(Controller, RenderObjects)
{
	Controller controller;
	controller.SetObjectFactory(std::make_shared<TestObjectFactory>());
	MockObject* object = static_cast<MockObject*>(controller.AddObject((ObjectType)255).get());
	EXPECT_CALL(*object, Render())
		.Times(1);

	controller.RenderObjects();
}