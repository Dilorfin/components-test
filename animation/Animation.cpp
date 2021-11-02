#include "Animation.hpp"

Animation::Animation(sf::Sprite &sprite) 
	: sprite(sprite)
{}

Animation::Animation(const Animation& animation)
	: frames(animation.frames),
	  sprite(animation.sprite),
	  looped(animation.looped),
	  playing(animation.playing),
	  currentFrame(animation.currentFrame),
	  timer(animation.timer),
	  frameTime(animation.frameTime)
{ }

Animation::Animation(Animation&& animation) noexcept
	: frames(std::move(animation.frames)),
	  sprite(animation.sprite),
	  looped(animation.looped),
	  playing(animation.playing),
	  currentFrame(animation.currentFrame),
	  timer(animation.timer),
	  frameTime(animation.frameTime)
{ }

Animation& Animation::operator=(const Animation& animation)
{
	this->frames = animation.frames;
	this->sprite = animation.sprite;
	this->looped = animation.looped;
	this->playing = animation.playing;
	this->currentFrame = animation.currentFrame;
	this->timer = animation.timer;
	this->frameTime = animation.frameTime;
	return *this;
}

Animation& Animation::operator=(Animation&& animation) noexcept
{
	this->frames = std::move(animation.frames);
	this->sprite = std::move(animation.sprite);
	this->looped = animation.looped;
	this->playing = animation.playing;
	this->currentFrame = animation.currentFrame;
	this->timer = animation.timer;
	this->frameTime = animation.frameTime;
	return *this;
}

void Animation::addFrame(const sf::Vector2i& frame)
{
	frames.push_back(frame);
	this->setCurrentFrame();
}

void Animation::setFrameSize(const sf::Vector2i& frameSize)
{
	this->frameSize = frameSize;
}

void Animation::setCurrentFrame(const size_t frame)
{
	currentFrame = frame;
	this->setCurrentFrame();
}
void Animation::setCurrentFrame() const
{
	sprite.setTextureRect(sf::IntRect(frames[currentFrame], frameSize));
}

void Animation::update(int64_t microsecondsElapsed)
{
	const auto elapsed = sf::microseconds(microsecondsElapsed);
	this->update(elapsed);
}

void Animation::update(const sf::Time& elapsed)
{
	if (!playing) return;

	timer += elapsed;

	if (timer >= frameTime)
	{
		// keeping: timer - frameTime
		timer = sf::microseconds(timer.asMicroseconds() % frameTime.asMicroseconds());
		
		currentFrame++;

		if (currentFrame >= frames.size())
		{
			if (!looped)
			{
				playing = false;
				return;
			}
			currentFrame = 0;
		}

		this->setCurrentFrame();
	}
}

void Animation::play(const bool reset)
{
	if (reset) this->reset();
	playing = true;
}
void Animation::stop()
{
	playing = false;
}
void Animation::reset()
{
	currentFrame = 0;
	timer = sf::seconds(0);
}

void Animation::setLooped(const bool looped)
{
	this->looped = looped;
}
void Animation::setFrameTime(const sf::Time& frameTime)
{
	this->frameTime = frameTime;
}

bool Animation::isPlaying() const
{
	return playing;
}
bool Animation::isLooped() const
{
	return looped;
}