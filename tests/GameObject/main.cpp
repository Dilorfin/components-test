#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "core/GameObject.hpp"

#include "MockComponents.hpp"

TEST_CASE("addComponent")
{
	SUBCASE("adding component without params")
	{
		GameObject object;

		auto* testComponent = object.addComponent<TestComponent<0>>();

		CHECK_MESSAGE(testComponent != nullptr, "addComponent should return pointer to component");
	}

	SUBCASE("adding component with params")
	{
		constexpr int a = 42;
		constexpr double b = 7;
		GameObject object;

		auto* testParamsComponent = object.addComponent<TestParamsComponent>(a, b);

		CHECK_MESSAGE(testParamsComponent != nullptr, "addComponent should return pointer to component");
		CHECK_MESSAGE(testParamsComponent->a == a, "addComponent should pass params to constructing component");
		CHECK_MESSAGE(testParamsComponent->b == doctest::Approx(b).epsilon(0.01), "addComponent should pass params to constructing component");
	}

	SUBCASE("addComponent set gameObject")
	{
		GameObject object;

		const auto* testComponent = object.addComponent<TestComponent<0>>();

		CHECK_MESSAGE(testComponent->gameObject == &object, "addComponent should set pointer to gameObject");
	}
}

TEST_CASE("getComponent")
{
	SUBCASE("get component without adding")
	{
		GameObject object;

		auto* testComponent = object.getComponent<TestComponent<0>>();

		CHECK_MESSAGE(testComponent == nullptr, "getComponent should return nullptr if do not have such component");
	}

	SUBCASE("get component")
	{
		GameObject object;

		auto* onAddPtr = object.addComponent<TestComponent<0>>();
		auto* onGetPtr = object.getComponent<TestComponent<0>>();

		CHECK_MESSAGE(onGetPtr != nullptr, "getComponent should return pointer to component");
		CHECK_MESSAGE(onGetPtr == onAddPtr, "getComponent should return the same pointer as addComponent");
	}
}

TEST_CASE("components functions calls")
{
	SUBCASE("components start functions should be called")
	{
		GameObject object;
		const auto* component1 = object.addComponent<TestComponent<0>>();
		const auto* component2 = object.addComponent<TestComponent<1>>();

		CHECK_FALSE_MESSAGE(component1->started, "component1 should not be started");
		CHECK_FALSE_MESSAGE(component2->started, "component2 should not be started");

		object.start();

		CHECK_MESSAGE(component1->started, "component1 should be started");
		CHECK_MESSAGE(component2->started, "component2 should be started");
	}
	SUBCASE("components update functions should be called")
	{
		constexpr int64_t deltaTime = 1;

		GameObject object;
		const auto* component1 = object.addComponent<TestComponent<0>>();
		const auto* component2 = object.addComponent<TestComponent<1>>();

		CHECK_FALSE_MESSAGE(component1->updated, "component1 should not be updated");
		CHECK_FALSE_MESSAGE(component2->updated, "component2 should not be updated");

		object.update(deltaTime);

		CHECK_MESSAGE(component1->updated, "component1 should be updated");
		CHECK_MESSAGE(component2->updated, "component2 should be updated");
	}
}

TEST_CASE("remove destroyed components on update")
{
	constexpr int64_t deltaTime = 1;

	SUBCASE("component should be deleted on update")
	{
		GameObject object;
		auto* component = object.addComponent<TestComponent<0>>();

		component->destroy();

		component = object.getComponent<TestComponent<0>>();
		CHECK_MESSAGE(component != nullptr, "before update component still available");

		object.update(deltaTime);

		component = object.getComponent<TestComponent<0>>();
		CHECK_MESSAGE(component == nullptr, "after update getting component return nullptr");
	}

	SUBCASE("should not fail after deleting")
	{
		GameObject object;
		object.addComponent<TestComponent<0>>();
		object.addComponent<TestComponent<1>>();
		object.addComponent<TestComponent<2>>();
		object.addComponent<TestComponent<3>>();

		object.getComponent<TestComponent<0>>()->destroy();

		for (int i = 0; i <= 60; i++)
		{
			object.update(deltaTime);
		}
	}

	SUBCASE("should not fail after deleting multiple components")
	{
		GameObject object;
		object.addComponent<TestComponent<0>>();
		object.addComponent<TestComponent<1>>();
		object.addComponent<TestComponent<2>>();
		object.addComponent<TestComponent<3>>();
		object.addComponent<TestComponent<4>>();
		object.addComponent<TestComponent<5>>();
		object.addComponent<TestComponent<6>>();
		object.addComponent<TestComponent<7>>();

		object.getComponent<TestComponent<0>>()->destroy();
		object.getComponent<TestComponent<3>>()->destroy();
		object.getComponent<TestComponent<6>>()->destroy();

		for (int i = 0; i <= 60; i++)
		{
			object.update(deltaTime);
		}
	}
}
