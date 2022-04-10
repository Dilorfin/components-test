#pragma once

#include "core/Component.hpp"

template<int N>
class TestComponent final : public Component<TestComponent<N>>
{
public:
	using BaseComponent::gameObject;

	bool started = false;
	void start() override
	{
		started = true;
	}

	bool updated = false;
	void update(const int64_t deltaTime) override
	{
		updated = true;
	}
};

class TestParamsComponent final : public Component<TestParamsComponent>
{
public:
	TestParamsComponent(int a, double b)
		: a(a), b(b)
	{}

	int a;
	double b;
};
