/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Brick object
*
*	Copyright 2021 by 3-codiots
*/

#include "Brick.h"

Brick::Brick(){
	brick_width = 0;
	brick_height = 0;
	deleted = false;
};

float Brick::get_Brick_width(){
	return brick_width;
}
float Brick::get_Brick_height(){
	return brick_height;
}
float Brick::get_Brick_x(){
	return this->getPosition().x;
}
float Brick::get_Brick_y(){
	return this->getPosition().y;
}

void Brick::set_Brick_size(float brick_width_, float brick_height_){
	this->brick_width=brick_width_;
	this->brick_height=brick_height_;
	this->setSize(sf::Vector2f(brick_width_, brick_height_));
	this->setFillColor(sf::Color(255, 0, 0));
}
void Brick::set_Brick_position(float brick_x_, float brick_y_){
	this->setPosition(brick_x_, brick_y_);
}
