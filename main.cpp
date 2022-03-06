#include <iostream>

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "core/GameObjectManager.hpp"
#include "core/SystemLocator.hpp"
#include "objects/Player.hpp"
#include "systems/RenderSystem.hpp"

#include <optional>

#include "physics/box2dSystem.hpp"
#include "physics/box2dDebugDrawSFML.hpp"
#include "physics/BoxPhysicsComponent.hpp"
#include "physics/CirclePhysicsComponent.hpp"

class RectangleRender : public RenderComponent<RectangleRender>
{
private:
	TransformComponent* transform = nullptr;

	sf::RectangleShape rect;
	sf::Vector2f size;
public:
	RectangleRender(sf::Vector2f size)
		: size(size)
	{
		rect.setSize(size);
		rect.setOrigin(size.x/2.f, size.y/2.f);
	}

	void start() override
	{
		transform = gameObject->getComponent<TransformComponent>();
	}
	void update(const int64_t deltaTime) override
	{
		constexpr float pi = 3.1415926535f;
		rect.setPosition(transform->position+sf::Vector2f(size.x/2, size.y/2));
		rect.setRotation(180.f*transform->rotation/pi);
		std::cout << transform->rotation << std::endl;
	}
	void render(sf::RenderTarget& renderTarget) override
	{
		renderTarget.draw(rect);
	}
};

class Box final : public GameObject
{
public:
	Box()
	{
		this->addComponent<TransformComponent>();
		this->addComponent<BoxPhysicsComponent>(sf::Vector2f{32, 32}, sf::Vector2f{400.f, 300.f}, b2_dynamicBody);
		this->addComponent<RectangleRender>(sf::Vector2f{32.f, 32.f});
		//this->addComponent<CirclePhysicsComponent>(32.f, {420.f, 200.f}, b2_dynamicBody);
		/*
		 * comp1.setBeginContactTrigger([](B2Component* comp) {
		//comp->
		std::cout << "begin contact" << std::endl;
	});
		 */
	}
};

class Ground final : public GameObject
{
public:
	Ground()
	{
		this->addComponent<TransformComponent>();
		this->addComponent<BoxPhysicsComponent>(sf::Vector2f{800, 64}, sf::Vector2f{0, 500.f}, b2_staticBody);
		this->addComponent<RectangleRender>(sf::Vector2f{800.f, 64.f});
		/*
		 * comp1.setBeginContactTrigger([](B2Component* comp) {
		//comp->
		std::cout << "begin contact" << std::endl;
	});
		 */
	}
};

class CircleRender : public RenderComponent<CircleRender>
{
private:
	TransformComponent* transform = nullptr;

	sf::CircleShape circle;
public:
	CircleRender()
		: circle(32)
	{}

	void start() override
	{
		transform = gameObject->getComponent<TransformComponent>();
	}
	void update(const int64_t deltaTime) override
	{
		circle.setPosition(transform->position);
	}
	void render(sf::RenderTarget& renderTarget) override
	{
		renderTarget.draw(circle);
	}
};

class Circle final : public GameObject
{
public:
	Circle()
	{
		this->addComponent<TransformComponent>();
		const auto* physics = this->addComponent<CirclePhysicsComponent>(32.f, sf::Vector2f{420.f, 200.f}, b2_dynamicBody);
		physics->applyLinearImpulseToCenter({-4, 15});
		this->addComponent<CircleRender>();
		/*
		 * comp1.setBeginContactTrigger([](B2Component* comp) {
		//comp->
		std::cout << "begin contact" << std::endl;
	});
		 */
	}
};

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
	
	/*objectsManager->addObject(new Box);
	objectsManager->addObject(new Circle);
	objectsManager->addObject(new Ground);*/
	
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
