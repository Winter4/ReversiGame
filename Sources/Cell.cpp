#include "../Headers/Cell.h"

Cell::Cell(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture)
	: TexturedEntity(window, position, texture)
{
	state = false;
	player = PLAYER_NONE;
	
	sprite.setScale({ 1.5, 1.5 });

	// the texture image is {2*x; x}
	// that's why the sprite origin width is divided 2 times 
	sprite.setOrigin(sprite.getLocalBounds().width / 2 / 2, sprite.getLocalBounds().height / 2);
}

void Cell::draw() {
	if (state)
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

void Cell::set(Player player) 
{
	switch (player) {

	case Player::PLAYER_NONE:
		throw std::exception("Chip should have the master (PLAYER_NONE in set() ).");
		break;

	// the texture is 90x45, so sprites are two squares
	// its squares left upper corners are in the following coords 
		// relatively to the texture
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

