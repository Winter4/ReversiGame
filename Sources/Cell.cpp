#include "../Headers/Cell.h"

Cell::Cell(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture)
	: TexturedEntity(window, position, texture)
{
	state = false;
	player = PLAYER_NONE;
	
	sprite.setScale({ 1.8, 1.8 });
}

void Cell::draw() {
	if (state)
		TexturedEntity::draw();
}

void Cell::set(Player player) 
{
	switch (player) {

	case Player::PLAYER_NONE:
		throw std::exception("Chip should have the master (PLAYER_NONE in set() ).");
		break;

	case Player::PLAYER_BLACK:
		sprite.setTextureRect(sf::IntRect(0, 0, 45, 45));
		state = true;
		break;

	case Player::PLAYER_WHITE:
		sprite.setTextureRect(sf::IntRect(45, 0, 45, 45));
		state = true;
		break;
	}
	

}