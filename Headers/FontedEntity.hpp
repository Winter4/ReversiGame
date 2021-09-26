#pragma once
#include "Entity.h"

// 
class FontedEntity : public Entity {
protected:
	sf::Text text;

public:
	FontedEntity(sf::RenderWindow* window, sf::Vector2f position, const sf::Font& font);

	void virtual draw();
};