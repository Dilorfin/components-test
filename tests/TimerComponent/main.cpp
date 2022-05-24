#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "core/components/TimerComponent.hpp"

class TestClass
{
public:
	int count = 0;

	void function() { count++; }
};

TEST_CASE("testing timer component")
{
	SUBCASE("triger once")
	{
		TestClass test;
		TimerComponent component;

		component.setTrigger([&] { test.function(); });
		component.update(0);

		CHECK_MESSAGE(test.count == 1, "function should be called once");
	}

	SUBCASE("triger after time")
	{
		TestClass test;
		TimerComponent component;

		component.setEndTime(5);
		component.setTrigger([&] { test.function(); });

		for (int i = 0; i < 5; i++)
		{
			CHECK_MESSAGE(test.count == 0, "function should not be called");
			component.update(1);
		}

		CHECK_MESSAGE(test.count == 1, "function should be called once");
	}

	SUBCASE("several times out of time")
	{
		TestClass test;
		TimerComponent component;

		component.setEndTime(5);
		component.setTrigger([&] {test.function(); });

		for (int i = 0; i < 15; i++)
		{
			component.update(1);
		}

		CHECK_MESSAGE(test.count == 1, "function should be called once");
	}

	SUBCASE("several times triger looped")
	{
		TestClass test;
		TimerComponent component;

		component.setLooped(true);
		component.setEndTime(5);
		component.setTrigger([&] {test.function(); });

		for (int i = 0; i < 15; i++)
		{
			component.update(1);
		}

		CHECK_MESSAGE(test.count == 3, "function should be called 3 times");
	}

	SUBCASE("several times triger looped")
	{
		TestClass test;
		TimerComponent component;

		component.setLooped(true);
		component.setEndTime(5);
		component.setTrigger([&] { test.function(); });

		component.update(6);
		component.update(6);

		CHECK_MESSAGE(test.count == 2, "function should be called twice");

		component.setLooped(false);
		component.update(6);

		CHECK_MESSAGE(test.count == 3, "function should be called once more");

		component.update(6);
		CHECK_MESSAGE(test.count == 3, "function should not be called");
	}

	SUBCASE("restart timer")
	{
		TestClass test;
		TimerComponent component;

		component.setEndTime(5);
		component.setTrigger([&] { test.function(); });

		component.update(6);

		component.restart();

		component.update(6);

		CHECK_MESSAGE(test.count == 2, "function should be called twice");
	}
}
