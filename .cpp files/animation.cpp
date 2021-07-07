#include "Animation.h"

cAnimation::cAnimation() : texture_(NULL)
{

}

cAnimation::~cAnimation() {}

void cAnimation::addFrame(sf::IntRect rect)
{
	frames_.push_back(rect);
}

void cAnimation::setSpriteSheet(const sf::Texture& texture)
{
	texture_ = &texture;
}

const sf::Texture* cAnimation::getSpriteSheet() const
{
	return texture_;
}

std::size_t cAnimation::getSize() const
{
	return frames_.size();
}

const sf::IntRect& cAnimation::getFrame(std::size_t n) const
{
	return frames_[n];
}
