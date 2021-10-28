#pragma once
#include <functional>

#include "../core/Component.hpp"

class InputComponent final : public Component<InputComponent>
{
private:
	std::map<sf::Keyboard::Key, std::function<void()>> keyboardBindings;

public:
	void bind(const sf::Keyboard::Key key, const std::function<void()>& func)
	{
		keyboardBindings[key] = func;
	}

	void update(const float deltaTime) override
	{
		for (const auto& [key, function] : keyboardBindings)
		{
			if(sf::Keyboard::isKeyPressed(key))
			{
				function();
			}
		}
	}
};