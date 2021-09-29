#include "../Headers/Timer.h"

Timer::Timer(sf::RenderWindow* window, sf::Vector2f position, const sf::Font& font)
	: FontedEntity(window, position, font)
{
	startTime = 30;

	time = startTime;

	text.setFillColor(sf::Color::White);
	text.setCharacterSize(72);
}

void Timer::draw() {

	text.setString(std::to_string(time));

	if (time <= 5) text.setFillColor(sf::Color::Red);
	else text.setFillColor(sf::Color::White);

	window->draw(text);
}

int Timer::getTime() { return time; }

sf::Time Timer::getElapsedTime() { 
	
	sf::Time tmp = clock.getElapsedTime(); 
	return tmp;
}

void Timer::substractSecond() { 

	time--;
	clock.restart();
}

void Timer::refresh() {

	time = startTime;
}