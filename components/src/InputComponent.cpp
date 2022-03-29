#include "../InputComponent.hpp"

InputComponent::InputComponent()
{
	SystemLocator::getSystem<InputSystem>()->add(this);
}

InputComponent::~InputComponent()
{
	SystemLocator::getSystem<InputSystem>()->remove(this);
}

void InputComponent::bind(const sf::Keyboard::Key key, const std::function<void(InputSystem::Type)>& func)
{
	keyboardBindings[key] = func;
}

void InputComponent::keyPressed(const sf::Event::KeyEvent& keyEvent) const
{
	if (keyboardBindings.count(keyEvent.code))
	{
		keyboardBindings.at(keyEvent.code)(InputSystem::Type::Pressed);
	}
}

void InputComponent::keyReleased(const sf::Event::KeyEvent& keyEvent) const
{
	if (keyboardBindings.count(keyEvent.code))
	{
		keyboardBindings.at(keyEvent.code)(InputSystem::Type::Released);
	}
}
