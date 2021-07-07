#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.h"

class cAnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
	cAnimatedSprite(sf::Time frameTime, bool paused, bool looped);
	~cAnimatedSprite();
	void update(sf::Time deltaTime);
	void setAnimation(const cAnimation& animation);
	void setFrameTime(sf::Time time);
	void play();
	void play(const cAnimation& animation);
	void pause();
	void stop();
	void setLooped(bool looped);
	const cAnimation* getAnimation() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	bool isLooped() const;
	bool isPlaying() const;
	sf::Time getFrameTime() const;
	void setFrame(std::size_t newFrame, bool resetTime = true);

private:
	const cAnimation* animation_;
	sf::Time frameTime_;
	sf::Time currentTime_;
	std::size_t currentFrame_;
	bool isPaused_;
	bool isLooped_;
	const sf::Texture* texture_;
	sf::Vertex vertices_[4];

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
