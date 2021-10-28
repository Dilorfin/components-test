#pragma once
#include <functional>
#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../core/Component.hpp"
#include "../systems/InputSystem.hpp"

class InputComponent final : public Component<InputComponent>
{
private:
	std::map<sf::Keyboard::Key, std::function<void(InputSystem::Type)>> keyboardBindings;

public:
	InputComponent();

	~InputComponent() override;

	void bind(const sf::Keyboard::Key key, const std::function<void(InputSystem::Type)>& func);

	void keyPressed(const sf::Event::KeyEvent& keyEvent) const;
	void keyReleased(const sf::Event::KeyEvent& keyEvent) const;
};
