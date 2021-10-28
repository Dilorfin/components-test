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
	explicit SpriteComponent(const std::string& fileName);

	SpriteComponent(const std::string& fileName, const sf::IntRect& rect);

	void setSize(const float x, const float y);
	void setSize(const sf::Vector2f& size);

	void start() override;
	void update(int64_t deltaTime) override;

	void render(sf::RenderTarget& renderTarget) override;
};
