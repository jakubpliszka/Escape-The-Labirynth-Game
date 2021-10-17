#include "menu.h"
#include <SFML/Graphics.hpp>

cMenu::cMenu(float width, float height) {							//create menu
	texture_.loadFromFile("tilesetOpenGameBackground.png");
	sprite_.setTexture(texture_);
	sprite_.setScale(4, 3);
	if (!font_.loadFromFile("arial.ttf")) {}
	if(!titleFont_.loadFromFile("TheForegenRegular.otf"), 10) {}

	title_.setFont(titleFont_);
	title_.setFillColor(sf::Color::Black);
	title_.setString("Escape The Labyrinth");
	title_.setPosition(sf::Vector2f(width / 5, height * 0.03));
	title_.setCharacterSize(100);

	menu_[0].setFont(font_);
	menu_[0].setFillColor(sf::Color::Red);
	menu_[0].setString("Play");
	menu_[0].setPosition(sf::Vector2f(width / 2.1, height *0.4 ));

	menu_[1].setFont(font_);
	menu_[1].setFillColor(sf::Color::Black);
	menu_[1].setString("Controls");
	menu_[1].setPosition(sf::Vector2f(width / 2.18, height *0.5 ));

	menu_[2].setFont(font_);
	menu_[2].setFillColor(sf::Color::Black);
	menu_[2].setString("Credits");
	menu_[2].setPosition(sf::Vector2f(width / 2.15, height *0.6 ));

	controls_.setFont(font_);
	controls_.setFillColor(sf::Color::Black);
	controls_.setString("W - move up \n S - move down \n A - move left \n D - move right \n \n \n Get a score of 20 and find door to escape! \n \n \n Press Q to return");
	controls_.setPosition(sf::Vector2f(width / 5, height * 0.2));

	credits_.setFont(font_);
	credits_.setFillColor(sf::Color::Black);
	credits_.setString("All graphics from opengameart.org \n Thanks for playing! \n \n \n Press Q to return");
	credits_.setPosition(sf::Vector2f(width / 5, height * 0.2));
	selectedChoose_ = 0;
}

cMenu::~cMenu() {}

void cMenu::draw(sf::RenderWindow &window) {
	window.draw(sprite_);
	for (int i = 0; i < 3; i++) {
		window.draw(menu_[i]);
	}
	window.draw(title_);
}

void cMenu::drawControls(sf::RenderWindow &window) {
	window.draw(sprite_);
	window.draw(controls_);
}
void cMenu::drawCredits(sf::RenderWindow &window) {
	window.draw(sprite_);
	window.draw(credits_);
}

void cMenu::moveUp() {
	if (selectedChoose_ - 1 >= 0) {
		menu_[selectedChoose_].setFillColor(sf::Color::Black);
		selectedChoose_--;
		menu_[selectedChoose_].setFillColor(sf::Color::Red);
	}
}

void cMenu::moveDown() {
	if (selectedChoose_ +1 < 3) {
		menu_[selectedChoose_].setFillColor(sf::Color::Black);
		selectedChoose_++;
		menu_[selectedChoose_].setFillColor(sf::Color::Red);
	}
}

int cMenu::run(sf::RenderWindow &window, cMenu &menu) {									//menu is running
	int menuIndex = 0;
	bool ctrl = false;
	bool cred = false;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			
			if (event.type == sf::Event::KeyPressed) {									//menu movement
				switch (event.key.code) {
				case sf::Keyboard::W:
					menu.moveUp();
					menuIndex -= 1;
					if (menuIndex < 0) menuIndex = 0;
					break;
				case sf::Keyboard::S:
					menu.moveDown();
					menuIndex += 1;
					if (menuIndex > 2) menuIndex = 2;
					break;
				case sf::Keyboard::Enter:
					if (menuIndex == 0) {												
						window.close();
						return 1;
					}
					if (menuIndex == 1) {
						ctrl = true;
					}
					if (menuIndex == 2) {
						cred = true;
					}
					break;
				case sf::Keyboard::Q:
					ctrl = false;
					cred = false;
					break;
				}
			}
			if (event.type == sf::Event::Closed)	window.close();
		}

		window.clear();
		if (ctrl == false || cred == false) {										//check which window to open
			menu.draw(window); 
		}
		if (ctrl == true) { 
			menu.drawControls(window); 
		}
		if (cred == true) { 
			menu.drawCredits(window); 
		}
		window.display();
	}
	return -1;

}