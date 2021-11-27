/*
 *	SW3 (SSE2034-41) Term Project
 *	
 *	Briefly explain : Declare Ball object
 *
 *	Copyright 2021 by 3-codiots
 */

#include "Ball.h"

Ball::Ball() : CircleShape(0){
	ball_radius = 0;
	ball_speedX = 0;
	ball_speedY = 0;
	active = false;
};

float Ball::get_Ball_radius(){
	return this->getRadius();
}
float Ball::get_Ball_x(){
	return this->getPosition().x;
}
float Ball::get_Ball_y(){
	return this->getPosition().y;
}
float Ball::get_Ball_speedX(){
	return ball_speedX;
}
float Ball::get_Ball_speedY(){
	return ball_speedY;
}
bool Ball::get_Ball_active(){
	return active;
}

void Ball::set_Ball_size(float ball_radius_){
	ball_radius = ball_radius_;
	this->setRadius(ball_radius_);
}
void Ball::set_Ball_position(float ball_x_, float ball_y_){
	this->setPosition(ball_x_, ball_y_);
}
void Ball::set_Ball_speedX(float ball_speedX_){
	ball_speedX = ball_speedX_;
}
void Ball::set_Ball_speedY(float ball_speedY_){
	ball_speedY = ball_speedY_;
}
void Ball::set_Ball_active(){
	active = true;
}
void Ball::set_Ball_inactive(){
	active = false;
}
void Ball::set_Ball_color(){
	if(active) this->setFillColor(sf::Color::Red);
	else this->setFillColor(sf::Color::White);
}

void Ball::Ball_move(){
	this->move(ball_speedX, ball_speedY);
}
