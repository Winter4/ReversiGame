#include "../Headers/InfoBoard.h"

InfoBoard::InfoBoard(sf::RenderWindow* window, sf::Vector2f position, const sf::Font& font)
	: FontedEntity(window, position, font)
{
	text.setString("Player 1: press B or W button\nto choose your color.");
	text.setCharacterSize(30);
}

void InfoBoard::setString(const std::string& text) { this->text.setString(text); }
