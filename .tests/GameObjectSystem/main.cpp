#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../../core/GameObjectSystem.hpp"

#include "MockObjects.hpp"

TEST_CASE("adding object")
{
	SUBCASE("object id should be unique")
	{
		GameObjectSystem manager;
		auto* obj1 = new GameObject;
		auto* obj2 = new GameObject;
		manager.add(obj1);
		manager.add(obj2);

		CHECK(obj1->getId() != obj2->getId());
	}

	SUBCASE("object should be started on add")
	{
		GameObjectSystem manager;
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
		const GameObjectSystem manager;

		const GameObject* obj = manager.getObjectById(0);

		CHECK(obj == nullptr);
	}

	SUBCASE("object should be found by id")
	{
		GameObject* obj = new GameObject;

		GameObjectSystem manager;
		manager.add(new GameObject);
		manager.add(obj);

		const auto objId = obj->getId();

		obj = manager.getObjectById(objId);

		CHECK(obj != nullptr);
		CHECK(obj->getId() == objId);
	}
}

TEST_CASE("removing destroyed objects")
{
	constexpr int64_t deltaTime = 1;

	SUBCASE("object should be deleted on update")
	{
		GameObjectSystem manager;
		GameObject* obj = new GameObject;
		manager.add(obj);

		const auto objId = obj->getId();

		obj->destroy();

		obj = manager.getObjectById(objId);
		CHECK(obj != nullptr);

		manager.update(deltaTime);

		obj = manager.getObjectById(objId);
		CHECK(obj == nullptr);
	}

	SUBCASE("should not fail after deleting")
	{
		GameObjectSystem manager;
		manager.add(new GameObject);
		manager.add(new GameObject);
		manager.add(new GameObject);

		GameObject* obj = new GameObject;
		manager.add(obj);

		manager.add(new GameObject);
		manager.add(new GameObject);
		manager.add(new GameObject);

		obj->destroy();

		for (int i = 0; i <= 60; i++)
		{
			manager.update(deltaTime);
		}
	}

	SUBCASE("should not fail after deleting multiple objects")
	{
		GameObject* obj = nullptr;
		GameObjectSystem manager;

		manager.add(new GameObject);
		manager.add(new GameObject);
		manager.add(new GameObject);

		obj = new GameObject;
		manager.add(obj);
		obj->destroy();

		manager.add(new GameObject);
		manager.add(new GameObject);
		manager.add(new GameObject);

		obj = new GameObject;
		manager.add(obj);
		obj->destroy();

		manager.add(new GameObject);
		manager.add(new GameObject);
		manager.add(new GameObject);

		for (int i = 0; i <= 60; i++)
		{
			manager.update(deltaTime);
		}
	}
}
