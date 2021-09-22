#pragma once

#include "TexturedEntity.h"

class ChipPhantom : public TexturedEntity {
private:
	bool state;
	sf::Vector2i index;

public:
	ChipPhantom(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture);
	void draw() override;
	void setPosition(sf::Vector2f position);
	void setIndex(sf::Vector2i index);
	void setState(bool state);

	bool getState();
	sf::Vector2i getIndex();
};
