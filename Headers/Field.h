#include "TexturedEntity.h"

class Field : public TexturedEntity {
public:
	Field(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture);
};