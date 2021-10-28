#include "InputComponent.hpp"

InputComponent::InputComponent()
{
	InputSystem::getInstance()->subscribe(this);
}

InputComponent::~InputComponent()
{
	InputSystem::getInstance()->unsubscribe(this);
}

void InputComponent::bind(const sf::Keyboard::Key key, const std::function<void(InputSystem::Type)>& func)
{
	keyboardBindings[key] = func;
}

void InputComponent::keyPressed(const sf::Event::KeyEvent& keyEvent) const
{
	if (keyboardBindings.contains(keyEvent.code))
	{
		keyboardBindings.at(keyEvent.code)(InputSystem::Type::Pressed);
	}
}

void InputComponent::keyReleased(const sf::Event::KeyEvent& keyEvent) const
{
	if (keyboardBindings.contains(keyEvent.code))
	{
		keyboardBindings.at(keyEvent.code)(InputSystem::Type::Released);
	}
}
