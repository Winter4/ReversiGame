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
		if (field->checkFreeCells()) {
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

	if (currentPlayer == Player::PLAYER_BLACK) chipShower.setTextureRect(sf::IntRect(0, 0, 85, 85));
	else chipShower.setTextureRect(sf::IntRect(85, 0, 85, 85));

	timer->refresh();
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
	infoBoard = new InfoBoard(&window, { 60, 300 }, fontsHolder.get(Fonts::Gilroy));
	timer = new Timer(&window, { 230, 450 }, fontsHolder.get(Fonts::Gilroy));

	chipShower.setTexture(texturesHolder.get(Textures::Chips));
	chipShower.setTextureRect(sf::IntRect(0, 0, 0, 0));
	chipShower.setPosition({ 230, 160 });
	
	
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

	// _____________ DEBUG _____________
	system("cls");
	// debug displaying cursor position
	std::cout << "Mouse: " << sf::Mouse::getPosition(window).x << "  "
		<< sf::Mouse::getPosition(window).y << std::endl;

	std::cout << currentPlayer << std::endl;
	// _____________ DEBUG _____________

	// 0 seconds = game over
	if (timer->getTime() <= 0) {

		timer->refresh();
		changePlayer();
		move();
	}

	if (timer->getElapsedTime() >= sf::seconds(1))
		timer->substractSecond();


	gameOver = gameOver ? true : not (field->checkFreeCells());


	// GAME OVER
	if (gameOver) {

		int blackNumber = field->calcChips(Player::PLAYER_BLACK);
		int whiteNumber = field->calcChips(Player::PLAYER_WHITE);

		if (blackNumber > whiteNumber) {
			infoBoard->setString("BLACK WINS \n" + std::to_string(blackNumber)
				+ " > " + std::to_string(whiteNumber));
		}
		else if (whiteNumber > blackNumber) {
			infoBoard->setString("WHITE WINS \n" + std::to_string(whiteNumber)
			+ " > " + std::to_string(blackNumber));
		}
		else {
			infoBoard->setString("DRAW! NOONE WINS \n" + std::to_string(blackNumber)
				+ " = " + std::to_string(whiteNumber));
		}

		chipShower.setTextureRect(sf::IntRect(0, 0, 0, 0));

		render();
		while (true) {

			sf::Event event;
			window.pollEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}

void Game::render() {

	window.clear();

	window.draw(background);
	field->draw();
	infoBoard->draw();
	timer->draw();
	window.draw(chipShower);

	window.display();
}