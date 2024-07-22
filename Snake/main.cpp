#include <iostream>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"

void drawSnake(sf::RenderWindow *window, const Snake& snake);
void drawFood(sf::RenderWindow* window, std::pair<int, int> foodPos);
static void checkEaten(Snake& snake, std::pair<int, int>& foodPos, int* score);
static void checkDeath(sf::RenderWindow* window, Snake& snake, int& windowLength, int& windowHeight);
int main() {
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> lengthDist(0, 39);
	std::uniform_int_distribution<int> widthDist(0, 29); 
	sf::Font font;
	if (!font.loadFromFile("Montserrat-Black.ttf")) {
		// Handle error
		return -1;
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	int windowLength = 800;
	int windowHeight = 600;
	text.setPosition(30,windowHeight-30);
	int score = 0;
	text.setString(std::to_string(score));
	std::pair<int, int> foodPos = {lengthDist(rng)*20, widthDist(rng)*20};
	sf::RenderWindow window(sf::VideoMode(windowLength, windowHeight), "Snake");
	sf::Event event;
	sf::RectangleShape rectangle(sf::Vector2f(20, 20));
	window.setFramerateLimit(10);
	Snake snake = Snake();
	std::string currentDirection = "DOWN";
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					currentDirection = "UP";
					break;
				case sf::Keyboard::A:
					currentDirection = "LEFT";
					break;
				case sf::Keyboard::D:
					currentDirection = "RIGHT";
					break;
				case sf::Keyboard::S:
					currentDirection = "DOWN";
					break;
				case sf::Keyboard::G:
					snake.grow();
					break;
				};
				
			};
		};
		text.setString(std::to_string(score));
		window.clear();
		window.draw(text);
		snake.setDirection(currentDirection);
		snake.move();
		checkDeath(&window, snake, windowLength, windowHeight);
		checkEaten(snake, foodPos, &score);
		drawFood(&window, foodPos);
		drawSnake(&window, snake);
		window.display();
	}
}


void drawSnake(sf::RenderWindow *window, const Snake &snake) { // snake passed by const reference
	for (const auto& block : snake.getBody(false)) {
		sf::RectangleShape snakeBlock(sf::Vector2f(20, 20));
		snakeBlock.setPosition(static_cast<float>(block.first), static_cast<float>(block.second)); 
		snakeBlock.setFillColor(sf::Color::Green);
		window->draw(snakeBlock);
	}

}

static void checkDeath(sf::RenderWindow* window, Snake &snake, int &windowLength,int &windowHeight) {
	if (snake.touchingBody() || snake.outOfBounds(windowLength, windowHeight)) {
		window->close();
	}
}

static void checkEaten(Snake &snake, std::pair<int, int>& foodPos, int* score) {
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> lengthDist(0, 39);
	std::uniform_int_distribution<int> widthDist(0, 29);
	if (snake.getHead() == foodPos) {
		snake.grow();
		(*score)++;
		foodPos = { lengthDist(rng) * 20, widthDist(rng) * 20 };
		while (snake.touching(foodPos)) {
			foodPos = { lengthDist(rng) * 20, widthDist(rng) * 20 };
		}
		std::cout << "(" << foodPos.first << ", " << foodPos.second << ")" << "\n";
		
	}
}

void drawFood(sf::RenderWindow* window, std::pair<int, int> foodPos) {
	sf::RectangleShape foodBlock(sf::Vector2f(20, 20));
	foodBlock.setPosition(static_cast<float>(foodPos.first), static_cast<float>(foodPos.second));
	foodBlock.setFillColor(sf::Color::Red);
	window->draw(foodBlock);
}