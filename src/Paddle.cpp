/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Paddle object
*
*	Copyright 2021 by 3-codiots
*/

#include "Paddle.h"

Paddle::Paddle(float w, float h, float x, float y, float speed){
	xSpeed = speed;
	setSize(sf::Vector2f(w, h));
	setFillColor(sf::Color(100, 100, 100));
	setPosition(x, y);
};

float Paddle::get_Speed(){
	return xSpeed;
}
