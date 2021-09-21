#include "../Headers/Field.h"

Field::Field(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture, 
	const sf::Texture& chipsTexture, const sf::Texture& cellHoverTexture)
	: TexturedEntity(window, position, texture)
{
	cells = new Cell * *[FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; i++)
		cells[i] = new Cell*[FIELD_SIZE];

	cellHover.setTexture(cellHoverTexture);

	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++) {
			cells[i][j] = new Cell(window, sf::Vector2f(25 + 85 * j + 85 / 2, 
				25 + 85 * i + 85 / 2) + sprite.getPosition(), chipsTexture);
			cells[i][j]->set(Player::PLAYER_BLACK);
			
		}
	
}

void Field::draw() {
	TexturedEntity::draw();
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			cells[i][j]->draw();
}

sf::FloatRect Field::getBounds() { return sprite.getGlobalBounds(); }

void Field::processCursor(sf::Vector2i cursorPosition) {

	if (sprite.getGlobalBounds().contains(sf::Vector2f(cursorPosition))) {

		
	}
}