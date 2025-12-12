///Paddle.cpp
#include "Paddle.h"


Paddle::Paddle(sf::Vector2f startPos, sf::Vector2f rozmiar, sf::Vector2f startVel) {
	x = startPos.x;
	y = startPos.y;
	szerokosc = rozmiar.x;
	wysokosc = rozmiar.y;
	predkosc = startVel.x;

			//rozmaiar - Vector2f(szerokosc, wysokosc)
	m_shape.setPosition(startPos);
	m_shape.setSize(rozmiar);
	m_shape.setOrigin(rozmiar.x / 2.f, rozmiar.y / 2.f);	//polozenie patrzone od srodka
	m_shape.setFillColor(sf::Color::Red);
	velocity = startVel;

	}


	void Paddle::moveLeft() {
		m_shape.move(-predkosc, 0.f);		//przesuwa o wektor w lewo
		x = m_shape.getPosition().x;		//pobranie i zapisanie aktualnej pozycji
		y = m_shape.getPosition().y;

	}	
	void Paddle::moveRight() {
		m_shape.move(predkosc, 0.f);
		x = m_shape.getPosition().x;
		y = m_shape.getPosition().y;
	}


	//blokada wyjścia poza okno
	void Paddle::clampToBounds(float windowWidth) {
		float xCenter = m_shape.getPosition().x;
		float halfWidth = m_shape.getSize().x / 2.f;

		if (xCenter - halfWidth < 0.f) { m_shape.setPosition(halfWidth, m_shape.getPosition().y); }
		if (xCenter + halfWidth > windowWidth) { m_shape.setPosition(windowWidth - halfWidth, m_shape.getPosition().y); }
	}


sf::FloatRect Paddle::getGlobalBounds() const { return m_shape.getGlobalBounds(); }


void Paddle::setPosition(float newX, float newY) {
	x = newX;
	y = newY;
	m_shape.setPosition(x, y);
}



