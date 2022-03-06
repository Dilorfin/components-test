#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

class Animation final
{
private:
	sf::Vector2i frameSize;
	std::vector<sf::Vector2i> frames;
	
	sf::Sprite &sprite;

	bool looped = true;
	bool playing = true;

	size_t currentFrame = 0;

	sf::Time timer = sf::seconds(0);
	sf::Time frameTime = sf::seconds(0.2f);

public:
	// ReSharper disable once CppNonExplicitConvertingConstructor
	Animation(sf::Sprite &sprite);

	Animation(const Animation& animation);
	Animation(Animation&& animation) noexcept;

	Animation& operator=(const Animation& animation);
	Animation& operator=(Animation&& animation) noexcept;

	~Animation() = default;

	void addFrame(const sf::Vector2i& frame);
	void setFrameSize(const sf::Vector2i& frameSize);

	void setCurrentFrame(const size_t frame);
	void setCurrentFrame() const;

	void update(int64_t microsecondsElapsed);
	void update(const sf::Time& elapsed);
	
	void play(bool reset = false);
	void stop();
	void reset();

	void setLooped(bool looped);
	void setFrameTime(const sf::Time& frameTime);

	[[nodiscard]] bool isPlaying() const;
	[[nodiscard]] bool isLooped() const;
};
