/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Brick object
*
*	Copyright 2021 by 3-codiots
*/

#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>

class Brick : public sf::RectangleShape{
private:
	bool deleted;
	
	// item, hp, color
public:
	Brick(float w, float h, float x, float y);
};

#endif


