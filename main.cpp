#include <iostream>

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "core/GameObjectSystem.hpp"
#include "core/SystemLocator.hpp"

#include "systems/RenderSystem.hpp"

#include "objects/Player.hpp"
#include "objects/Dummy.hpp"

#include "physics/PhysicsSystem.hpp"

class TestScene final : Scene
{
public:
	TestScene()
	{
		SystemLocator::getSystem<GameObjectSystem>()->add(new Player(sf::Vector2f(100, 100)));
		SystemLocator::getSystem<GameObjectSystem>()->add(new Dummy(sf::Vector2f(300, 300)));
	}
};

int main() try
{
	sf::RenderWindow window(sf::VideoMode(864, 724), "SFML test", sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	SystemLocator::getSystem<RenderSystem>()->setRenderTarget(&window);

	SceneManager::getInstance()->addScene("test scene", [] {
		return reinterpret_cast<Scene*>(new TestScene);
		});
	SceneManager::getInstance()->loadScene(0);

#ifdef _DEBUG
	SystemLocator::getSystem<PhysicsSystem>()->enableDebugDraw();
#endif

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
		SystemLocator::getSystem<PhysicsSystem>()->update(dt.asMicroseconds());

		SystemLocator::getSystem<GameObjectSystem>()->update(dt.asMicroseconds());

		window.clear();

#ifdef _DEBUG
		SystemLocator::getSystem<PhysicsSystem>()->debugDraw();
#endif

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
