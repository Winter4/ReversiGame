#include "TexturedEntity.h"
#include "Cell.h"
#include "ChipPhantom.h"
#include <iostream>

#include <cassert>

#define FIELD_SIZE 8

class Field : public TexturedEntity {
private:
	//sf::Texture chipsTexture;
	Cell*** cells;

	ChipPhantom chipPhantom;

public:
	Field(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture, 
		const sf::Texture& chipsTexture, const sf::Texture& cellHoverTexture);

	void draw();
	sf::FloatRect getBounds();
	// diplay chip phantom if necessary
	void processCursor(sf::Vector2i cursorPosition);
	bool setChip(Player player);

	bool checkLine(sf::Vector2i cell, sf::Vector2i direction, Player player);
	void findAllowedCells(Player player);

	void reverse(Player player, sf::Vector2i cell);
	void reverseRow(Player player, sf::Vector2i cell, sf::Vector2i direction);
};