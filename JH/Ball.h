/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Ball object
*
*	Copyright 2021 by 3-codiots
*/

#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball : public sf::CircleShape{
private:
	float ball_radius;
	float ball_speedX;
	float ball_speedY;
public:
	Ball();

	float get_Ball_radius();
	float get_Ball_x();
	float get_Ball_y();
	float get_Ball_speedX();
	float get_Ball_speedY();

	void set_Ball_size(float ball_radius_);
	void set_Ball_position(float ball_x_, float ball_y_);
	void set_Ball_speedX(float ball_speedX_);
	void set_Ball_speedY(float ball_speedX_);

	void Ball_move(int screen_width, int screen_height, Paddle& p1, Paddle& p2);
};

#endif


