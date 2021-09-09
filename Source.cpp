#include <SFML/Graphics.hpp>
#include "Headers/Game.h"
#include <time.h>

int main()
{
	srand(time(NULL));

	Game game;
	game.run();

}