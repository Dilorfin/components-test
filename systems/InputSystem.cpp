#include "InputSystem.hpp"

void InputSystem::add(InputComponent* component)
{
	components.push_back(component);
}

void InputSystem::remove(InputComponent* component)
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

void InputSystem::clear()
{
	components.clear();
}
