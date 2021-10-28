#include <iostream>

#include <SFML/Graphics.hpp>

#include "core/GameObjectManager.hpp"

#include "objects/Player.hpp"

#include "systems/RenderSystem.hpp"

int main() try
{
	sf::RenderWindow window(sf::VideoMode(816, 624), "SFML test", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	auto* objectsManager = GameObjectsManager::getInstance();
	objectsManager->addObject(new Player(sf::Vector2f(100, 100)));

	auto* render = RenderSystem::getInstance();
	sf::Clock frameClock;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time frameTime = frameClock.restart();
		const float deltaTime = static_cast<float>(frameTime.asMicroseconds()) / 800.f;
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