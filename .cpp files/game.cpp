#include "game.h"
#include "animation.h"
#include "animatedSprite.h"
#include "map.h"
#include "score.h"
#include <ctime>
#include <SFML/Graphics.hpp>

cGame::cGame(float width, float height) {								//initialize game window
	background_.loadFromFile("game_background.png");
	sprite_.setTexture(background_);
	sprite_.setScale(3, 2.5);
	hero_.loadFromFile("hero.png");
	if (!font_.loadFromFile("arial.ttf")) {}
}

cGame::~cGame() {}

void cGame::draw(sf::RenderWindow &window) {
	window.draw(sprite_);
}

int cGame::run(sf::RenderWindow &window, cGame &game) {
	std::srand(time(NULL));
	window.setFramerateLimit(60);

	cAnimation walkingAnimationDown;											//set animations of character
	walkingAnimationDown.setSpriteSheet(hero_);
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	cAnimation walkingAnimationLeft;
	walkingAnimationLeft.setSpriteSheet(hero_);
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

	cAnimation walkingAnimationRight;
	walkingAnimationRight.setSpriteSheet(hero_);
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));

	cAnimation walkingAnimationUp;
	walkingAnimationUp.setSpriteSheet(hero_);
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

	cAnimation* currentAnimation = &walkingAnimationDown;							//character creation
	cAnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setPosition(sf::Vector2f(1920 / 2, 1080 / 2));
	animatedSprite.setScale(1.5, 1.5);


	sf::Clock frameClock;															//map creation
	std::vector<sf::RectangleShape> objects;
	std::vector<sf::CircleShape> points;
	cMap map;
	map.setObjects(objects);
	map.setPoints(points);
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1920.f / 3, 1080.f / 3));

	int score = 0;																	//score
	cScore count(score);
	sf::RectangleShape doors(sf::Vector2f(35,5));
	doors.setFillColor(sf::Color::Blue);
	doors.setPosition(sf::Vector2f(870, 1038));
	bool end = false;
	bool final = false;
	
	bool noKeyWasPressed = true;
	while (window.isOpen()) {														//running game loop
		sf::Event event;
		sf::Time frameTime = frameClock.restart();
		if (end == false) {															//movement of a character
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				currentAnimation = &walkingAnimationUp;
				animatedSprite.move(0.0, -2.0);
				count.move(animatedSprite.getPosition().x, animatedSprite.getPosition().y);
				for (int i = 0; i < objects.size(); i++) {
					if (animatedSprite.getGlobalBounds().intersects(objects[i].getGlobalBounds())) {
						animatedSprite.move(0.0, 2.0);
					}
				}
				noKeyWasPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				currentAnimation = &walkingAnimationDown;
				animatedSprite.move(0.0, 2.0);
				count.move(animatedSprite.getPosition().x, animatedSprite.getPosition().y);
				for (int i = 0; i < objects.size(); i++) {
					if (animatedSprite.getGlobalBounds().intersects(objects[i].getGlobalBounds())) {
						animatedSprite.move(0.0, -2.0);
					}
				}
				noKeyWasPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				currentAnimation = &walkingAnimationLeft;
				animatedSprite.move(-2.0, 0.0);
				count.move(animatedSprite.getPosition().x, animatedSprite.getPosition().y);
				for (int i = 0; i < objects.size(); i++) {
					if (animatedSprite.getGlobalBounds().intersects(objects[i].getGlobalBounds())) {
						animatedSprite.move(2.0, 0.0);
					}
				}
				noKeyWasPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				currentAnimation = &walkingAnimationRight;
				animatedSprite.move(2.0, 0.0);
				count.move(animatedSprite.getPosition().x, animatedSprite.getPosition().y);
				for (int i = 0; i < objects.size(); i++) {
					if (animatedSprite.getGlobalBounds().intersects(objects[i].getGlobalBounds())) {
						animatedSprite.move(-2.0, 0.0);
					}
				}
				noKeyWasPressed = false;
			}
		}
		animatedSprite.play(*currentAnimation);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if (end == true)	return 0;
		}

		if (noKeyWasPressed)
		{
			animatedSprite.stop();
		}
		noKeyWasPressed = true;

		animatedSprite.update(frameTime);																	//animation update

		
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) window.close();
		}

		for (int i = 0; i < points.size();) {																//points counter
			if (animatedSprite.getGlobalBounds().intersects(points[i].getGlobalBounds())) {
				 points.erase(points.begin() + i);
				 map.drawPoints(window, points);
				 count.update(window, score);
				 if (score == 20) {
					final = true;
				 }
			}
			else {
				i++;
			}
		}

		view.setCenter(animatedSprite.getPosition().x, animatedSprite.getPosition().y);						//zoomed and centered camera
		
		
		window.clear();
		window.setView(view);
		game.draw(window);
		map.draw(window);
		count.draw(window);
		if (final == true) {
			window.draw(doors);
		}
		window.draw(animatedSprite);
		if (animatedSprite.getGlobalBounds().intersects(doors.getGlobalBounds()) && final == true) {		//End of a game
			end = true;
			sf::Text win;
			sf::Text quit;
			quit.setFont(font_);
			win.setFont(font_);
			quit.setCharacterSize(20);
			quit.setPosition(animatedSprite.getPosition().x - 50, animatedSprite.getPosition().y + 100);
			quit.setString("Press Q to quit");
			win.setCharacterSize(50);
			win.setPosition(animatedSprite.getPosition().x-150, animatedSprite.getPosition().y-50);
			win.setString("Escape found!");
			window.draw(win);
			window.draw(quit);
		}
		window.display();
	}
	return -1;
}
