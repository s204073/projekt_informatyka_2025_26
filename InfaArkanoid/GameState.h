//GameState.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct BlockData {
	float x, y;
	int hp;
};

class Paddle;
class Ball;
class Brick;

class GameState {
private:
	sf::Vector2f paddlePosition;
	sf::Vector2f ballPosition;
	sf::Vector2f ballVelocity;

	std::vector<BlockData> blocks;

public:
	void capture(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks);
	bool saveToFile(const std::string& filename);
	bool loadFromFile(const std::string& filename);
	void load(Paddle& paddle, Ball& ball, std::vector<Brick>& bricks);

};