#include "InputSystem.hpp"

void InputSystem::subscribe(InputComponent* component)
{
	components.push_back(component);
}

void InputSystem::unsubscribe(InputComponent* component)
{
	components.erase(std::remove(std::begin(components), std::end(components), component), std::end(components));
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
