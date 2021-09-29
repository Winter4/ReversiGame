#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceHolder.hpp"
#include "Resources-enums.h"
#include "Field.h"
#include "InfoBoard.h"
#include "Timer.h"

class Game {
private:
	sf::RenderWindow window;

	ResourceHolder<sf::Texture, Textures::ID> texturesHolder;
	ResourceHolder<sf::Font, Fonts::ID> fontsHolder;

	sf::Sprite background;
	Field* field;
	InfoBoard* infoBoard;
	Timer* timer;

	Player currentPlayer;

	bool gameOver;
	bool wasSkipped;

private:
	void chooseFirstPlayer();
	std::string getPlayerText();
	void move();
	void changePlayer();

public:
	Game();

	//
	void run();

private:
	// 
	void loadAssets();

	// 
	void processEvents();
	// 
	void update();
	// 
	void render();
};

