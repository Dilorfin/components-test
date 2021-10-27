#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "components/AnimatedSpriteComponent.hpp"
#include "core/GameObject.hpp"

#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "systems/RenderSystem.hpp"

class Test final : public GameObject
{
public:
	Test()
	{
		this->addComponent<TransformComponent>();
		//this->addComponent<SpriteComponent>("./assets/Book.png");
		auto* animation = this->addComponent<AnimatedSpriteComponent>("./assets/hurray.png");
		animation->addFrame(sf::IntRect(0, 0, 64, 64));
		animation->addFrame(sf::IntRect(64, 0, 64, 64));
		animation->addFrame(sf::IntRect(128, 0, 64, 64));
		
	}
};

class GameObjectsManager
{
private:
	std::vector<GameObject*> objects;

public:
	~GameObjectsManager()
	{
		for (const auto* obj : objects)
		{
			delete obj;
		}
	}

	void addObject(GameObject* object)
	{
		objects.push_back(object);
	}

	void removeObject(GameObject* object)
	{
		std::erase(objects, object);
	}

	void start() const
	{
		for (const auto* obj : objects)
		{
			obj->start();
		}
	}

	void update(const float deltaTime) const
	{
		for (auto* obj : objects)
		{
			obj->update(deltaTime);
		}
	}
};

int main(int argc, char* argv[]) try
{
	sf::RenderWindow window(sf::VideoMode(816, 624), "SFML test", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	GameObjectsManager objectsManager;
	objectsManager.addObject(new Test);

	objectsManager.start();

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
		objectsManager.update(frameTime.asMicroseconds());
		
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