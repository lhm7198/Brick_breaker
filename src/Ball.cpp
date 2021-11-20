/*
 *	SW3 (SSE2034-41) Term Project
 *	
 *	Briefly explain : Declare Ball object
 *
 *	Copyright 2021 by 3-codiots
 */

#include "Ball.h"
#include <math.h>

Ball::Ball() : CircleShape(0){
	ball_radius = 0;
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

void Ball::Ball_move(int screen_width, int screen_height, Paddle &p1, Paddle &p2, std::vector<Brick> &p1_b, std::vector<Brick> &p2_b){
	this->move(ball_speedX, ball_speedY);

	// wall
	if(get_Ball_x() - ball_radius < 0){ // left collision
		set_Ball_speedX(-ball_speedX);
		
	}
	else if(get_Ball_x() + 2*ball_radius >= screen_width){ // right collision
		set_Ball_speedX(-ball_speedX);
	}
	if(get_Ball_y() - ball_radius < 0){ // topside collision
		set_Ball_speedY(-ball_speedY);
		set_Ball_speedX(0);
		set_Ball_speedY(0);
	}
	else if(get_Ball_y() + 2*ball_radius >= screen_height){ // downside collision
		set_Ball_speedY(-ball_speedY);
		set_Ball_speedX(0);
		set_Ball_speedY(0);
	}

	// paddle
	if(get_Ball_speedY() < 0){ // when ball moves down to top
		if(this->get_Ball_y() - p1.get_Paddle_y() > p1.get_Paddle_height() && this->get_Ball_y() - p1.get_Paddle_y() < p1.get_Paddle_height() + 5){
			if(this->get_Ball_x() + this->ball_radius > p1.get_Paddle_x() && this->get_Ball_x() - this->ball_radius < p1.get_Paddle_x() + p1.get_Paddle_width()){ // collide with p1_paddle
				this->set_Ball_speedY(-ball_speedY);
			}
		}
		if(this->get_Ball_y() - p2.get_Paddle_y() > p2.get_Paddle_height() && this->get_Ball_y() - p2.get_Paddle_y() < p2.get_Paddle_height() + 5){ // collide with p2_paddle
			if(this->get_Ball_x() + this->ball_radius > p2.get_Paddle_x() && this->get_Ball_x() - this->ball_radius < p2.get_Paddle_x() + p2.get_Paddle_width()){
				this->set_Ball_speedY(-ball_speedY);
			}
		}

	}
	else{ // when ball moves top to down
		if(p1.get_Paddle_y() - this->get_Ball_y() > 1.5*this->ball_radius && p1.get_Paddle_y() - this->get_Ball_y() < 1.5*this->ball_radius + 5){ // collide with p1_paddle
			if(this->get_Ball_x() + 2*this->ball_radius > p1.get_Paddle_x() && this->get_Ball_x() < p1.get_Paddle_x() + p1.get_Paddle_width()){
				this->set_Ball_speedY(-ball_speedY);
				
			}
		}
		if(p2.get_Paddle_y() - this->get_Ball_y() > 1.5*this->ball_radius && p2.get_Paddle_y() - this->get_Ball_y() < 1.5*this->ball_radius + 5){ // collide with p2_paddle
			if(this->get_Ball_x() + 2*this->ball_radius > p2.get_Paddle_x() && this->get_Ball_x() < p2.get_Paddle_x() + p2.get_Paddle_width()){
				this->set_Ball_speedY(-ball_speedY);
			}
		}

	}

	// brick
	for(int i=0; i<p1_b.size(); i++){
		// p1_brick
		if(p1_b[i].get_Brick_deleted() == false){
			if(get_Ball_speedY() < 0){ // collide with p1_bricks downside
				if(get_Ball_y() - p1_b[i].get_Brick_y() > 0.7*p1_b[i].get_Brick_height() && get_Ball_y() - p1_b[i].get_Brick_y() < 0.7*p1_b[i].get_Brick_height() + 5){
					if(get_Ball_x() + ball_radius >= p1_b[i].get_Brick_x() && get_Ball_x() < p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width()){
						set_Ball_speedY(-ball_speedY);
						p1_b[i].set_Brick_deleted();
					}
				}
			}
			else{ // collide with p1_bricks topside
				if(p1_b[i].get_Brick_y() - get_Ball_y() > 0.7*p1_b[i].get_Brick_height() && p1_b[i].get_Brick_y() - get_Ball_y() < 0.7*p1_b[i].get_Brick_height() + 5){
					if(get_Ball_x() + ball_radius >= p1_b[i].get_Brick_x() && get_Ball_x() < p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width()){
						set_Ball_speedY(-ball_speedY);
						p1_b[i].set_Brick_deleted();
					}
				}
			}
			if(get_Ball_speedX() > 0){ // collide with p1_bricks leftside
				if(get_Ball_x() + ball_radius >= p1_b[i].get_Brick_x() && get_Ball_x() + ball_radius < p1_b[i].get_Brick_x() + 5){	
					if(get_Ball_y() >= p1_b[i].get_Brick_y() && get_Ball_y() < p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height()){
						set_Ball_speedX(-ball_speedX);
						p1_b[i].set_Brick_deleted();
					}
				}
			}
			else{ // collide with p1_bricks rightside
				if(get_Ball_x() - ball_radius > p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width() && get_Ball_x() - ball_radius < p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width() + 5){
					if(get_Ball_y() >= p1_b[i].get_Brick_y() && get_Ball_y() < p1_b[i].get_Brick_y()+p1_b[i].get_Brick_height()){
						set_Ball_speedX(-ball_speedX);
						p1_b[i].set_Brick_deleted();
					}
				}
			}
			//if(get_Ball_speedX() > 0){ // collide with p1_bricks leftside
			//	if(get_Ball_x() + ball_radius >= p1_b[i].get_Brick_x() - 5 && get_Ball_x() + ball_radius < p1_b[i].get_Brick_x()){	
			//		if(get_Ball_y() - ball_radius >= p1_b[i].get_Brick_y() && get_Ball_y() + ball_radius < p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height()){
			//			set_Ball_speedX(-ball_speedX);
			//			p1_b[i].set_Brick_deleted();
			//		}
			//	}
			//}
			//else{ // collide with p1_bricks rightside
			//	if(get_Ball_x() - ball_radius > p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width() && get_Ball_x() - ball_radius < p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width() + 5){
			//		if(get_Ball_y() - ball_radius >= p1_b[i].get_Brick_y() && get_Ball_y() + ball_radius < p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height()){
			//			set_Ball_speedX(-ball_speedX);
			//			p1_b[i].set_Brick_deleted();
			//		}
			//	}
			//}
		}
		// p2_brick
		if(p2_b[i].get_Brick_deleted() == false){
			if(get_Ball_speedY() < 0){ // collide with p2_bricks downside
				if(this->get_Ball_y() - p2_b[i].get_Brick_y() > 0.7*p2_b[i].get_Brick_height() && this->get_Ball_y() - p2_b[i].get_Brick_y() < 0.7*p2_b[i].get_Brick_height() + 5){
					if(get_Ball_x() + this->ball_radius >= p2_b[i].get_Brick_x() && get_Ball_x() < p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width()){
						set_Ball_speedY(-ball_speedY);
						p2_b[i].set_Brick_deleted();
					}
				}
			}
			else{ // collide with p2_bricks topside
				if(p2_b[i].get_Brick_y() - this->get_Ball_y() > 0.7*p2_b[i].get_Brick_height() && p2_b[i].get_Brick_y() - this->get_Ball_y() < 0.7*p2_b[i].get_Brick_height() + 5){
					if(get_Ball_x() + this->ball_radius >= p2_b[i].get_Brick_x() && get_Ball_x() < p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width()){
						set_Ball_speedY(-ball_speedY);
						p2_b[i].set_Brick_deleted();
					}
				}
			}
			if(get_Ball_speedX() > 0){ // collide with p2_bricks leftside
				if(get_Ball_x() + ball_radius > p2_b[i].get_Brick_x() && get_Ball_x() + ball_radius < p2_b[i].get_Brick_x() + 5){	
					if(get_Ball_y() >= p2_b[i].get_Brick_y() && get_Ball_y() < p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height()){
						set_Ball_speedX(-ball_speedX);
						p2_b[i].set_Brick_deleted();
					}
				}
			}
			else{ // collide with p2_bricks rightside
				if(get_Ball_x() - ball_radius > p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width() && get_Ball_x() - ball_radius < p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width() + 5){
					if(get_Ball_y() >= p2_b[i].get_Brick_y() && get_Ball_y() < p2_b[i].get_Brick_y()+p2_b[i].get_Brick_height()){
						set_Ball_speedX(-ball_speedX);
						p2_b[i].set_Brick_deleted();
					}
				}
			}
			/*if(get_Ball_speedX() > 0){ // collide with p2_bricks leftside
				if(get_Ball_x() + ball_radius >= p2_b[i].get_Brick_x() - 5 && get_Ball_x() + ball_radius < p2_b[i].get_Brick_x()){	
					if(get_Ball_y() - ball_radius >= p2_b[i].get_Brick_y() && get_Ball_y() + ball_radius < p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height()){
						set_Ball_speedX(-ball_speedX);
						p2_b[i].set_Brick_deleted();
					}
				}
			}
			else{ // collide with p2_bricks rightside
				if(get_Ball_x() - ball_radius > p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width() && get_Ball_x() - ball_radius < p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width() + 5){
					if(get_Ball_y() - ball_radius >= p2_b[i].get_Brick_y() && get_Ball_y() + ball_radius < p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height()){
						set_Ball_speedX(-ball_speedX);
						p2_b[i].set_Brick_deleted();
					}
				}
			}*/
		}
	}
}
