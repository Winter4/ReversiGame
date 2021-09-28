#include "../Headers/InfoBoard.h"

InfoBoard::InfoBoard(sf::RenderWindow* window, sf::Vector2f position, const sf::Font& font)
	: FontedEntity(window, position, font)
{
	text.setCharacterSize(30);
}

void InfoBoard::setString(const std::string& text) { this->text.setString(text); }
