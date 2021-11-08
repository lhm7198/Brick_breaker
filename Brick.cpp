/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Brick object
*
*	Copyright 2021 by 3-codiots
*/

#include "Brick.h"

Brick::Brick(float w, float h, float x, float y){
	setSize(sf::Vector2f(w, h));
	setFillColor(sf::Color(255, 0, 0));
	setPosition(x, y);

	deleted = false;
};

