#include <SFML/Graphics.hpp>
#include "game.h"
#include "menu.h"
#include <iostream>
using namespace sf;

int main() {	
	
	RenderWindow menuWindow(VideoMode(1280, 720), "Escape The Labyrinth");					//menu window
	cMenu menu(menuWindow.getSize().x, menuWindow.getSize().y);

	if (menu.run(menuWindow, menu) == 1) {
		RenderWindow gameWindow(VideoMode(1920, 1080), "Escape The Labyrinth");				//game window
		cGame game(gameWindow.getSize().x, gameWindow.getSize().y);
		game.run(gameWindow, game);
	}

	return 0;
}
