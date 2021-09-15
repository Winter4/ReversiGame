#pragma once
#include "TexturedEntity.h"
#include "Resources-enums.h"

class Cell : TexturedEntity {
private:
	bool state;
	Player player;

public:
	Cell(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture);

	void draw();
	void set(Player player);
};
