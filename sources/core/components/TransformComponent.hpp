#pragma once

#include <SFML/System.hpp>

#include "core/Component.hpp"

class TransformComponent final : public Component<TransformComponent>
{
public:
	sf::Vector2f position;
	float rotation{};
};
