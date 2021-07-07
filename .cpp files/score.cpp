#include "score.h"
#include <SFML/Graphics.hpp>


cScore::cScore(int score) {
	if (!font_.loadFromFile("arial.ttf")) {}
	scoreDisplay_.setFont(font_);
	scoreDisplay_.setFillColor(sf::Color::White);
	scoreDisplay_.setPosition(1190, 360);
	scoreDisplay_.setCharacterSize(20);
	std::string s = std::to_string(score);
	scoreDisplay_.setString("Score: " + s);
	score_ = score;
}

cScore::~cScore() {}

void cScore::move(float x, float y) {
	scoreDisplay_.setPosition(x + 230, y - 180);
}

void cScore::update(sf::RenderWindow &window, int &score) {				//score update
	score++;
	
	std::string s = std::to_string(score);
	scoreDisplay_.setString("Score: " + s);
	if (score == 20) {
		scoreDisplay_.setString("Find door");
	}
	score_ = score;
}

void cScore::draw(sf::RenderWindow &window) {
	window.draw(scoreDisplay_);
}
