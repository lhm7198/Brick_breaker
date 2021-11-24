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
#include <vector>
#include "Paddle.h"
#include "Brick.h"

class Ball : public sf::CircleShape{
private:
	float ball_radius;
	float ball_speedX;
	float ball_speedY;
	float gap;
	bool active;
public:
	Ball();

	float get_Ball_radius();
	float get_Ball_x();
	float get_Ball_y();
	float get_Ball_speedX();
	float get_Ball_speedY();
	bool get_Ball_active();

	void set_Ball_size(float ball_radius_);
	void set_Ball_position(float ball_x_, float ball_y_);
	void set_Ball_speedX(float ball_speedX_);
	void set_Ball_speedY(float ball_speedX_);
	void set_Ball_active();
	void set_Ball_inactive();
	void set_Ball_color();

	void Ball_move();
};

#endif


