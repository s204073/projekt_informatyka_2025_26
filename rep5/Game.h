//game.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"


class Game {
private:
	sf::RenderWindow m_window; 		//m_window - bo member zmienna
	sf::Clock m_deltaClock;
	Paddle m_paddle;
	Ball m_ball;
	std::vector<Brick> m_bricks;

	void processEvents();
	void update(sf::Time dt);
	void render();

public:
	Game();
	void run();

};
