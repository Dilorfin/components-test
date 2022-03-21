#pragma once
#ifdef _DEBUG
#include <SFML/Graphics.hpp>

// https://stackoverflow.com/a/4528055/8885358
class PhysicsDebugDraw final : public b2Draw
{
private:
	sf::RenderTarget*const renderTarget;
public:
	explicit PhysicsDebugDraw(sf::RenderTarget* const renderTarget)
		: renderTarget(renderTarget)
	{}

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		sf::VertexArray lines(sf::LineStrip, vertexCount+1);
		for (int i = 0; i < vertexCount; ++i)
		{
			lines[i].position = PhysicsSystem::metersToPixels(vertices[i]);
			lines[i].color = convert(color);
		}
		lines[vertexCount].position = PhysicsSystem::metersToPixels(vertices[0]);
		lines[vertexCount].color = convert(color);
		renderTarget->draw(lines);
	}
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		sf::VertexArray lines(sf::TriangleStrip, vertexCount+1);
		for (int i = 0; i < vertexCount; ++i)
		{
			lines[i].position = PhysicsSystem::metersToPixels(vertices[i]);
			lines[i].color = convert(color);
		}
		lines[vertexCount].position = PhysicsSystem::metersToPixels(vertices[0]);
		lines[vertexCount].color = convert(color);
		renderTarget->draw(lines);
	}
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override
	{
		const float r = PhysicsSystem::metersToPixels(radius);
		sf::CircleShape circle(r);
		circle.setOrigin({r, r});
		circle.setPosition(PhysicsSystem::metersToPixels(center));
		circle.setOutlineThickness(2);
		circle.setOutlineColor(convert(color));
		renderTarget->draw(circle);
	}
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override
	{
		const float r = PhysicsSystem::metersToPixels(radius);
		sf::CircleShape circle(r);
		circle.setOrigin({r, r});
		circle.setPosition(PhysicsSystem::metersToPixels(center));
		circle.setFillColor(convert(color));
		renderTarget->draw(circle);
	}
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override
	{
		sf::VertexArray lines(sf::Lines, 2);
		lines[0].position = PhysicsSystem::metersToPixels(p1);
		lines[0].color = convert(color);
		lines[1].position = PhysicsSystem::metersToPixels(p2);
		lines[1].color = convert(color);
		renderTarget->draw(lines);
	}

	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override
	{
		const float r = PhysicsSystem::metersToPixels(size);
		sf::CircleShape circle(r);
		circle.setOrigin({PhysicsSystem::metersToPixels(r/2), PhysicsSystem::metersToPixels(r/2)});
		circle.setPosition(PhysicsSystem::metersToPixels(p));
		circle.setFillColor(convert(color));
		renderTarget->draw(circle);
	}

	void DrawTransform(const b2Transform& xf) override
	{}

private:
	
	static sf::Color convert(const b2Color& color)
	{
		auto c = [](const float v)->sf::Uint8 {
			return static_cast<sf::Uint8>(std::floor(v >= 1.0f ? 255 : v * 256.0f));
		};
		return {
			c(color.r),
			c(color.g),
			c(color.b),
			c(color.a)
		};
	}
};

#endif
