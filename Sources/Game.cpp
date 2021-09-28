#include "../Headers/Game.h"

void Game::loadAssets() {
	texturesHolder.load(Textures::Background, "assets/textures/background.png");
	texturesHolder.load(Textures::Field, "assets/textures/field.png");
	texturesHolder.load(Textures::Chips, "assets/textures/chips.png");
	texturesHolder.load(Textures::CellHover, "assets/textures/cellhover.png");

	fontsHolder.load(Fonts::Gilroy, "assets/fonts/gilroy-regular.ttf");
}

void Game::chooseFirstPlayer() {

	infoBoard->setString("Player 1: press B or W button\nto choose your color.");

	render();

	while (currentPlayer == PLAYER_NONE) {
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
			currentPlayer = Player::PLAYER_BLACK;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			currentPlayer = Player::PLAYER_WHITE;
	}
}

std::string Game::getPlayerText() {

	std::string tmp;
	if (currentPlayer == Player::PLAYER_BLACK) tmp = "Black player";
	else if (currentPlayer == Player::PLAYER_WHITE) tmp = "White player";
	else throw new std::exception("Invalid current player: can't get info text.");

	return tmp;
}

void Game::move() {

	if (field->findAllowedCells(currentPlayer)) {

		infoBoard->setString(getPlayerText() + ", make your move!");
		wasSkipped = false;
	}
	else {
		// if no allowed cells were found, skip move
		infoBoard->setString(getPlayerText() + ", you can't move. \nPress S to skip!");
		render();

		gameOver = wasSkipped;

		if (not gameOver)
			while (true) {
				//std::cout << "LOOP  " << std::endl;
				if (sf::Keyboard::isKeyPressed((sf::Keyboard::S))) {

					wasSkipped = true;

					changePlayer();
					move();
					break;
				}
			}
	}
}

void Game::changePlayer() {

	currentPlayer = currentPlayer == Player::PLAYER_BLACK ? 
		Player::PLAYER_WHITE : Player::PLAYER_BLACK;
}

// ___________________________________________________________________

Game::Game() : window(sf::VideoMode(1400, 900), "Reversi") {

	gameOver = false;
	wasSkipped = false;

	loadAssets();
	
	background.setTexture(texturesHolder.get(Textures::Background));
	field = new Field(&window, { 520, 80 }, texturesHolder.get(Textures::Field), 
		texturesHolder.get(Textures::Chips), texturesHolder.get(Textures::CellHover));
	infoBoard = new InfoBoard(&window, { 75, 300 }, fontsHolder.get(Fonts::Gilroy));
	
	// field chips placing init
	currentPlayer = Player::PLAYER_NONE;
	chooseFirstPlayer();

	move();
}

// ____________________________________________________________________

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
		
		// displaying chip phantom if necessary
		field->processCursor(sf::Mouse::getPosition(window));
		break;

	case sf::Event::MouseButtonPressed:
		if (event.key.code == sf::Mouse::Button::Left) {

			if (field->setChip(currentPlayer)) {

				changePlayer();
				move();
			}
		}
	}
}

void Game::update() {

	system("cls");
	// debug displaying cursor position
	std::cout << "Mouse: " << sf::Mouse::getPosition(window).x << "  "
		<< sf::Mouse::getPosition(window).y << std::endl;

	std::cout << currentPlayer << std::endl;

	if (gameOver) {

		infoBoard->setString("GAME OVER");
		render();
		while (true);
	}
}

void Game::render() {

	window.clear();

	window.draw(background);
	field->draw();
	infoBoard->draw();

	window.display();
}