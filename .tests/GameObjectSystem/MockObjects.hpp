#pragma once

class TestComponent final : public Component<TestComponent>
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

class TestStartObject : public GameObject
{
private:

	TestComponent* component = nullptr;
	
public:

	TestStartObject()
	{
		component = this->addComponent<TestComponent>();
	}
	
	bool isStarted() const
	{
		return this->component->started;
	}
};
