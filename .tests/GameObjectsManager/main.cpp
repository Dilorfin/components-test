#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../../core/GameObjectSystem.hpp"

#include "MockObjects.hpp"

TEST_CASE("adding object")
{
	SUBCASE("object id should be unique")
	{
		GameObjectsManager manager;
		auto* obj1 = new GameObject;
		auto* obj2 = new GameObject;
		manager.add(obj1);
		manager.add(obj2);

		CHECK(obj1->getId() != obj2->getId());
	}

	SUBCASE("object should be started on add")
	{
		GameObjectsManager manager;
		auto* obj = new TestStartObject;

		CHECK_FALSE(obj->isStarted());

		manager.add(obj);

		CHECK(obj->isStarted());
	}
}

TEST_CASE("get object by id")
{
	SUBCASE("object not found")
	{
		const GameObjectsManager manager;

		const GameObject* obj = manager.getObjectById(0);

		CHECK(obj == nullptr);
	}

	SUBCASE("object should be found by id")
	{
		GameObject* obj = new GameObject;

		GameObjectsManager manager;
		manager.add(new GameObject);
		manager.add(obj);

		const auto objId = obj->getId();

		obj = manager.getObjectById(objId);

		CHECK(obj != nullptr);
		CHECK(obj->getId() == objId);
	}
}
