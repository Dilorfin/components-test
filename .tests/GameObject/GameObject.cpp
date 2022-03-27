#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../../core/GameObject.hpp"

#include "MockComponents.hpp"

TEST_CASE("addComponent")
{
	SUBCASE("addComponent wo params")
	{
		GameObject object;

		auto* testComponent = object.addComponent<TestComponent>();

		CHECK_MESSAGE(testComponent != nullptr, "addComponent should return pointer to component");
	}

	SUBCASE("addComponent with params")
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

		const auto* testComponent = object.addComponent<TestComponent>();

		CHECK_MESSAGE(testComponent->gameObject == &object, "addComponent should set pointer to gameObject");
	}
}

TEST_CASE("getComponent")
{
	SUBCASE("getComponent wo adding")
	{
		GameObject object;

		auto* testComponent = object.getComponent<TestComponent>();

		CHECK_MESSAGE(testComponent == nullptr, "getComponent should return nullptr if do not have such component");
	}

	SUBCASE("getComponent")
	{
		GameObject object;

		auto* onAddPtr = object.addComponent<TestComponent>();
		auto* onGetPtr = object.getComponent<TestComponent>();

		CHECK_MESSAGE(onGetPtr != nullptr, "getComponent should return pointer to component");
		CHECK_MESSAGE(onGetPtr == onAddPtr, "getComponent should return the same pointer as addComponent");
	}
}

TEST_CASE("components functions calls")
{
	SUBCASE("components start functions should be called")
	{
		GameObject object;
		object.addComponent<TestComponent>();
		const auto* component1 = object.addComponent<TestFuncComponent<0>>();
		const auto* component2 = object.addComponent<TestFuncComponent<1>>();

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
		object.addComponent<TestComponent>();
		const auto* component1 = object.addComponent<TestFuncComponent<0>>();
		const auto* component2 = object.addComponent<TestFuncComponent<1>>();

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

	GameObject object;
	object.addComponent<TestComponent>();
	object.addComponent<TestFuncComponent<1>>();
	auto* addComp = object.addComponent<TestFuncComponent<0>>();

	addComp->destroy();
	object.update(deltaTime);

	BaseComponent* getComp = object.getComponent<TestFuncComponent<0>>();
	CHECK(getComp == nullptr);
	
	for (int i = 0; i <= 60; i++)
	{
		object.update(deltaTime);
	}
	
	object.getComponent<TestComponent>()->destroy();
	object.getComponent<TestFuncComponent<1>>()->destroy();
	
	object.update(deltaTime);
	
	getComp = object.getComponent<TestComponent>();
	CHECK(getComp == nullptr);
	getComp = object.getComponent<TestFuncComponent<1>>();
	CHECK(getComp == nullptr);
}
