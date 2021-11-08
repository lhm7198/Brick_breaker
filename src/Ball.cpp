/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Ball object
*
*	Copyright 2021 by 3-codiots
*/

#include "Ball.h"

Ball::Ball(float r, float x, float y) : CircleShape(r){
	setFillColor(sf::Color::White);
	setPosition(x, y);
};

