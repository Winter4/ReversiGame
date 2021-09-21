#include "../Headers/Game.h"

void Game::loadAssets() {

	texturesHolder.load(Textures::Background, "assets/textures/background.png");
	texturesHolder.load(Textures::Field, "assets/textures/field.png");
	texturesHolder.load(Textures::Chips, "assets/textures/chips.png");
	texturesHolder.load(Textures::CellHover, "assets/textures/cellhover.png");
}

Game::Game() : window(sf::VideoMode(1400, 900), "Reversi") {

	loadAssets();
	
	background.setTexture(texturesHolder.get(Textures::Background));
	field = new Field(&window, { 520, 80 }, texturesHolder.get(Textures::Field), 
		texturesHolder.get(Textures::Chips), texturesHolder.get(Textures::CellHover));
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

	case sf::Event::MouseMoved:
		field->processCursor(sf::Mouse::getPosition(window));
			
		system("cls");
		std::cout << "Mouse: " << sf::Mouse::getPosition(window).x << "  " 
			<< sf::Mouse::getPosition(window).y << std::endl;
		break;
	}
}

void Game::update() {


}

void Game::render() {

	window.clear();

	window.draw(background);
	field->draw();

	window.display();
}