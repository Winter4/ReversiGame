#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceHolder.hpp"
#include "Resources-enums.h"

class Game {
private:
	sf::RenderWindow window;

	ResourceHolder<sf::Texture, Textures::ID> texturesHolder;

	sf::Sprite background;

public:
	Game();

	//
	void run();

public:
	// 
	void loadAssets();

	// 
	void processEvents();
	// 
	void update();
	// 
	void render();

	// 
	void reset();
};

