//ball.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball {
private:
	float x, y;				//polozenie
	float radius;			//promien
	sf::CircleShape m_shape;
	sf::Vector2f velocity{ 100.f, 100.f }; //predkosc poczatkowa

public:
	Ball(sf::Vector2f startPos, float radius, sf::Vector2f startVel);	//konstruktor
	void odbijY();
	void odbijX();
	void draw(sf::RenderTarget& window);
	void ruch(sf::Time dt, sf::Vector2f windowWH, Paddle& pd1);		//windowWH - szerokosc i wysokosc
	void collideWalls(float windowWidth, float windowHeight);
	bool collidePaddle(const Paddle& pal);      //const - f nie modyfikuje obiektu 
	void setVelocity(sf::Vector2f v);

	sf::FloatRect getGlobalBounds() const { return m_shape.getGlobalBounds(); }


	//pobieranie biezacych danych - getteryyyy

	sf::Vector2f getPosition() const { return m_shape.getPosition(); }
	sf::Vector2f getVelocity() const { return velocity; }
	float getRadius() const { return radius; }


	void setPosition(float newX, float newY);
	void setVelocity(float newVX, float newVY);			

};





