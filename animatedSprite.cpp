#include "animatedSprite.h"

cAnimatedSprite::cAnimatedSprite(sf::Time frameTime, bool paused, bool looped) : animation_(NULL), frameTime_(frameTime), currentFrame_(0), isPaused_(paused), isLooped_(looped), texture_(NULL)
{
}

cAnimatedSprite::~cAnimatedSprite() {}

void cAnimatedSprite::setAnimation(const cAnimation& animation)
{
	animation_ = &animation;
	texture_ = animation_->getSpriteSheet();
	currentFrame_ = 0;
	setFrame(currentFrame_);
}

void cAnimatedSprite::setFrameTime(sf::Time time)
{
	frameTime_ = time;
}

void cAnimatedSprite::play()
{
	isPaused_ = false;
}

void cAnimatedSprite::play(const cAnimation& animation)
{
	if (getAnimation() != &animation)
		setAnimation(animation);
	play();
}

void cAnimatedSprite::pause()
{
	isPaused_ = true;
}

void cAnimatedSprite::stop()
{
	isPaused_ = true;
	currentFrame_ = 0;
	setFrame(currentFrame_);
}

void cAnimatedSprite::setLooped(bool looped)
{
	isLooped_ = looped;
}


const cAnimation* cAnimatedSprite::getAnimation() const
{
	return animation_;
}

sf::FloatRect cAnimatedSprite::getLocalBounds() const
{
	sf::IntRect rect = animation_->getFrame(currentFrame_);

	float width = static_cast<float>(std::abs(rect.width));
	float height = static_cast<float>(std::abs(rect.height));

	return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect cAnimatedSprite::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

bool cAnimatedSprite::isLooped() const
{
	return isLooped_;
}

bool cAnimatedSprite::isPlaying() const
{
	return !isPaused_;
}

sf::Time cAnimatedSprite::getFrameTime() const
{
	return frameTime_;
}

void cAnimatedSprite::setFrame(std::size_t newFrame, bool resetTime)
{
	if (animation_)
	{
		sf::IntRect rect = animation_->getFrame(newFrame);

		vertices_[0].position = sf::Vector2f(0.f, 0.f);
		vertices_[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
		vertices_[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
		vertices_[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

		float left = static_cast<float>(rect.left) + 0.0001f;
		float right = left + static_cast<float>(rect.width);
		float top = static_cast<float>(rect.top);
		float bottom = top + static_cast<float>(rect.height);

		vertices_[0].texCoords = sf::Vector2f(left, top);
		vertices_[1].texCoords = sf::Vector2f(left, bottom);
		vertices_[2].texCoords = sf::Vector2f(right, bottom);
		vertices_[3].texCoords = sf::Vector2f(right, top);
	}

	if (resetTime)
		currentTime_ = sf::Time::Zero;
}

void cAnimatedSprite::update(sf::Time deltaTime)
{
	if (!isPaused_ && animation_)
	{	
		currentTime_ += deltaTime;

		if (currentTime_ >= frameTime_)
		{
			currentTime_ = sf::microseconds(currentTime_.asMicroseconds() % frameTime_.asMicroseconds());

			if (currentFrame_ + 1 < animation_->getSize())
				currentFrame_++;
			else
			{
				currentFrame_ = 0; 

				if (!isLooped_)
				{
					isPaused_ = true;
				}

			}

			setFrame(currentFrame_, false);
		}
	}
}

void cAnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (animation_ && texture_)
	{
		states.transform *= getTransform();
		states.texture = texture_;
		target.draw(vertices_, 4, sf::Quads, states);
	}
}