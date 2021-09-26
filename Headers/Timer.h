#pragma once
#include "FontedEntity.hpp"

class Timer : public FontedEntity {

public:
	Timer(sf::RenderWindow* window, sf::Vector2f position, const sf::Font& font);
};