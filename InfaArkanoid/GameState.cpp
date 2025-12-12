//GameState.cpp
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"	
#include <fstream>
#include <iostream>



void GameState::capture(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks){
//do zapisu tj pozycje i predkosci etc

	paddlePosition = { paddle.getX(), paddle.getY() };
	ballPosition = ball.getPosition();
	ballVelocity = ball.getVelocity();

	blocks.clear();
	for (const auto& b : bricks) {
		if (!b.czyZniszczony()) {
			BlockData dane;
			sf::Vector2f pos = b.getPosition();
			dane.x = pos.x;
			dane.y = pos.y;
			dane.hp = b.getHP();
			blocks.push_back(dane);

		}
	}
}


bool GameState::saveToFile(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Nie mozna otorzyc by zapisac pliku o nazwie " << filename << std::endl;
		return false;
	}

	//dla porzadku w pliku

	//Paletka
	file << "PADDLE " << paddlePosition.x << " "
		<< paddlePosition.y << "\n";

	//Pilka
	file << "BALL "
		<< ballPosition.x << " "
		<< ballPosition.y << " "
		<< ballVelocity.x << " "
		<< ballVelocity.y << "\n";

	//Bloczki
	file << "BRICKS " << blocks.size() << "\n";
	for (const auto& b : blocks) {
		file << b.x << " "
			<< b.y << " "
			<< b.hp << "\n";
	}


	file.close();
	return true;
}


bool GameState::loadFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) return false;

	std::string label;

	//pa;etla
	if (!(file>> label >> paddlePosition.x >> paddlePosition.y))
		return false;
	
	// Pilka
		if (!(file >> label >> ballPosition.x >> ballPosition.y
			>> ballVelocity.x >> ballVelocity.y))
			return false;

	// Bloki
	int blocksCount = 0;
	if (!(file >> label >> blocksCount))
		return false;

	blocks.clear();
	for (int i = 0; i < blocksCount; ++i) {
		float x, y;
		int hp;
		if (!(file >> x >> y >> hp)) return false;
		blocks.push_back({ x, y, hp });
	}

	return true;
}



void GameState::load(Paddle& paddle, Ball& ball, std::vector<Brick>& bricks) {
	paddle.setPosition(paddlePosition.x, paddlePosition.y);
	ball.setPosition(ballPosition.x, ballPosition.y);
	ball.setVelocity(ballVelocity);

	bricks.clear();
	const int ILOSC_KOLUMN = 12;
	const int ILOSC_WIERSZY = 4;
	float ROZMIAR_BLOKU_X = (1000 - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
	float ROZMIAR_BLOKU_Y = 20.f;

	for (const auto& b : blocks) {
		bricks.emplace_back(
			sf::Vector2f(b.x, b.y),
			sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
			b.hp
		);
	}
}
