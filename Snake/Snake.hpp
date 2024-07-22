/// Snake.hpp
#ifndef SNAKE_HPP // checks if SNEAKY_HPP is defined
#define SNAKE_HPP
#include <iostream>
#include <vector>
#include <utility> // For std::pair
#include <random>
class Snake {
public:

    Snake(); // Constructor
    int getLength(); // Method to get the length of the snake
    void move(); // Method to move the snake
    void setDirection(const std::string& newDirection); // Method to set the snake's direction
    void grow();
    const std::vector<std::pair<int, int>>& getBody(bool log) const;
    const std::pair<int, int> getHead() const;
    bool touchingBody();
    bool touching(std::pair<int, int> position);
    bool outOfBounds(int length, int width);
    std::string getDirection();
private:
    std::string direction = "DOWN";
    int length = 1;
    std::vector<std::pair<int, int>> snake_body;
    int speed = 20;
};

#endif // SNAKE_HPP