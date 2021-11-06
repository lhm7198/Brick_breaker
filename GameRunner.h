/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare game object
*
*	Copyright 2021 by 3-codiots
*/

#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include <SFML/Graphics.hpp>
//#include "Brick.h"

class Game{
private:
	int screen_width;
	int screen_height;

	bool is_start_page;
/*	// Players
	Player player1;
	Player player2;

	// Bricks
	vector<Brick> bricks;
*/
	// Event
	sf::Event event;

	// Window
	sf::RenderWindow window;
public:
	Game(int w, int h);

	void gameStart();
};

#endif
