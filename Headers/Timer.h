#pragma once
#include "FontedEntity.hpp"

class Timer : public FontedEntity {

	int startTime;

	sf::Clock clock;
	int time;

public:
	Timer(sf::RenderWindow* window, sf::Vector2f position, const sf::Font& font);

	void draw();
	int getTime();
	sf::Time getElapsedTime();
	void substractSecond();
	void refresh();
};