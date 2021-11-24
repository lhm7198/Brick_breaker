/*
 *	SW3 (SSE2034-41) Term Project
 *	
 *	Briefly explain : Declare Ball object
 *
 *	Copyright 2021 by 3-codiots
 */

#include "Ball.h"
#include <stdio.h>
#include <math.h>

Ball::Ball() : CircleShape(0){
	ball_radius = 0;
	ball_speedX = 0;
	ball_speedY = 0;
	gap = 0;
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
void Ball::set_gap(float gap_){
	gap = gap_;
}
void Ball::set_Ball_color(){
	if(active) this->setFillColor(sf::Color::Red);
	else this->setFillColor(sf::Color::White);
}

void Ball::Ball_move(int screen_width, int screen_height, Paddle &p1, Paddle &p2, std::vector<Brick> &p1_b, std::vector<Brick> &p2_b){
	this->move(ball_speedX, ball_speedY);

	// wall
	if(get_Ball_x() - ball_radius < 0){ // left collision
		if(ball_speedX < 0) set_Ball_speedX(-ball_speedX);	
	}
	else if(get_Ball_x() + 2*ball_radius >= screen_width){ // right collision
		if(ball_speedX > 0) set_Ball_speedX(-ball_speedX);
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
	if(ball_speedY < 0){ // when ball moves down to top
		if(get_Ball_y() - ball_radius >= p1.get_Paddle_y() + p1.get_Paddle_height() && get_Ball_y() - ball_radius < p1.get_Paddle_y() + p1.get_Paddle_height() - ball_speedY){
			if(get_Ball_x() > p1.get_Paddle_x() && get_Ball_x() < p1.get_Paddle_x() + p1.get_Paddle_width()){ // collide with p1_paddle
				if(p1.get_Paddle_item_work(ITEM1) && !active){ // p1 was active
					active = true;
					p1.set_Paddle_item_inactive(ITEM1);
				}

				if(ball_speedX * p2.get_Paddle_speedX() > 0){ // accelerate
					if(abs(ball_speedX) < 5.2){
						ball_speedX = ball_speedX * 1.2;
						ball_speedY = ball_speedY * 0.75;
					}
				}
				else{
					if(abs(ball_speedX) > 2.7){ // unaccelerate
						ball_speedX = ball_speedX / 1.2;
						ball_speedY = ball_speedY * 1.33;
					}
				}

				ball_speedY = -ball_speedY;
			}
		}
		if(get_Ball_y() - ball_radius >= p2.get_Paddle_y() + p2.get_Paddle_height() && get_Ball_y() - ball_radius < p2.get_Paddle_y() + p2.get_Paddle_height() - ball_speedY){ 
			if(get_Ball_x() > p2.get_Paddle_x() && get_Ball_x() < p2.get_Paddle_x() + p2.get_Paddle_width()){ // collide with p2_paddle
				if(p2.get_Paddle_item_work(ITEM1) && !active){ // p2 was active
					active = true;
					p2.set_Paddle_item_inactive(ITEM1);
				}				

				if(ball_speedX * p2.get_Paddle_speedX() > 0){ // accelerate
					if(abs(ball_speedX) < 5.2){
						ball_speedX = ball_speedX * 1.2;
						ball_speedY = ball_speedY * 0.75;
					}
				}
				else{
					if(abs(ball_speedX) > 2.7){ // unaccelerate
						ball_speedX = ball_speedX / 1.2;
						ball_speedY = ball_speedY * 1.33;
					}
				}

				ball_speedY = -ball_speedY;
			}
		}

	}
	else{ // when ball moves top to down
		if(get_Ball_y() + ball_radius <= p1.get_Paddle_y() && get_Ball_y() + ball_radius > p1.get_Paddle_y() - ball_speedY){
			if(get_Ball_x() > p1.get_Paddle_x() && get_Ball_x() < p1.get_Paddle_x() + p1.get_Paddle_width()){ // collide with p1_paddle
				if(p1.get_Paddle_item_work(ITEM1) && !active){ // p1 was active
					active = true;
					p1.set_Paddle_item_inactive(ITEM1);
				}

				if(ball_speedX * p1.get_Paddle_speedX() > 0){ // accelerate
					if(abs(ball_speedX) < 5.2){
						ball_speedX = ball_speedX * 1.2;
						ball_speedY = ball_speedY * 0.75;
					}
				}
				else{
					if(abs(ball_speedX) > 2.7){ // unaccelerate
						ball_speedX = ball_speedX / 1.2;
						ball_speedY = ball_speedY * 1.33;
					}
				}

				ball_speedY = -ball_speedY;
			}
		}
		if(get_Ball_y() + ball_radius <= p2.get_Paddle_y() && get_Ball_y() + ball_radius > p2.get_Paddle_y() - ball_speedY){
			if(get_Ball_x() > p2.get_Paddle_x() && get_Ball_x() < p2.get_Paddle_x() + p2.get_Paddle_width()){ // collide with p2_paddle
				if(p2.get_Paddle_item_work(ITEM1) && !active){ // p2 was active
					active = true;
					p2.set_Paddle_item_inactive(ITEM1);
				}

				if(ball_speedX * p2.get_Paddle_speedX() > 0){ // accelerate
					if(abs(ball_speedX) < 5.2){
						ball_speedX = ball_speedX * 1.2;
						ball_speedY = ball_speedY * 0.75;
					}
				}
				else{
					if(abs(ball_speedX) > 2.7){ // unaccelerate
						ball_speedX = ball_speedX / 1.2;
						ball_speedY = ball_speedY * 1.33;
					}
				}

				ball_speedY = -ball_speedY;
			}
		}
	}

	// p1_brick
	for(int i=0; i<p1_b.size(); i++){
		if(p1_b[i].get_Brick_hp() == 0) continue;

		bool collide_flag = false;
		if(ball_speedY < 0){ // collide with p1_bricks downside
			if(abs(get_Ball_y() - (p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height())) <= abs(ball_speedY)){
				if(i < 20 && p1_b[i+10].get_Brick_hp()) continue; // can't collide

				if(get_Ball_x() >= p1_b[i].get_Brick_x() - gap*0.5 && get_Ball_x() < p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width() + gap*0.5){
					set_Ball_speedY(-ball_speedY);

					collide_flag = true;
				}
			}
		}
		else{ // collide with p1_bricks topside
			if(abs(get_Ball_y() - p1_b[i].get_Brick_y()) <= abs(ball_speedY)){
				if(i >= 10 && p1_b[i-10].get_Brick_hp()) continue; // can't collide

				if(get_Ball_x() >= p1_b[i].get_Brick_x() - gap*0.5 && get_Ball_x() < p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width() + gap*0.5){
					set_Ball_speedY(-ball_speedY);

					collide_flag = true;
				}
			}
		}
		if(ball_speedX > 0){ // collide with p1_bricks leftside
			if(abs(get_Ball_x() - p1_b[i].get_Brick_x()) <= abs(ball_speedX)){	
				if(i%10 >= 1 && p1_b[i-1].get_Brick_hp()) continue; // can't collide

				if(get_Ball_y() >= p1_b[i].get_Brick_y() - gap*0.5 && get_Ball_y() < p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height() + gap*0.5){
					set_Ball_speedX(-ball_speedX);

					collide_flag = true;
				}
			}
		}
		else{ // collide with p1_bricks rightside
			if(abs(get_Ball_x() - (p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width())) <= abs(ball_speedX)){
				if(i%10 < 9 && p1_b[i+1].get_Brick_hp()) continue; // can't collide

				if(get_Ball_y() >= p1_b[i].get_Brick_y() - gap*0.5 && get_Ball_y() < p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height() + gap*0.5){
					set_Ball_speedX(-ball_speedX);

					collide_flag = true;
				}
			}
		}

		if(collide_flag){
			if(active){
				active = false;
				if(i >= 10 && p1_b[i-10].get_Brick_hp()){ // top
					p1_b[i-10].set_Brick_hp(p1_b[i-10].get_Brick_hp() - 1);
					if(p1_b[i-10].get_Brick_hp() == 0) p2_get_item(p1_b[i-10], p2);
				}
				if(i < 20 && p1_b[i+10].get_Brick_hp()){ // down
					p1_b[i+10].set_Brick_hp(p1_b[i+10].get_Brick_hp() - 1);
					if(p1_b[i+10].get_Brick_hp() == 0) p2_get_item(p1_b[i+10], p2);
				}
				if(i%10 >= 1 && p1_b[i-1].get_Brick_hp()){ // left
					p1_b[i-1].set_Brick_hp(p1_b[i-1].get_Brick_hp() - 1);
					if(p1_b[i-1].get_Brick_hp() == 0) p2_get_item(p1_b[i-1], p2);
				}
				if(i%10 < 9 && p1_b[i+1].get_Brick_hp()){ // right
					p1_b[i+1].set_Brick_hp(p1_b[i+1].get_Brick_hp() - 1);
					if(p1_b[i+1].get_Brick_hp() == 0) p2_get_item(p1_b[i+1], p2);
				}
			}

			p1_b[i].set_Brick_hp(p1_b[i].get_Brick_hp() - 1); // self
			if(p1_b[i].get_Brick_hp() == 0) p2_get_item(p1_b[i], p2);
		}
	}

	// p2_brick
	for(int i=0; i<p2_b.size(); i++){
		if(p2_b[i].get_Brick_hp() == 0) continue;

		bool collide_flag = false;
		if(ball_speedY < 0){ // collide with p2_bricks downside
			if(abs(get_Ball_y() - (p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height())) <= abs(ball_speedY)){
				if(i >= 10 && p2_b[i-10].get_Brick_hp()) continue; // can't collide


				if(get_Ball_x() >= p2_b[i].get_Brick_x() - gap*0.5 && get_Ball_x() < p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width() + gap*0.5){
					set_Ball_speedY(-ball_speedY);

					collide_flag = true;
				}
			}
		}
		else{ // collide with p2_bricks topside
			if(abs(get_Ball_y() - p2_b[i].get_Brick_y()) <= abs(ball_speedY)){
				if(i < 20 && p2_b[i+10].get_Brick_hp()) continue; // can't collide

				if(get_Ball_x() >= p2_b[i].get_Brick_x() - gap*0.5 && get_Ball_x() < p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width() + gap*0.5){
					set_Ball_speedY(-ball_speedY);

					collide_flag = true;
				}
			}
		}
		if(ball_speedX > 0){ // collide with p2_bricks leftside
			if(abs(get_Ball_x() - p2_b[i].get_Brick_x()) <= abs(ball_speedX)){	
				if(i%10 >= 1 && p2_b[i-1].get_Brick_hp()) continue; // can't collide

				if(get_Ball_y() >= p2_b[i].get_Brick_y() - gap*0.5 && get_Ball_y() < p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height() + gap*0.5){
					set_Ball_speedX(-ball_speedX);

					collide_flag = true;
				}
			}
		}
		else{ // collide with p1_bricks rightside
			if(abs(get_Ball_x() - (p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width())) <= abs(ball_speedX)){
				if(i%10 < 9 && p2_b[i+1].get_Brick_hp()) continue; // can't collide

				if(get_Ball_y() >= p2_b[i].get_Brick_y() - gap*0.5 && get_Ball_y() < p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height() + gap*0.5){
					set_Ball_speedX(-ball_speedX);

					collide_flag = true;
				}
			}
		}

		if(collide_flag){
			if(active){
				active = false;
				if(i < 20 && p2_b[i+10].get_Brick_hp()){ // top
					p2_b[i+10].set_Brick_hp(p2_b[i+10].get_Brick_hp() - 1);
					if(p2_b[i+10].get_Brick_hp() == 0) p1_get_item(p2_b[i+10], p1);
				}
				if(i >= 10 && p2_b[i-10].get_Brick_hp()){ // down
					p2_b[i-10].set_Brick_hp(p2_b[i-10].get_Brick_hp() - 1);
					if(p2_b[i-10].get_Brick_hp() == 0) p1_get_item(p2_b[i-10], p1);
				}
				if(i%10 >= 1 && p2_b[i-1].get_Brick_hp()){ // left
					p2_b[i-1].set_Brick_hp(p2_b[i-1].get_Brick_hp() - 1);
					if(p2_b[i-1].get_Brick_hp() == 0) p1_get_item(p2_b[i-1], p1);
				}
				if(i%10 < 9 && p2_b[i+1].get_Brick_hp()){ // right
					p2_b[i+1].set_Brick_hp(p2_b[i+1].get_Brick_hp() - 1);
					if(p2_b[i+1].get_Brick_hp() == 0) p1_get_item(p2_b[i+1], p1);
				}
			}

			p2_b[i].set_Brick_hp(p2_b[i].get_Brick_hp() - 1); // self
			if(p2_b[i].get_Brick_hp() == 0) p1_get_item(p2_b[i], p1);
		}
	}
}

void Ball::p1_get_item(Brick &brick, Paddle &paddle){
	int item = brick.get_Brick_item();

	switch(item){
		case 0: 
			break;
		case 1: 
			break;
		case 2:
			paddle.set_Paddle_item(ITEM2, 1);
			break;
		case 3:
			paddle.set_Paddle_item(ITEM1, 3);
			break;
		default:
			break;		
	}
}
void Ball::p2_get_item(Brick &brick, Paddle &paddle){
	int item = brick.get_Brick_item();

	switch(item){
		case 0: 
			break;
		case 1: 
			break;
		case 2:
			paddle.set_Paddle_item(ITEM2, 1);
			break;
		case 3:
			paddle.set_Paddle_item(ITEM1, 3);
			break;
		default:
			break;		
	}
}

