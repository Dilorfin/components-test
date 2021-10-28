#include "InputSystem.hpp"

InputSystem* InputSystem::getInstance()
{
	if (instance == nullptr)
	{
		instance = new InputSystem();
	}
	return instance;
}

void InputSystem::subscribe(InputComponent* component)
{
	components.push_back(component);
}

void InputSystem::unsubscribe(InputComponent* component)
{
	std::erase(components, component);
}

void InputSystem::keyPressed(const sf::Event::KeyEvent& keyEvent) const
{
	for (const auto* component : components)
	{
		component->keyPressed(keyEvent);
	}
}

void InputSystem::keyReleased(const sf::Event::KeyEvent& keyEvent) const
{
	for (const auto* component : components)
	{
		component->keyReleased(keyEvent);
	}
}
