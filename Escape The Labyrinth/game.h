#pragma once
#include <SFML/Graphics.hpp>

class cGame {
public:	
	cGame(float width, float height);
	~cGame();

	void draw(sf::RenderWindow &window);
	int run(sf::RenderWindow &window, cGame &Game);
private:
	sf::Texture background_;
	sf::Texture hero_;
	sf::Sprite sprite_;
	sf::Font font_;
};