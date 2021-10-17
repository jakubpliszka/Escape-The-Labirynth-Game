#pragma once
#include <SFML/Graphics.hpp>

class cMenu  {
public: 
	cMenu(float width, float height);
	~cMenu();
	void draw(sf::RenderWindow &window);
	void drawControls(sf::RenderWindow &window);
	void drawCredits(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
	int run(sf::RenderWindow &window, cMenu &menu);
private:
	sf::Font font_;
	sf::Text title_;
	sf::Font titleFont_;
	sf::Text menu_[3];
	sf::Text controls_;
	sf::Text credits_;
	sf::Texture texture_;
	sf::Sprite sprite_;
	int selectedChoose_;
};