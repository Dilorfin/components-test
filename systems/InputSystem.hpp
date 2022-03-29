#pragma once
#include <list>
#include <SFML/Window/Event.hpp>

#include "../core/SystemLocator.hpp"

class InputComponent;

class InputSystem final : public System<InputSystem, InputComponent>
{
public:
	enum class Type { Pressed, Released };

private:
	std::list<InputComponent*> components;

public:
	void add(InputComponent* component) override;
	void remove(InputComponent* component) override;

	void keyPressed(const sf::Event::KeyEvent& keyEvent) const;
	void keyReleased(const sf::Event::KeyEvent& keyEvent) const;

	void clear() override;
};

#include "../components/InputComponent.hpp"
