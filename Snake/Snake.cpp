#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Snake.hpp"

Snake::Snake() : length(1) {
	snake_body.push_back({ 0,0 });
}

int Snake::getLength() {
	return length;
}
const std::vector<std::pair<int, int>>& Snake::getBody(bool log = true) const {
	if (log) {
		for (const auto& segment : snake_body) {
			std::cout << "(" << segment.first << ", " << segment.second << ")\n";
		}
		std::cout << std::endl;
	}
	return snake_body;
}

bool Snake::touching(std::pair<int, int> position) {
	for (const auto block : snake_body) {
		if (block == position) {
			return true;
		}
	}
	return false;
}


bool Snake::touchingBody() {
	std::vector<std::pair<int, int>> snake_blocks = snake_body;
	if (snake_body.size() > 1) {
		snake_blocks.erase(snake_blocks.begin());

	}
	else {
		return false;
	}

std::pair<int, int> head = getHead();
for (const auto block : snake_blocks) {
	if (block == head) {
		return true;
	}
}
return false;
}
bool Snake::outOfBounds(int length, int height) {
	std::pair<int, int> head = getHead();
	if (head.first < 0 || head.first > length || head.second > height || head.second < 0) {
		return true;
	}
	else {
		return false;
	}
}
const std::pair<int, int> Snake::getHead() const {
	return snake_body.front();
}
std::string Snake::getDirection() {
	return direction;
}

void Snake::setDirection(const std::string& newDirection) {
	if (direction == "LEFT" && newDirection == "RIGHT") {
		return;
	}
	else if (direction == "RIGHT" && newDirection == "LEFT") {
		return;
	}
	else if (direction == "UP" && newDirection == "DOWN") {
		return;
	}
	else if (direction == "DOWN" && newDirection == "UP") {
		return;

	}
	else {
		direction = newDirection;

	}
}

void Snake::grow() {
	snake_body.push_back(snake_body.back()); // duplicate last block
}
void Snake::move() {
	std::pair<int, int>  lastBlock = snake_body.back();
	std::pair<int, int> firstBlock = snake_body.front();
	snake_body.pop_back();
	if (direction == "UP") {
		lastBlock = { firstBlock.first, firstBlock.second - speed };
	}
	else if (direction == "DOWN") {
		lastBlock = { firstBlock.first, firstBlock.second + speed };
	}
	else if (direction == "RIGHT") {
		lastBlock = { firstBlock.first + speed, firstBlock.second };
	}
	else if (direction == "LEFT") {
		lastBlock = { firstBlock.first - speed, firstBlock.second };
	}
	snake_body.insert(snake_body.begin(), lastBlock);
	// std::cout << direction;
	Snake::getBody(false);
}


