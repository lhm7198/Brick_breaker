/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare Brick object
*
*	Copyright 2021 by 3-codiots
*/

#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>

class Brick : public sf::RectangleShape{
private:
	float brick_width; 
	float brick_height;
	int brick_hp;
	int item;
	bool deleted;
public:
	Brick();

	float get_Brick_width();
	float get_Brick_height();
	float get_Brick_x();
	float get_Brick_y();
	int get_Brick_hp();
	int get_Brick_item();
	bool get_Brick_deleted();

	void set_Brick_size(float brick_width_, float brick_height_);
	void set_Brick_position(float brick_x_, float brick_y_);
	void set_Brick_hp(int brick_hp_);
	void set_Brick_color();
	void set_Brick_item(int item_);
	void set_Brick_deleted();
};

#endif


