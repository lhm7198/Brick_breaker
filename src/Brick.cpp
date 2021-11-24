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
	brick_hp = 0;
	item = 0;
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
int Brick::get_Brick_hp(){
	return brick_hp;
}
int Brick::get_Brick_item(){
	return item;
}

void Brick::set_Brick_size(float brick_width_, float brick_height_){
	brick_width=brick_width_;
	brick_height=brick_height_;
	this->setSize(sf::Vector2f(brick_width_, brick_height_));
}
void Brick::set_Brick_position(float brick_x_, float brick_y_){
	this->setPosition(brick_x_, brick_y_);
}
void Brick::set_Brick_hp(int brick_hp_){
	brick_hp = brick_hp_;
}
void Brick::set_Brick_color(){
	this->setFillColor(sf::Color(255, 120*(3-brick_hp), 0));
	if(item){
		this->setOutlineThickness(1.25);
		this->setOutlineColor(sf::Color::Cyan);
	}
}
void Brick::set_Brick_item(int item_){
	item = item_;	
}
