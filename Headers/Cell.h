#pragma once
#include "TexturedEntity.h"
#include "Resources-enums.h"

class Cell : TexturedEntity {
private:
	bool filled;
	Player player;

	bool allowedToSet;

public:
	Cell(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture);

	void draw();
	void setChip(Player player);
	bool contains(sf::Vector2f point);
	sf::Vector2f getPosition();
	bool hovered(sf::Vector2f point);

	bool getFilling();
	Player getPlayer();

	// returns result allowance
	void setAllowance(bool allowance);
	bool getAllowance();
};
