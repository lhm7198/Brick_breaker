/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Paddle object
*
*	Copyright 2021 by 3-codiots
*/

#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle : public sf::RectangleShape{
private:
	float xSpeed;
public:
	Paddle(float w, float h, float x, float y, float speed);
	float get_Speed();
};

#endif


