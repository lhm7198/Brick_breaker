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
	// const variable
	const int BRICKS_PER_ROW = 12;
	const float BALL_RADIUS = 4;
	const float PADDLE_SPEED = 7.5;
	
	// variable
	float gap;
	int screen_width;
	int screen_height;
	bool is_start_page;

/*	// Players
	Player player1;
	Player player2;
*/
	// Bricks
	float brick_width;
	float brick_height;
	std::vector<Brick> p1_bricks;
	std::vector<Brick> p2_bricks;

	// Ball
	float ball_radius;
	std::vector<Ball> balls;

	// Paddle
	float paddle_width;
	float paddle_height;
	float p1_paddle_speed;
	float p2_paddle_speed;
	std::vector<Paddle> p1_paddles;
	std::vector<Paddle> p2_paddles;

	// Event
	sf::Event event;

	// Window
	sf::RenderWindow window;
public:
	Game(int w, int h);

	void gameStart();
	
	void gameRunning();

	void receiveKeyinputs();

	void draw();
};

#endif
