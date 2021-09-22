#include "../Headers/ChipPhantom.h"

ChipPhantom::ChipPhantom(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture)
	: TexturedEntity(window, position, texture)
{
	state = false;
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setColor(sf::Color::Red);

	index = { -1, -1 };
}

void ChipPhantom::draw() {
	if (state)
		TexturedEntity::draw();
}

void ChipPhantom::setPosition(sf::Vector2f position) { sprite.setPosition(position); }

void ChipPhantom::setIndex(sf::Vector2i index) { this->index = index; }

void ChipPhantom::setState(bool state) { this->state = state; }

bool ChipPhantom::getState() { return state; }

sf::Vector2i ChipPhantom::getIndex() { return index; }