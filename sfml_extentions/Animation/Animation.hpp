#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include <vector>

class Animation final
{
private:
	std::vector<sf::IntRect> frames;
	
	sf::Sprite &sprite;

	bool looped = true;
	bool playing = true;

	size_t currentFrame = 0;

	sf::Time timer = sf::seconds(0);
	sf::Time frameTime = sf::seconds(0.2f);

public:
	Animation(sf::Sprite &sprite);

	Animation& operator=(const Animation& animation);
	Animation& operator=(Animation&& animation) noexcept;

	void addFrame(const sf::IntRect& frame);
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