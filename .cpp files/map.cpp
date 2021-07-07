#include <SFML/Graphics.hpp>
#include "map.h"
#include <ctime>
#include <vector>

cMap::cMap() {}

void cMap::draw(sf::RenderWindow &window) {
	for (int i = 0; i < objects_.size(); i++) {
		window.draw(objects_[i]);
	}
	for (int i = 0; i < points_.size(); i++) {
		window.draw(points_[i]);
	}
}

void cMap::drawPoints(sf::RenderWindow &window, std::vector<sf::CircleShape> &points) {		
	points_ = points;
	for (int i = 0; i < points.size(); i++) {
		window.draw(points[i]);
	}
}

void cMap::setObjects(std::vector<sf::RectangleShape> &objects) {							//map creation
	sf::RectangleShape w1;
	w1.setSize(sf::Vector2f(40, 1080));
	w1.setFillColor(sf::Color::Black);
	objects.push_back(w1);

	sf::RectangleShape w2;
	w2.setSize(sf::Vector2f(1920, 40));
	w2.setFillColor(sf::Color::Black);
	objects.push_back(w2);

	sf::RectangleShape w3;
	w3.setSize(sf::Vector2f(2500, 500));
	w3.setFillColor(sf::Color::Black);
	w3.setPosition(sf::Vector2f(0, 1040));
	objects.push_back(w3);

	sf::RectangleShape w4;
	w4.setSize(sf::Vector2f(800, 1500));
	w4.setFillColor(sf::Color::Black);
	w4.setPosition(sf::Vector2f(1880, 0));
	objects.push_back(w4);
	
	sf::RectangleShape o[32];
	o[0].setSize(sf::Vector2f(40, 300));
	o[0].setPosition(sf::Vector2f(150, 0));
	o[1].setSize(sf::Vector2f(40, 150));
	o[1].setPosition(sf::Vector2f(150, 450));
	o[2].setSize(sf::Vector2f(150, 40));
	o[2].setPosition(sf::Vector2f(40, 600));
	o[3].setSize(sf::Vector2f(40, 250));
	o[3].setPosition(sf::Vector2f(150, 790));
	o[4].setSize(sf::Vector2f(150, 40));
	o[4].setPosition(sf::Vector2f(150, 410));
	o[5].setSize(sf::Vector2f(40, 300));
	o[5].setPosition(sf::Vector2f(300, 150));
	o[6].setSize(sf::Vector2f(150, 40));
	o[6].setPosition(sf::Vector2f(340, 150));
	o[7].setSize(sf::Vector2f(530, 40));
	o[7].setPosition(sf::Vector2f(470, 320));
	o[8].setSize(sf::Vector2f(40, 190));
	o[8].setPosition(sf::Vector2f(620, 150));
	o[9].setSize(sf::Vector2f(40, 210));
	o[9].setPosition(sf::Vector2f(1000, 150));
	o[10].setSize(sf::Vector2f(40, 190));
	o[10].setPosition(sf::Vector2f(300, 650));
	o[11].setSize(sf::Vector2f(190, 40));
	o[11].setPosition(sf::Vector2f(300, 650));
	o[12].setSize(sf::Vector2f(40, 550));
	o[12].setPosition(sf::Vector2f(470, 500));
	o[13].setSize(sf::Vector2f(190, 40));
	o[13].setPosition(sf::Vector2f(470, 500));
	o[14].setSize(sf::Vector2f(40, 340));
	o[14].setPosition(sf::Vector2f(810, 340));
	o[15].setSize(sf::Vector2f(750, 40));
	o[15].setPosition(sf::Vector2f(620, 650));
	o[16].setSize(sf::Vector2f(40, 190));
	o[16].setPosition(sf::Vector2f(620, 650));
	o[17].setSize(sf::Vector2f(490, 40));
	o[17].setPosition(sf::Vector2f(620, 840));
	o[18].setSize(sf::Vector2f(40, 190));
	o[18].setPosition(sf::Vector2f(920, 880));
	o[19].setSize(sf::Vector2f(40, 380));
	o[19].setPosition(sf::Vector2f(1360, 500));
	o[20].setSize(sf::Vector2f(170, 40));
	o[20].setPosition(sf::Vector2f(1000, 500));
	o[21].setSize(sf::Vector2f(40, 500));
	o[21].setPosition(sf::Vector2f(1170, 40));
	o[22].setSize(sf::Vector2f(190, 40));
	o[22].setPosition(sf::Vector2f(1170, 320));
	o[23].setSize(sf::Vector2f(190, 40));
	o[23].setPosition(sf::Vector2f(1360, 840));
	o[24].setSize(sf::Vector2f(40, 230));
	o[24].setPosition(sf::Vector2f(1550, 650));
	o[25].setSize(sf::Vector2f(190, 40));
	o[25].setPosition(sf::Vector2f(1550, 650));
	o[26].setSize(sf::Vector2f(40, 190));
	o[26].setPosition(sf::Vector2f(810, 0));
	o[27].setSize(sf::Vector2f(40, 200));
	o[27].setPosition(sf::Vector2f(1700, 840));
	o[28].setSize(sf::Vector2f(340, 40));
	o[28].setPosition(sf::Vector2f(1400, 500));
	o[29].setSize(sf::Vector2f(40, 350));
	o[29].setPosition(sf::Vector2f(1520, 150));
	o[30].setSize(sf::Vector2f(380, 40));
	o[30].setPosition(sf::Vector2f(1360, 150));
	o[31].setSize(sf::Vector2f(40, 190));
	o[31].setPosition(sf::Vector2f(1700, 320));


	for (int i = 0; i < 32; i++) {
		o[i].setFillColor(sf::Color::Black);
		objects.push_back(o[i]);
	}
	objects_ = objects;
}

void cMap::setPoints(std::vector<sf::CircleShape> &points) {						//set score on map
	sf::CircleShape c[20];
	for (int i = 0; i < 20; i++) {
		c[i].setRadius(5);
		c[i].setFillColor(sf::Color::Yellow);
	}
	for (int i = 0; i < 20; i++) {
		c[i].setPosition(rand() % 1860 + 60, rand() % 1020 + 60);  

		for (int j = 0; j < objects_.size(); j++) {					
			if (c[i].getGlobalBounds().intersects(objects_[j].getGlobalBounds())) {
				c[i].setPosition(rand() % 1860 + 60, rand() % 1020 + 60); //c[i].setPosition(rand() % 1880 + 40, rand() % 1040 + 40);
				j = -1;
			}
		}
		points.push_back(c[i]);
	}

	
	points_ = points;
}

