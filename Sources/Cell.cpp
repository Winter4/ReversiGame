#include "../Headers/Cell.h"

Cell::Cell(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture)
	: TexturedEntity(window, position, texture)
{
	filled = false;
	player = PLAYER_NONE;

	allowedToSet = false;
	
	sprite.setScale({ 0.7, 0.7 });

	// the texture image is {3*x; x}
	// that's why the sprite origin is divided 3 and 2 times
	sprite.setOrigin(sprite.getLocalBounds().width / 3 / 2, sprite.getLocalBounds().height / 2);
}

void Cell::draw() {
	if (allowedToSet or filled)
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
		break;

	case Player::PLAYER_WHITE:
		sprite.setTextureRect(sf::IntRect(85, 0, 85, 85));
		break;
	}

	this->player = player;
	filled = true;
}

bool Cell::contains(sf::Vector2f point) { return sprite.getGlobalBounds().contains(point); }

sf::Vector2f Cell::getPosition() { return sprite.getPosition(); }

bool Cell::hovered(sf::Vector2f point) { 
	// sprite.getPosition() - {85/2; 85/2} =  cell left upper corner
	// cell is 85x85
	return sf::FloatRect(sprite.getPosition().x - 85 / 2, sprite.getPosition().y - 85 / 2, 85, 85).contains(point);
}

bool Cell::getFilling() { return filled; }

Player Cell::getPlayer() { return player; }

void Cell::setAllowance(bool allowance) { 

	allowedToSet = allowance; 

	if (allowedToSet) sprite.setTextureRect(sf::IntRect(170, 0, 85, 85));
	else sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

bool Cell::getAllowance() { return allowedToSet; }
