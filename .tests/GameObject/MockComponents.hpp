#pragma once

#include "../../core/Component.hpp"

class TestComponent final : public Component<TestComponent>
{
public:
	using BaseComponent::gameObject;
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

template<int N>
class TestFuncComponent final : public Component<TestFuncComponent<N>>
{
public:
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
