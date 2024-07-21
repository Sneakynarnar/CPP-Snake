#include <iostream>
#include <SFML/Graphics.hpp>

void updatePlayer(sf::RectangleShape* rect);
int main() {
	std::string direction = "DOWN";
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
	sf::Event event;
	sf::RectangleShape rectangle(sf::Vector2f(20, 20));
	rectangle.setFillColor(sf::Color::Green);
	window.setFramerateLimit(15);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					direction = "UP";
					break;

				case sf::Keyboard::A:
					direction = "LEFT";
					break;
				case sf::Keyboard::D:
					direction = "RIGHT";
					break;
				case sf::Keyboard::S:
					direction = "DOWN";
					break;
				};
			};
		};
		window.clear();
		updatePlayer(&rectangle, &direction);
		window.draw(rectangle);
		window.display();
	}
}


	void updatePlayer(sf::RectangleShape *rect, std::string *direction) {
	sf::Vector2f directionVector = sf::
	if (direction == "Down")
	rect->move(sf::Vector2f(0, 10));
}