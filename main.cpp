#include <iostream>

#include <SFML/Graphics.hpp>

#include "core/GameObjectManager.hpp"
#include "core/SystemLocator.hpp"
#include "objects/Player.hpp"
#include "systems/RenderSystem.hpp"

int main() try
{
	sf::RenderWindow window(sf::VideoMode(816, 624), "SFML test", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	auto systemLocator = SystemLocator::getInstance();
	auto* render = systemLocator->addSystem<RenderSystem>();
	auto* input = systemLocator->addSystem<InputSystem>();
	
	auto* objectsManager = systemLocator->addSystem<GameObjectsManager>();
	objectsManager->addObject(new Player(sf::Vector2f(100, 100)));

	sf::Clock frameClock;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				input->keyPressed(event.key);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				input->keyReleased(event.key);
			}
		}

		sf::Time frameTime = frameClock.restart();
		const auto deltaTime = static_cast<float>(frameTime.asMicroseconds());
		objectsManager->update(deltaTime);

		window.clear();
		render->render(window);
		window.display();
	}
	
	return 0;
}
catch (std::exception& exception)
{
	std::cerr << "An error has occurred: ";
	std::cerr << exception.what() << std::endl;
	system("pause");
	return -1;
}