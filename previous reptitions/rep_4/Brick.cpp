//Brick.cpp
#include "Brick.h"
#include <SFML/Graphics.hpp>

Brick::Brick(sf::Vector2f startPos, sf::Vector2f rozmiar, int zycie) : sf::RectangleShape(rozmiar){
	setPosition(startPos);
	setOrigin(rozmiar.x / 2, rozmiar.y / 2); // srodek prostokata
	hp = zycie;
	updateColor();
}

void Brick::trafienie() {
		hp--;
		updateColor();
	}

bool Brick::czyZniszczony() const {
	return hp <= 0;
}

void Brick::updateColor() {
	if (hp<=0) setFillColor(sf::Color::Transparent);
	else if (hp == 1) setFillColor(sf::Color::Yellow);
	else if (hp == 2) setFillColor(sf::Color::Green);
	else setFillColor(sf::Color::Red);
}
