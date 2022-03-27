#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../core/Component.hpp"
#include "../physics/PhysicsComponent.hpp"

class PhysicsChildComponent : public PhysicsComponent
{};

class TestComponent final : public Component<TestComponent>
{};

TEST_CASE("testing the hash function")
{
	SUBCASE("default hash should be equal to typeid::hash_code call")
	{
		CHECK(hash<TestComponent>() == typeid(TestComponent).hash_code());
	}
	SUBCASE("hash of PhysicsComponent should be equal to 0")
	{
		CHECK(hash<PhysicsComponent>() == 0);
	}
	SUBCASE("hash of PhysicsComponent children should be equal to 0")
	{
		CHECK(hash<PhysicsChildComponent>() == 0);
	}
	SUBCASE("hash of instance should be equal to hash<T> function call")
	{
		CHECK(hash<TestComponent>() == TestComponent().hash_code());
	}
}
