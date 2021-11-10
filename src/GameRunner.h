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
#include <vector>
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"

class Game{
private:
	// initial value
	const int BRICKS_PER_ROW = 12;
	const float BALL_RADIUS = 6;
	const float PADDLE_SPEED = 7.5;
	const float BALL_SPEED = 5.0;
	
	// variable
	int screen_width;
	int screen_height;
	bool is_start_page;
	bool is_game_start;

/*	// Players
	Player player1;
	Player player2;
*/
	// Bricks
	float gap;
	int p1_bricks_num;
	int p2_bricks_num;
	std::vector<Brick> p1_bricks;
	std::vector<Brick> p2_bricks;

	// Paddle
	std::vector<Paddle> p1_paddle;
	std::vector<Paddle> p2_paddle;

	// Ball
	std::vector<Ball> balls;

	// Event
	sf::Event event;

	// Window
	sf::RenderWindow window;
public:
	Game(int w, int h);

	void gameStart();
	void gameRunning();
	void receiveKeyinputs();
	void object_draw();
};

#endif
