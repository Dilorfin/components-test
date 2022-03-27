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

class TestFunc1Component final : public Component<TestFunc1Component>
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
class TestFunc2Component final : public Component<TestFunc2Component>
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
