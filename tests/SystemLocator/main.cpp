#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "core/System.hpp"
#include "core/SystemLocator.hpp"

class TestSystem final : public System<TestSystem>
{};

TEST_CASE("getting system")
{
	SUBCASE("system created on get")
	{
		auto* system = SystemLocator::getSystem<TestSystem>();

		CHECK_MESSAGE(system != nullptr, "system created on get");
	}

	SUBCASE("the same pointer")
	{
		auto* first = SystemLocator::getSystem<TestSystem>();
		auto* second = SystemLocator::getSystem<TestSystem>();

		CHECK_MESSAGE(first == second, "getting one system should return the same ptr");
	}
}
