#pragma once
#include <list>

#include <SFML/Window/Event.hpp>

class InputComponent;

class InputSystem final
{
public:
	enum class Type { Pressed, Released };

private:
	inline static InputSystem* instance = nullptr;

	InputSystem() = default;

	std::list<InputComponent*> components;

public:
	static InputSystem* getInstance();

	void subscribe(InputComponent* component);
	void unsubscribe(InputComponent* component);

	void keyPressed(const sf::Event::KeyEvent& keyEvent) const;
	void keyReleased(const sf::Event::KeyEvent& keyEvent) const;
};

#include "../components/InputComponent.hpp"
