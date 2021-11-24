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
#include <cstdlib> // rand()
#include <ctime> // time()
#include <cmath> // abs()
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"

class Game{
private:
	// initial value
	const int BRICKS_PER_ROW = 10;
	const int BRICKS_PER_COL = 3;
	const float BALL_RADIUS = 6;
	const float PADDLE_SPEED = 5.0;
	const float BALL_SPEED = 5.0;
	
	// variable
	int screen_width;
	int screen_height;
	bool is_start_page;
	bool is_game_start;
	bool is_game_end;

	// Bricks
	float gap;
	std::vector<Brick> p1_b;
	std::vector<Brick> p2_b;

	// Paddle
	Paddle p1;
	Paddle p2;
	bool p1_item2_timer;
	bool p1_item3_timer;
	bool p2_item2_timer;
	bool p2_item3_timer;

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

	void ball_wall_collision();
	void ball_paddle_collision();
	void ball_brick_collision(Ball &ball);

	void p1_get_item(Brick &brick);
	void p2_get_item(Brick &brick);
};

#endif
