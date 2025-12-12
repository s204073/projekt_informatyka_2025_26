//game.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"


class Game {
private:
	Paddle m_paddle;
	Ball m_ball;
	std::vector<Brick> m_bricks;
	bool m_lost = false;
	bool m_won = false;



public:
	Game();
	void update(sf::Time dt, sf::RenderWindow& window);			//wie ile minelo od klatki i okno zeby mozna np zamknac
	void render(sf::RenderWindow& target);						//moze rysowac w nim pog

	bool hasLost() const { return m_lost; }
	bool hasWon()  const { return m_won; }

	const Paddle& getPaddle() const { return m_paddle; }
	const Ball& getBall()   const { return m_ball; }
	const std::vector<Brick>& getBricks() const { return m_bricks; }

	Paddle& getPaddle() { return m_paddle; }
	Ball& getBall() { return m_ball; }
	std::vector<Brick>& getBricks() { return m_bricks; }



};
