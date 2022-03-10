#include <iostream>

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "core/GameObjectManager.hpp"
#include "core/SystemLocator.hpp"

#include "systems/RenderSystem.hpp"

#include "objects/Player.hpp"
#include "objects/Dummy.hpp"

#include "physics/box2dSystem.hpp"
#include "physics/box2dDebugDrawSFML.hpp"

int main() try
{
	sf::RenderWindow window(sf::VideoMode(864, 724), "SFML test", sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	auto systemLocator = SystemLocator::getInstance();
	
	
	auto* input = systemLocator->addSystem<InputSystem>();
	auto* render = systemLocator->addSystem<RenderSystem>();
	auto* physics = systemLocator->addSystem<Box2dSystem>();
	auto* objectsManager = systemLocator->addSystem<GameObjectsManager>();

	objectsManager->addObject(new Player(sf::Vector2f(100, 100)));
	objectsManager->addObject(new Dummy(sf::Vector2f(300, 300)));
	
#ifdef _DEBUG
	DebugDraw draw(window);
	draw.AppendFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	physics->setDebugDraw(&draw);
#endif

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
		auto dt = frameClock.restart();
		physics->update(dt.asMicroseconds());
		
		objectsManager->update(dt.asMicroseconds());

		window.clear();
#ifdef _DEBUG
		physics->debugDraw();
#endif

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
