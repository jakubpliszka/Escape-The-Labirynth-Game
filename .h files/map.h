#pragma once
#include <SFML/Graphics.hpp>

class cMap {
public:
	cMap();
	void draw(sf::RenderWindow &window);
	void setObjects(std::vector<sf::RectangleShape> &objects);
	void setPoints(std::vector<sf::CircleShape> &points);
	void drawPoints(sf::RenderWindow &window, std::vector<sf::CircleShape> &points);
	
private:
	std::vector<sf::RectangleShape> objects_;
	std::vector<sf::CircleShape> points_;
};
