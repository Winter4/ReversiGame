#include "../Headers/Game.h"

void Game::loadAssets() {
	texturesHolder.load(Textures::Background, "assets/textures/background.png");
	texturesHolder.load(Textures::Field, "assets/textures/field.png");
	texturesHolder.load(Textures::Chips, "assets/textures/chips.png");
	texturesHolder.load(Textures::CellHover, "assets/textures/cellhover.png");

	fontsHolder.load(Fonts::Gilroy, "assets/fonts/gilroy-regular.ttf");
}

void Game::chooseFirstPlayer() {

	render();

	while (currentPlayer == PLAYER_NONE) {
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
			currentPlayer = Player::PLAYER_BLACK;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			currentPlayer = Player::PLAYER_WHITE;
	}
}

std::string Game::getInfoText() {

	std::string tmp;
	if (currentPlayer == Player::PLAYER_BLACK) tmp = "Black player";
	else if (currentPlayer == Player::PLAYER_WHITE) tmp = "White player";
	else throw new std::exception("Invalid current player: can't get info text.");

	return tmp;
}

void Game::changePlayer() {

	if (currentPlayer == Player::PLAYER_BLACK) currentPlayer = Player::PLAYER_WHITE;
	else currentPlayer = Player::PLAYER_BLACK;
	
	infoBoard->setString(getInfoText() + ", make your move!");

	field->findAllowedCells(currentPlayer);
}

Game::Game() : window(sf::VideoMode(1400, 900), "Reversi") {

	gameOver = false;

	loadAssets();
	
	background.setTexture(texturesHolder.get(Textures::Background));
	field = new Field(&window, { 520, 80 }, texturesHolder.get(Textures::Field), 
		texturesHolder.get(Textures::Chips), texturesHolder.get(Textures::CellHover));
	infoBoard = new InfoBoard(&window, { 75, 300 }, fontsHolder.get(Fonts::Gilroy));
	
	// field chips placing init
	currentPlayer = Player::PLAYER_NONE;
	chooseFirstPlayer();
	infoBoard->setString(getInfoText() + ", make your move!");
	field->findAllowedCells(currentPlayer);
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
		if (event.key.code == sf::Mouse::Button::Left) {
			bool wasSet = field->setChip(currentPlayer);
			if (wasSet) changePlayer();
		}
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