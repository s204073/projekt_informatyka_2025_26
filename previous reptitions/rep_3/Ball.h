#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball {
private:
	float x, y;				//polozenie
	float radius;			//promien
	float vx, vy;		//predkosc w x i y
	sf::CircleShape m_shape;
	sf::Vector2f velocity{ 200.f, 100.f }; //predkosc poczatkowa, 200 po x tylko? to tak jakby glupie

public:
	Ball(sf::Vector2f startPos, float radius, sf::Vector2f startVel);	//konstruktor
	void odbijY();
	void odbijX();
	void draw(sf::RenderTarget& window);
	void ruch(sf::Time dt, sf::Vector2f windowWH, Paddle& pd1);		//windowWH - szerokosc i wysokosc
	void collideWalls(float windowWidth, float windowHeight);
	bool collidePaddle(const Paddle& pd1);

	sf::FloatRect getGlobalBounds() const { return m_shape.getGlobalBounds(); }

	//kolizje - chyba w ruch sa?
	//void kolizja_paletka(const Paddle& pd1);
	//void kolizja_sciana(sf::Vector2f windowWH);

	//pobieranie biezacych danych - getteryyyy

	sf::Vector2f getPosition() const { return m_shape.getPosition(); }
	sf::Vector2f getVelocity() const { return velocity; }
	float getRadius() const { return radius; }


	void setPosition(float newX, float newY);
	void setVelocity(float newVX, float newVY);			//nie wiem po co to jeszcze

};





