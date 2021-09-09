#include "../Headers/Game.h"

Game::Game() : window(sf::VideoMode(1400, 900), "Reversi") {



}

void Game::run() {

	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {

	sf::Event event;
	window.pollEvent(event);

	switch (event.type) {

	case sf::Event::Closed:
		window.close();
		break;

		
	}
}

void Game::update() {


}

void Game::render() {

	window.clear(sf::Color::Magenta);

	window.display();
}