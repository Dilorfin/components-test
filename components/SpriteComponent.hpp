#pragma once
#include <SFML/Graphics.hpp>

#include "../core/GameObject.hpp"
#include "../core/Component.hpp"

#include "RenderComponent.hpp"
#include "TransformComponent.hpp"

class SpriteComponent final : public Component<SpriteComponent>, public RenderComponent
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	TransformComponent* transform = nullptr;

public:
	SpriteComponent(const std::string& fileName)
	{
		if (!texture.loadFromFile(fileName))
		{
			// error...
		}
		sprite.setTexture(texture);
		
		sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	}

	SpriteComponent(const std::string& fileName, const sf::IntRect& rect)
	{
		if (!texture.loadFromFile(fileName, rect))
		{
			// error...
		}
		sprite.setTexture(texture);
	}
	
	void start() override;
	void update(int64_t deltaTime) override;

	void render(sf::RenderTarget& renderTarget) override;
};
