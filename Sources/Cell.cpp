#include "../Headers/Cell.h"

Cell::Cell(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture)
	: TexturedEntity(window, position, texture)
{
	filled = false;
	player = PLAYER_NONE;
	
	sprite.setScale({ 0.7, 0.7 });

	// the texture image is {2*x; x}
	// that's why the sprite origin width is divided 2 times 
	sprite.setOrigin(sprite.getLocalBounds().width / 2 / 2, sprite.getLocalBounds().height / 2);
}

void Cell::draw() {
	if (filled)
		TexturedEntity::draw();

	// sprite origin debug
	/*
	sf::RectangleShape dot;
	dot.setPosition(sprite.getPosition());
	dot.setSize({ 5, 5 });
	dot.setFillColor(sf::Color::Red);
	window->draw(dot);
	*/
}

void Cell::setChip(Player player) 
{
	switch (player) {

	case Player::PLAYER_NONE:
		throw std::exception("Chip should have the master (PLAYER_NONE in set() ).");
		break;

	// the texture is 170x85, so sprites are two squares
	// its squares left upper corners are in the following coords 
		// relatively to the texture
	case Player::PLAYER_BLACK:
		sprite.setTextureRect(sf::IntRect(0, 0, 85, 85));
		filled = true;
		break;

	case Player::PLAYER_WHITE:
		sprite.setTextureRect(sf::IntRect(85, 0, 85, 85));
		filled = true;
		break;
	}
	

}

bool Cell::contains(sf::Vector2f point) { return sprite.getGlobalBounds().contains(point); }

sf::Vector2f Cell::getPosition() { return sprite.getPosition(); }

bool Cell::hovered(sf::Vector2f point) { 
	// sprite.getPosition() - {85/2; 85/2} =  cell left upper corner
	// cell is 85x85
	return sf::FloatRect(sprite.getPosition().x - 85 / 2, sprite.getPosition().y - 85 / 2, 85, 85).contains(point);
}

bool Cell::getFilling() { return filled; }
