#include "../Headers/Field.h"

Field::Field(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture, 
	const sf::Texture& chipsTexture, const sf::Texture& chipPhantomTexture)
	: TexturedEntity(window, position, texture),
	chipPhantom(window, {-100, -100}, chipPhantomTexture)
{
	cells = new Cell * *[FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; i++)
		cells[i] = new Cell*[FIELD_SIZE];

	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++) {
			// 25 - cells grid padding
			// 85 - one sprite width=height
			// 85 / 2 - to set the origin in the cell center
			cells[i][j] = new Cell(window, sf::Vector2f(25 + 85 * j + 85 / 2, 
				25 + 85 * i + 85 / 2) + sprite.getPosition(), chipsTexture);

			// debug chips displaying
			//cells[i][j]->set(Player::PLAYER_WHITE);
		}
}

void Field::draw() {
	TexturedEntity::draw();

	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			cells[i][j]->draw();

	chipPhantom.draw();
}

sf::FloatRect Field::getBounds() { return sprite.getGlobalBounds(); }

void Field::processCursor(sf::Vector2i cursorPosition) {

	if (sprite.getGlobalBounds().contains(sf::Vector2f(cursorPosition))) {

		sf::Vector2i allegedCell((cursorPosition.x - sprite.getPosition().x - 25) / 85, 
			(cursorPosition.y - sprite.getPosition().y - 25) / 85);

		if ((allegedCell.x >= 0 && allegedCell.x < FIELD_SIZE)
			&& (allegedCell.y >= 0 && allegedCell.y < FIELD_SIZE))
		{
			std::cout << "Alleged cell: " << allegedCell.x << "  " << allegedCell.y << std::endl;
			if (cells[allegedCell.y][allegedCell.x]->hovered(sf::Vector2f(cursorPosition)) 
				&& not (cells[allegedCell.y][allegedCell.x]->getFilling())) {

				chipPhantom.setState(true);
				chipPhantom.setPosition(cells[allegedCell.y][allegedCell.x]->getPosition());
				chipPhantom.setIndex(allegedCell);
			}
			else {
				chipPhantom.setState(false);
			}
		}
	}
	else {
		chipPhantom.setState(false);
	}
}

void Field::setChip(Player player) {
	if (chipPhantom.getState())
		if (not (cells[chipPhantom.getIndex().y][chipPhantom.getIndex().y]->getFilling())) {
			cells[chipPhantom.getIndex().y][chipPhantom.getIndex().x]->setChip(player);
			chipPhantom.setState(false);
		}
}