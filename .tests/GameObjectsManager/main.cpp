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
