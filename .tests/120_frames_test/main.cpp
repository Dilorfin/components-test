#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <SFML/Graphics.hpp>

#include "../../core/GameObjectSystem.hpp"
#include "../../core/SystemLocator.hpp"

#include "../../systems/RenderSystem.hpp"

#include "../../objects/Player.hpp"
#include "../../objects/Dummy.hpp"

#include "../../physics/PhysicsSystem.hpp"

class TestScene final : Scene
{
public:
	TestScene()
	{
		SystemLocator::getSystem<GameObjectsManager>()->add(new Player(sf::Vector2f(100, 100)));
		SystemLocator::getSystem<GameObjectsManager>()->add(new Dummy(sf::Vector2f(300, 300)));
	}
};

TEST_CASE("not fail on 120 frames") {
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

	int iterations = 120;

	sf::Clock frameClock;
	while (iterations--)
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

		SystemLocator::getSystem<GameObjectsManager>()->update(dt.asMicroseconds());

		window.clear();
		if(iterations>15)
		{
			throw "AAAA";
		}
#ifdef _DEBUG
		SystemLocator::getSystem<PhysicsSystem>()->debugDraw();
#endif

		SystemLocator::getSystem<RenderSystem>()->render();
		window.display();
	}
}