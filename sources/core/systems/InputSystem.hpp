#pragma once
#include <list>
#include <SFML/Window/Event.hpp>

#include "core/SystemLocator.hpp"

class InputComponent;

class InputSystem final : public System<InputSystem>
{
public:
	enum class Type { Pressed, Released };

private:
	std::list<InputComponent*> components;

public:
	void subscribe(InputComponent* component);
	void unsubscribe(InputComponent* component);

	void keyPressed(const sf::Event::KeyEvent& keyEvent) const;
	void keyReleased(const sf::Event::KeyEvent& keyEvent) const;
};

#include "../components/InputComponent.hpp"
