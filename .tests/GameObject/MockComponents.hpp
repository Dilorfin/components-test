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

class Counting
{
public:
	inline static int count = 0;
	Counting()
	{
		count++;
	}
	virtual ~Counting()
	{
		count--;
	}
};

template<int n>
class TestCountingComponent final : public Component<TestCountingComponent<n>>
{};

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
