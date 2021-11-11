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
	is_paddle_move_right = false;
	is_paddle_move_left = false;
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
	this->setFillColor(sf::Color(100, 100, 100));
}
void Paddle::set_Paddle_position(float paddle_x_, float paddle_y_){
	this->setPosition(paddle_x_, paddle_y_);
}
void Paddle::set_Paddle_speedX(float paddle_speedX_){
	paddle_speedX = paddle_speedX_;
}
void Paddle::set_Paddle_move_right(bool is_paddle_move_right_){
	is_paddle_move_right = is_paddle_move_right_;
}
void Paddle::set_Paddle_move_left(bool is_paddle_move_left_){
	is_paddle_move_left = is_paddle_move_left_;
}

void Paddle::Paddle_move(int screen_width, int screen_height){
	if(is_paddle_move_right){
		if(this->get_Paddle_x() < screen_width - this->get_Paddle_width()){
			this->move(paddle_speedX, 0);
		}
	}
	else if(is_paddle_move_left){
		if(this->get_Paddle_x() > 0){
			this->move(-paddle_speedX, 0);
		}
	}
}
