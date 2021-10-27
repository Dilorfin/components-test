#pragma once
#include "RenderComponent.hpp"
#include "TransformComponent.hpp"
#include "../core/GameObject.hpp"

#include "../sfml_extentions/Animation/AnimatedSprite.hpp"

class AnimatedSpriteComponent final : public Component<AnimatedSpriteComponent>, public RenderComponent
{
private:
	AnimatedSprite sprite;

	TransformComponent* transform = nullptr;

public:
	explicit AnimatedSpriteComponent(const std::string& fileName)
	{
		if (!sprite.loadFromFile(fileName))
		{
			// error...
		}
	}
	
	void start() override
	{
		transform = gameObject->getComponent<TransformComponent>();
	}

	void update(const float deltaTime) override
	{
		sprite.update(deltaTime);
		sprite.setPosition(transform->position);
		sprite.setRotation(transform->rotation);
	}

	void addFrame(const sf::IntRect& frame)
	{
		sprite.addFrame(frame);
	}

	void render(sf::RenderTarget& renderTarget) override
	{
		renderTarget.draw(sprite);
	}
};
