/*
 *	SW3 (SSE2034-41) Term Project
 *	
 *	Briefly explain : Declare Ball object
 *
 *	Copyright 2021 by 3-codiots
 */

#include "Ball.h"

Ball::Ball() : CircleShape(0){
	ball_speedX = 0;
	ball_speedY = 0;
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

void Ball::set_Ball_size(float ball_radius_){
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

void Ball::Ball_move(int screen_width, int screen_height, Paddle& p1, Paddle& p2){
	this->move(ball_speedX, ball_speedY);

	if(this->get_Ball_x() < 0){
		this->set_Ball_speedX(-ball_speedX);
	}
	else if(this->get_Ball_x() > screen_width){
		this->set_Ball_speedX(-ball_speedX);
	}

	if(this->get_Ball_y() < 0){
		this->set_Ball_speedY(-ball_speedY);
	}
	else if(this->get_Ball_y() > screen_height){
		this->set_Ball_speedY(-ball_speedY);
	}
	if(get_Ball_speedY()<0){
		if((this->get_Ball_y() - p1.get_Paddle_y() > 0) && (this->get_Ball_y() - p1.get_Paddle_y() < 5)){
			if((this->get_Ball_x() > p1.get_Paddle_x()) && (this->get_Ball_x() < p1.get_Paddle_x() + 96)){
				this->set_Ball_speedY(-ball_speedY);
			}
		}
		if((p2.get_Paddle_y() - this->get_Ball_y() > -7) && (p2.get_Paddle_y() - this->get_Ball_y() < -2)){
			if((this->get_Ball_x() > p2.get_Paddle_x()) && (this->get_Ball_x() < p2.get_Paddle_x() + 96)){
				this->set_Ball_speedY(-ball_speedY);
			}
		}

	}
	else{
		if((this->get_Ball_y() - p1.get_Paddle_y() > -7) && (this->get_Ball_y() - p1.get_Paddle_y() < -2)){
			if((this->get_Ball_x() > p1.get_Paddle_x()) && (this->get_Ball_x() < p1.get_Paddle_x() + 96)){
				this->set_Ball_speedY(-ball_speedY);
			}
		}
		if((p2.get_Paddle_y() - this->get_Ball_y() > 0) && (p2.get_Paddle_y() - this->get_Ball_y() < 5)){
			if((this->get_Ball_x() > p2.get_Paddle_x()) && (this->get_Ball_x() < p2.get_Paddle_x() + 96)){
				this->set_Ball_speedY(-ball_speedY);
			}
		}

	}
}
