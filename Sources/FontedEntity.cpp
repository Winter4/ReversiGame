#pragma once
#include "../Headers/FontedEntity.hpp"

FontedEntity::FontedEntity(sf::RenderWindow* window, sf::Vector2f position, const sf::Font& font)
	: Entity(window)
{
	text.setPosition(position);
	text.setFont(font);
}

void FontedEntity::draw()
{
	window->draw(text);
}