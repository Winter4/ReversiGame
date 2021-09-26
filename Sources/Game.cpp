#include "../Headers/Game.h"

void Game::loadAssets() {
	texturesHolder.load(Textures::Background, "assets/textures/background.png");
	texturesHolder.load(Textures::Field, "assets/textures/field.png");
	texturesHolder.load(Textures::Chips, "assets/textures/chips2.png");
	texturesHolder.load(Textures::CellHover, "assets/textures/cellhover.png");

	fontsHolder.load(Fonts::Gilroy, "assets/fonts/gilroy-regular.ttf");
}

void Game::chooseFirstPlayer() {

	Player firstPlayer = PLAYER_NONE;
	while (firstPlayer == PLAYER_NONE) {
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
	}
}

Game::Game() : window(sf::VideoMode(1400, 900), "Reversi") {

	loadAssets();
	
	background.setTexture(texturesHolder.get(Textures::Background));
	field = new Field(&window, { 520, 80 }, texturesHolder.get(Textures::Field), 
		texturesHolder.get(Textures::Chips), texturesHolder.get(Textures::CellHover));
	infoBoard = new InfoBoard(&window, { 75, 300 }, fontsHolder.get(Fonts::Gilroy));
	

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
		system("cls");
		// displaying chip phantom if necessary
		field->processCursor(sf::Mouse::getPosition(window));
			
		// debug displaying cursor position
		std::cout << "Mouse: " << sf::Mouse::getPosition(window).x << "  " 
			<< sf::Mouse::getPosition(window).y << std::endl;
		break;

	case sf::Event::MouseButtonPressed:
		if (event.key.code == sf::Mouse::Button::Left)
			field->setChip(Player::PLAYER_WHITE);
	}
}

void Game::update() {


}

void Game::render() {

	window.clear();

	window.draw(background);
	field->draw();
	infoBoard->draw();

	window.display();
}