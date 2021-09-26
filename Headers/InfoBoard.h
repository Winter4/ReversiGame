#pragma once
#include "FontedEntity.hpp"

class InfoBoard : public FontedEntity {
public:
	InfoBoard(sf::RenderWindow* window, sf::Vector2f position, const sf::Font& font);
};

