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

	// start chips placing
	cells[3][3]->setChip(Player::PLAYER_BLACK);
	cells[4][3]->setChip(Player::PLAYER_WHITE);
	cells[3][4]->setChip(Player::PLAYER_WHITE);
	cells[4][4]->setChip(Player::PLAYER_BLACK);
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

bool Field::setChip(Player player) {
	if (chipPhantom.getState())
		if (not (cells[chipPhantom.getIndex().y][chipPhantom.getIndex().x]->getFilling())) {

			cells[chipPhantom.getIndex().y][chipPhantom.getIndex().x]->setChip(player);
			chipPhantom.setState(false);

			return true;
		}
	return false;
}

bool Field::checkLine(sf::Vector2i cell, sf::Vector2i direction, Player player) {

	//assert(not (cell.x == 4 and cell.y == 1));

	// bug catching
	if (player == PLAYER_NONE) throw new std::exception("Cell can't has a PLAYER_NONE owner.");

	// another player color
	Player oppositePlayer = (player == Player::PLAYER_BLACK) ? PLAYER_WHITE : PLAYER_BLACK;

	// throwed exception means out_of_board or 
	try {
		// in board check
		if (not ((cell.y + direction.y >= 0 and cell.y + direction.y < FIELD_SIZE)
			and (cell.x + direction.x >= 0 and cell.x + direction.x < FIELD_SIZE)))
		{
			throw std::exception();
		}

		if (cells[cell.y + direction.y][cell.x + direction.x]->getPlayer() == oppositePlayer) {

			// checking the line until the player chip or the board end
			for (int i = cell.y + direction.y, j = cell.x + direction.x;
				cells[i][j]->getPlayer() != Player::PLAYER_NONE;
				i += direction.y, j += direction.x)
			{
				// in board check
				if (not ((i >= 0 and i < FIELD_SIZE)
					and (j >= 0 and j < FIELD_SIZE)))
				{
					throw std::exception();
				}

				if (cells[i][j]->getPlayer() == player) 
					return true;
			}
		}
	}
	catch (std::exception exc) {}

	return false;
}

void Field::findAllowedCells(Player player) {

	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++) {
			
			if (not (cells[i][j]->getFilling()))
				cells[i][j]->setAllowance(
					checkLine({ j, i }, { 0, 1 }, player) // south
					or checkLine({ j, i }, { 1, 1 }, player) // south-east
					or checkLine({ j, i }, { 1, 0 }, player) // east
					or checkLine({ j, i }, { 1, -1 }, player) // north-east
					or checkLine({ j, i }, { 0, -1 }, player) // north
					or checkLine({ j, i }, { -1, -1 }, player) // north-west
					or checkLine({ j, i }, { -1, 0 }, player) // west
					or checkLine({ j, i }, { -1, 1 }, player) // south-west
				);

			// debug
			//assert(not (cells[i][j]->getAllowance()));
		}
}