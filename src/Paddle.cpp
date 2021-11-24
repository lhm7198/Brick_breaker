/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Paddle object
*
*	Copyright 2021 by 3-codiots
*/

#include "Paddle.h"

Paddle::Paddle(){
	paddle_width = 0;
	paddle_height = 0;
	paddle_speedX = 0;
	num_item1 = 0;
	num_item2 = 0;
	num_item3 = 0;
	item1_active = false;
	item2_active = false;
	item3_active = false;
};

float Paddle::get_Paddle_width(){
	return paddle_width;
}
float Paddle::get_Paddle_height(){
	return paddle_height;
}
float Paddle::get_Paddle_x(){
	return this->getPosition().x;
}
float Paddle::get_Paddle_y(){
	return this->getPosition().y;
}
float Paddle::get_Paddle_speedX(){
	return paddle_speedX;
}

void Paddle::set_Paddle_size(float paddle_width_, float paddle_height_){
	paddle_width = paddle_width_;
	paddle_height = paddle_height_;
	this->setSize(sf::Vector2f(paddle_width_, paddle_height_));
}
void Paddle::set_Paddle_position(float paddle_x_, float paddle_y_){
	this->setPosition(paddle_x_, paddle_y_);
}
void Paddle::set_Paddle_speedX(float paddle_speedX_){
	paddle_speedX = paddle_speedX_;
}
void Paddle::set_Paddle_color(){
	this->setFillColor(sf::Color(100, 100, 100));
	this->setOutlineThickness(0);
	if(item1_active){
		this->setOutlineThickness(1.25);
		this->setOutlineColor(sf::Color::Red);
	}
}

int Paddle::get_Paddle_item(int idx){
	switch(idx){
		case 1: return num_item1;
		case 2: return num_item2;
		case 3: return num_item3;
		default: break;
	}
}
bool Paddle::get_Paddle_item_work(int idx){
	switch(idx){
		case 1: return item1_active;
		case 2: return item2_active;
		case 3: return item3_active;
		default: break;
	}
}
void Paddle::set_Paddle_item(int idx, int num){
	switch(idx){
		case 1: num_item1 = num; break;
		case 2: num_item2 = num; break;
		case 3: num_item3 = num; break;
		default: break;
	}
}
void Paddle::set_Paddle_item_active(int idx){
	switch(idx){
		case 1: item1_active = true; break;
		case 2: item2_active = true; break;
		case 3: item3_active = true; break;
		default: break;
	}
}
void Paddle::set_Paddle_item_inactive(int idx){
	switch(idx){
		case 1: item1_active = false; break;
		case 2: item2_active = false; break;
		case 3: item3_active = false; break;
		default: break;
	}
}

void Paddle::Paddle_move(int screen_width, int screen_height){
	if(paddle_speedX > 0){
		if(this->get_Paddle_x() < screen_width - paddle_width){
			this->move(paddle_speedX, 0);
		}
	}
	if(paddle_speedX < 0){
		if(this->get_Paddle_x() > 0){
			this->move(paddle_speedX, 0);
		}
	}
}
