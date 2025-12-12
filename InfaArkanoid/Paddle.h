//paddle.h
#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
	sf::RectangleShape m_shape;						//m_shape - ksztalt, m bo member zmienna
	float x, y;										//polozenie od srodka
	float szerokosc, wysokosc; 						//wymiary 
	float predkosc;									// predkosc kratekowa
	sf::Vector2f velocity{ 400.f, 0.f };			//400 pikseli tylko w x, .f-float


public:
	Paddle(sf::Vector2f startPos, sf::Vector2f rozmiar, sf::Vector2f startVel);
	void moveLeft();
	void moveRight();
	void clampToBounds(float windowWidth);


	void draw(sf::RenderTarget& window) {
		window.draw(m_shape);
	}

	//gettery - do pobierania przydatnych danych
	float getX() const { return x; }
	float getY() const { return y; }
	float getSzerokosc() const { return szerokosc; }
	float getWysokosc() const { return wysokosc; }
	sf::FloatRect getGlobalBounds() const;

	void setPosition(float newX, float newY);						//tu nie jestem pewien
};





