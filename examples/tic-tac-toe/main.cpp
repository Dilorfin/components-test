#include <iostream>

#include <SFML/Graphics.hpp>

#include "core/SceneManager.hpp"
#include "core/SystemLocator.hpp"

#include "core/systems/GameObjectSystem.hpp"
#include "core/systems/RenderSystem.hpp"
#include "core/systems/InputSystem.hpp"

#include "scenes/GameScene.hpp"

int main() try
{
	sf::RenderWindow window(sf::VideoMode({300, 400}), "TicTacToe", sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	SystemLocator::getSystem<RenderSystem>()->setRenderTarget(&window);

	SceneManager::getInstance()->addScene("GameScene", [] {
		return reinterpret_cast<Scene*>(new GameScene);
	});
	SceneManager::getInstance()->loadScene(0);

	sf::Clock frameClock;
	while (window.isOpen())
	{
		SceneManager::getInstance()->update();

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				SystemLocator::getSystem<InputSystem>()->keyPressed(event.key);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				SystemLocator::getSystem<InputSystem>()->keyReleased(event.key);
			}
		}
		auto dt = frameClock.restart();

		SystemLocator::getSystem<GameObjectSystem>()->update(dt.asMicroseconds());

		window.clear();

		SystemLocator::getSystem<RenderSystem>()->render();
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
