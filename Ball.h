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

class Ball : public sf::CircleShape{
private:
	const float BallSpeed = 2.5;
	float xSpeed;
	float ySpeed;
public:
	Ball(float r, float x, float y);
};

#endif


