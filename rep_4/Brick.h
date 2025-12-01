//Brick.h
#pragma once
#include <SFML/Graphics.hpp>

class Brick : public sf::RectangleShape{		//tu dziedziczy z prostokata jest w upragdzie m_shape i inne typu rysowanie etc
private:
	int hp;
	void updateColor();

public:
	Brick(sf::Vector2f startPos, sf::Vector2f rozmiar, int zycie);
	void trafienie();
	bool czyZniszczony() const;

	//get global bunds dostaje automatycznie z dziedziczenia RectangleShape

};

