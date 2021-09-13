#pragma once
#include "../Headers/TexturedEntity.h"

TexturedEntity::TexturedEntity(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture)
	: Entity(window)
{
	sprite.setPosition(position);
	sprite.setTexture(texture);
}

void TexturedEntity::draw()
{
	window->draw(sprite);
}