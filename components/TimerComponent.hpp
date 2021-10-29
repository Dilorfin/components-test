#pragma once
#include <functional>

#include "../core/Component.hpp"

class TimerComponent final : public Component<TimerComponent>
{
private:
	std::function<void()> trigger;
	int64_t timer = 0;
	int64_t endTime = 0;
	bool looped = false;
	bool isRunning = true;

public:
	void update(const int64_t deltaTime) override
	{
		if(!isRunning) return;

		timer += deltaTime;
		if(timer >= endTime)
		{
			trigger();
			isRunning = false;
		}
	}

	void setLooped(const bool loop)
	{
		looped = loop;
	}

	void setEndTime(const int64_t time)
	{
		endTime = time;
	}
	void setTrigger(const std::function<void()>& func)
	{
		trigger = func;
	}
};
