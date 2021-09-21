#include "TexturedEntity.h"
#include "Cell.h"

#define FIELD_SIZE 8

class Field : public TexturedEntity {
private:
	sf::Texture chipsTexture;
	Cell*** cells;

	sf::Sprite cellHover;

public:
	Field(sf::RenderWindow* window, sf::Vector2f position, const sf::Texture& texture, 
		const sf::Texture& chipsTexture, const sf::Texture& cellHoverTexture);

	void draw();
	sf::FloatRect getBounds();
	void processCursor(sf::Vector2i cursorPosition);
};