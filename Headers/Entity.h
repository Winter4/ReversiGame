#pragma once
#include <SFML/Graphics.hpp>

// 
class Entity {
protected:
	sf::RenderWindow* window;

public:
	Entity(sf::RenderWindow* window);

	void virtual draw() = 0;
};