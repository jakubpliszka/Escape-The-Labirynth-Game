#pragma once
#include <SFML/Graphics.hpp>

class cScore {
public:
	cScore(int score);
	~cScore();
	void update(sf::RenderWindow &window, int &score);
	void draw(sf::RenderWindow &window);
	void move(float x, float y);
private:
	sf::Text scoreDisplay_;
	int score_;
	sf::Font font_;
};
