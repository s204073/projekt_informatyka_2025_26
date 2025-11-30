#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <math.h>


Ball::Ball(sf::Vector2f startPos, float radius, sf::Vector2f startVel) {
	velocity = startVel;
	m_shape.setPosition(startPos);
	m_shape.setRadius(radius);
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setOrigin(radius, radius);		//srodek kola bedzie patrzony przy warunkach jakby

	x = startPos.x;
	y = startPos.y;

}

void Ball::draw(sf::RenderTarget& window) {
	window.draw(m_shape);
}

void Ball::odbijX() {
	velocity.x = -velocity.x;
}

void Ball::odbijY() {
	velocity.y = -velocity.y;
}

void Ball::setPosition(float newX, float newY) {
	x = newX;
	y = newY;
	m_shape.setPosition(x, y);
}

void Ball::collideWalls(float windowWidth, float windowHeight) {
	float xp = m_shape.getPosition().x;
	float yp = m_shape.getPosition().y;
	float rp = m_shape.getRadius();

	if (xp - rp <= 0 || xp + rp >= windowWidth) {
		odbijX();
	}
	if (yp - rp <= 0) {
		odbijY();
	}
}

bool Ball::collidePaddle(const Paddle& pd1) {
	//przypisanie zmiennych dla ladniekjszego i czytelniejszefo kodu

	float palX = pal.getX();				// para,metry paletki
	float palY = pal.getY();
	float palW = pal.getSzerokosc();
	float palH = pal.getWysokosc();
	float palTop = palY - palH / 2.f; // gorna krawedz paletski

	float bx = m_shape.getPosition().x;				//parametry pilki
	float by = m_shape.getPosition().y;
	float br = m_shape.getRadius();

	//zeby sprawdzic czy sie odbila, trzeba sprawdzic czy jest centralnie nad paletka i czy dotyka gornej powierzchni, wiec
	//warunek 1: czy pilka jest na osi x nad szerokoscia paletki
	bool nadPaletka = (bx >= palX - palW / 2.f) && (bx <= palX + palW / 2.f);

	//warunek 2: czy pilka dotyka od gory paletki a nie od boku np
	bool kontaktOdGory = (by + br) >= palTop && (by - br) < palTop;

	//sprawdzzenie warunkow
	if (nadPaletka && kontaktOdGory) {
		velocity.y = -std::abs(velocity.y);  //pilka zawsze do gory obviously :rolling_eyes:
		by = palTop - br;        //ustawienie pilki dokladnie nad gore paletki
		m_shape.setPosition(bx, by);
		x = bx;
		y = by;
		return true;
	}
	return false;

	void Ball::ruch(sf::Time dt, sf::Vector2f windowWH, Paddle & pd1) {
		m_shape.move(velocity * dt.asSeconds());
		x = m_shape.getPosition().x;
		y = m_shape.getPosition().y;

		collideWalls(windowWH.x, windowWH.y);
		collidePaddle(pd1);
	}








//void Ball::ruch(sf::Time dt, sf::Vector2f windowWH, Paddle& pd1) {		//kolizja ze sciana
//	m_shape.move(velocity * dt.asSeconds());
//	float xp = m_shape.getPosition().x;
//	float yp = m_shape.getPosition().y;
//	float rp = m_shape.getRadius();
//	if (xp - rp <= 0 || xp + rp >= windowWH.x) {
//		velocity.x = -velocity.x;
//	}
//	if (yp - rp <= 0) {
//		velocity.y = -velocity.y;
//	}
//	if (yp + rp >= windowWH.y) {
//		velocity.y = 0;
//		velocity.x = 0;
//	}
//
//	if (m_shape.getGlobalBounds().intersects(pd1.getGlobalBounds())) {
//		velocity.y = -velocity.y;
//	}
//}
//
//


