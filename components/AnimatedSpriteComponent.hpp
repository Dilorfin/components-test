#pragma once
#include "RenderComponent.hpp"
#include "TransformComponent.hpp"
#include "../core/GameObject.hpp"

#include "../animation/AnimatedSprite.hpp"

class AnimatedSpriteComponent final : public RenderComponent<AnimatedSpriteComponent>
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

		sprite.setPosition(transform->position);
		sprite.setRotation(sf::degrees(transform->rotation));
	}

	void update(const int64_t deltaTime) override
	{
		sprite.update(deltaTime);
		sprite.setOrigin({sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f});
		sprite.setPosition(transform->position);
		sprite.setRotation(sf::degrees(transform->rotation));
	}

	void addFrame(const sf::Vector2i& frame)
	{
		sprite.addFrame(frame);
	}

	void setFrameSize(const sf::Vector2i& frameSize)
	{
		sprite.setFrameSize(frameSize);
	}

	void render(sf::RenderTarget& renderTarget) override
	{
		renderTarget.draw(sprite);
	}
};
