/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Paddle object
*
*	Copyright 2021 by 3-codiots
*/

#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle : public sf::RectangleShape{
private:
	float paddle_width;
	float paddle_height;
	float paddle_speedX;
	int num_item1; // bomb
	int num_item2; // paddle grow	
	int num_item3; // paddle shrink
	bool item1_active;
	bool item2_active;
	bool item3_active;
public:
	Paddle();

	float get_Paddle_width();
	float get_Paddle_height();
	float get_Paddle_x();
	float get_Paddle_y();
	float get_Paddle_speedX();

	void set_Paddle_size(float paddle_width_, float paddle_height_);
	void set_Paddle_position(float paddle_x_, float paddle_y_);
	void set_Paddle_speedX(float paddle_speedX_);
	void set_Paddle_color();

	int get_Paddle_item(int idx);
	bool get_Paddle_item_flag(int idx);
	void set_Paddle_item(int idx, int num);
	void set_Paddle_item_active(int idx);
	void set_Paddle_item_inactive(int idx);

	void Paddle_move(int screen_width, int screen_height);
};

#endif


