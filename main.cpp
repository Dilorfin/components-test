#include <iostream>

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "core/GameObjectSystem.hpp"
#include "core/SystemLocator.hpp"

#include "systems/RenderSystem.hpp"

#include "objects/Player.hpp"
#include "objects/Dummy.hpp"

#include "physics/PhysicsSystem.hpp"
#include "physics/PhysicsDebugDraw.hpp"

class TestScene final : Scene
{
public:
	TestScene()
	{
		SystemLocator::getSystem<GameObjectsManager>()->add(new Player(sf::Vector2f(100, 100)));
		SystemLocator::getSystem<GameObjectsManager>()->add(new Dummy(sf::Vector2f(300, 300)));
	}
};

int main() try
{
	sf::RenderWindow window(sf::VideoMode(864, 724), "SFML test", sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	SceneManager::getInstance()->addScene("test scene", [] {
		return reinterpret_cast<Scene*>(new TestScene);
		});
	SceneManager::getInstance()->loadScene(0);

#ifdef _DEBUG
	PhysicsDebugDraw draw(window);
	draw.AppendFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	SystemLocator::getSystem<PhysicsSystem>()->setDebugDraw(&draw);
#endif

	sf::Clock frameClock;
	while (window.isOpen())
	{
		SceneManager::getInstance()->switchScenes();

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

		SystemLocator::getSystem<GameObjectsManager>()->update(dt.asMicroseconds());

		window.clear();
#ifdef _DEBUG
		SystemLocator::getSystem<PhysicsSystem>()->debugDraw();
#endif

		SystemLocator::getSystem<RenderSystem>()->render(window);
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
