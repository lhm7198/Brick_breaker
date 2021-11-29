/*
 *	SW3 (SSE2034-41) Term Project
 *	
 *	Briefly explain : Declare game object
 *
 *	Copyright 2021 by 3-codiots
 */
#include "GameRunner.h"
#include <stdio.h>

void startset(sf::Text* text1, sf::Text* text2, sf::Text* prod, sf::Text* start, sf::Font* font1, sf::Font* font2);
void startgame(sf::Text* text, sf::Text* p1_control, sf::Text* p2_control, sf::Font* font);
void player1_win(sf::Text* text1, sf::Text* text2, sf::Font* font);
void player2_win(sf::Text* text1, sf::Text* text2, sf::Font* font);
void print_timer(sf::Text* timer, sf::Font* font, float time, float x, float y);
float fast(float speed);
float slow(float speed);

Game::Game(int w, int h){
	
	screen_width = w;
	screen_height = h;
	is_start_page = true;
	is_game_start = false;
	is_game_end = 0;

	rand_item();
	sound_setting();
	
	set_p1_item_slot_image();
	set_p2_item_slot_image();

	set_p1_item1_image();
	set_p1_item2_image();
	set_p1_item3_image();

	set_p2_item1_image();
	set_p2_item2_image();
	set_p2_item3_image();
	
	generate_p1_brick();
	generate_p2_brick();
	
	set_collision_sound();
	set_bomb_sound();
	set_victory_sound();

	set_p1_paddle();
	set_p2_paddle();
	p2.set_Paddle_color();
	
	set_ball1();
	set_ball2();

	window.create(sf::VideoMode(w, h), "3-codiots");
	window.setFramerateLimit(60);

}

void Game::gameStart(){
	
	while(window.isOpen() && is_start_page){
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				is_start_page = false;
			}
		}
		display_start_page();
	}

	gameRunning();
}

void Game::gameRunning(){
	
	while(window.isOpen() && !is_game_end){
		clock.restart();

		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();
			}

			receiveKeyinputs();
		}

		if(is_game_start){
			p1.Paddle_move(screen_width, screen_height); // player1 paddle move
			p2.Paddle_move(screen_width, screen_height); // player2 paddle move
			balls[0].Ball_move(); // ball1 move
			balls[1].Ball_move(); // ball2 move

			ball_wall_collision();
			ball_paddle_collision();
			ball_brick_collision(balls[0]);
			ball_brick_collision(balls[1]);
		}
		set_p1_item1_timer();
		set_p1_item2_timer();
		set_p2_item1_timer();
		set_p2_item2_timer();
		
		window.display();
	}

	while(window.isOpen() && is_game_end){
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}
		}
		display_end_page();
	}
}

void Game::receiveKeyinputs(){
	if(event.type == sf::Event::KeyPressed){
		switch(event.key.code){
			case sf::Keyboard::A:
				move_left_p1();
				break;
			case sf::Keyboard::S:
				p1.set_Paddle_speedX(0);
				break;
			
			
			///////////////////////////
			
			
			case sf::Keyboard::PageDown:
				if(p2.get_Paddle_item(ITEM3) && !p2.get_Paddle_item_work(ITEM3)){
					p2.set_Paddle_item_active(ITEM3);
					p2.set_Paddle_item(ITEM3, p2.get_Paddle_item(ITEM3) - 1);
					p1.set_Paddle_speedX(p1.get_Paddle_speedX() / 2);
					p2_item3_timer = true;
				}
				break;
			default:
				break;
		}
	}
}

void Game::object_draw(){
	window.clear(sf::Color::Black);

	draw_gamestart_page();
	
	draw_p1_item_slot();
	draw_p2_item_slot();
	
	draw_p1_item1();
	draw_p1_item2();
	draw_p1_item3();
	draw_p2_item1();
	draw_p2_item2();
	draw_p2_item3();

	draw_p1_paddle();
	draw_p2_paddle();

	draw_p1_brick();
	draw_p2_brick();

	set_brick_color();
	
	window.display();
}

void Game::ball_wall_collision(){
	// wall
	for(int i=0; i<balls.size(); i++){
		if(balls[i].get_Ball_x() - balls[i].get_Ball_radius() < 0){ // left collision
			if(balls[i].get_Ball_speedX() < 0) balls[i].set_Ball_speedX(-balls[i].get_Ball_speedX());	
		}
		else if(balls[i].get_Ball_x() + balls[i].get_Ball_radius() * 2 >= screen_width){ // right collision
			if(balls[i].get_Ball_speedX() > 0) balls[i].set_Ball_speedX(-balls[i].get_Ball_speedX());
		}
		if(balls[i].get_Ball_y() - balls[i].get_Ball_radius() < 0){ // topside collision
			balls[i].set_Ball_speedY(-balls[i].get_Ball_speedY());
			is_game_start = false;
			is_game_end = PLAYER2;
		}
		else if(balls[i].get_Ball_y() + balls[i].get_Ball_radius() * 2 >= screen_height){ // downside collision
			balls[i].set_Ball_speedY(-balls[i].get_Ball_speedY());
			is_game_start = false;
			is_game_end = PLAYER1;
		}
	}
}
void Game::ball_paddle_collision(){
	// paddle
	for(int i=0; i<balls.size(); i++){
		if(balls[i].get_Ball_speedY() < 0){ // when ball moves down to top
			if(check_y_boundary()){//collide with p1_paddle
				if(check_x_boundary()){
					soundPaddle.play();
					if(check_bomb){ // p1 was active && balls[i] was inactive
						p1.set_Paddle_item_inactive(ITEM1);
						balls[i].set_Ball_active();
					}

					if(accelate()){
						set_ball_speed();
					}
					else{ 
						set_ball_speed();
					}
					set_ball_direction();
				}
			}
		}

		//////////////////////
		//////////////////////

	}	
}
void Game::ball_brick_collision(Ball &ball){
	// p1_brick
	for(int i=0; i<p1_b.size(); i++){
		if(p1_b[i].get_Brick_hp() == 0) continue;

		bool collide_flag = false;
		if(ball.get_Ball_speedY() < 0){ // collide with p1_bricks downside
			if(check_y_boundary()){
				if(i < 20 && p1_b[i+10].get_Brick_hp()) continue; // can't collide

				if(check_x_boundary()){
					set_ball_direction();

					collide_flag = true;
				}
			}
		}
		
		/////////////////////

		if(collide_flag){
			if(ball.get_Ball_active()) soundBomb.play();
			else soundBricks.play(); 

			if(ball.get_Ball_active()){
				ball.set_Ball_inactive();
				if(i >= 10 && p1_b[i-10].get_Brick_hp()){ // top
					p1_b[i-10].set_Brick_hp(p1_b[i-10].get_Brick_hp() - 1);
					if(p1_b[i-10].get_Brick_hp() == 0) p2_get_item(p1_b[i-10]);
				}
				if(i < 20 && p1_b[i+10].get_Brick_hp()){ // down
					p1_b[i+10].set_Brick_hp(p1_b[i+10].get_Brick_hp() - 1);
					if(p1_b[i+10].get_Brick_hp() == 0) p2_get_item(p1_b[i+10]);
				}
				if(i%10 >= 1 && p1_b[i-1].get_Brick_hp()){ // left
					p1_b[i-1].set_Brick_hp(p1_b[i-1].get_Brick_hp() - 1);
					if(p1_b[i-1].get_Brick_hp() == 0) p2_get_item(p1_b[i-1]);
				}
				if(i%10 < 9 && p1_b[i+1].get_Brick_hp()){ // right
					p1_b[i+1].set_Brick_hp(p1_b[i+1].get_Brick_hp() - 1);
					if(p1_b[i+1].get_Brick_hp() == 0) p2_get_item(p1_b[i+1]);
				}
			}

			p1_b[i].set_Brick_hp(p1_b[i].get_Brick_hp() - 1); // self
			if(p1_b[i].get_Brick_hp() == 0) p2_get_item(p1_b[i]);

			continue;
		}

		if(ball.get_Ball_speedX() > 0){ // collide with p1_bricks leftside
			if(check_x_boundary()){	
				if(i%10 >= 1 && p1_b[i-1].get_Brick_hp()) continue; // can't collide

				if(check_y_boundary()){
					set_ball_direction();
					collide_flag = true;
					soundBricks.play();
				}
			}
		}

		/////////////////////
		if(collide_flag){
			if(ball.get_Ball_active()) soundBomb.play();
			else soundBricks.play(); 

			if(ball.get_Ball_active()){
				ball.set_Ball_inactive();
				if(i >= 10 && p1_b[i-10].get_Brick_hp()){ // top
					p1_b[i-10].set_Brick_hp(p1_b[i-10].get_Brick_hp() - 1);
					if(p1_b[i-10].get_Brick_hp() == 0) p2_get_item(p1_b[i-10]);
				}
				if(i < 20 && p1_b[i+10].get_Brick_hp()){ // down
					p1_b[i+10].set_Brick_hp(p1_b[i+10].get_Brick_hp() - 1);
					if(p1_b[i+10].get_Brick_hp() == 0) p2_get_item(p1_b[i+10]);
				}
				if(i%10 >= 1 && p1_b[i-1].get_Brick_hp()){ // left
					p1_b[i-1].set_Brick_hp(p1_b[i-1].get_Brick_hp() - 1);
					if(p1_b[i-1].get_Brick_hp() == 0) p2_get_item(p1_b[i-1]);
				}
				if(i%10 < 9 && p1_b[i+1].get_Brick_hp()){ // right
					p1_b[i+1].set_Brick_hp(p1_b[i+1].get_Brick_hp() - 1);
					if(p1_b[i+1].get_Brick_hp() == 0) p2_get_item(p1_b[i+1]);
				}
			}

			p1_b[i].set_Brick_hp(p1_b[i].get_Brick_hp() - 1); // self
			if(p1_b[i].get_Brick_hp() == 0) p2_get_item(p1_b[i]);
		}
	}


	// p2_brick
	for(int i=0; i<p2_b.size(); i++){
		if(p2_b[i].get_Brick_hp() == 0) continue;

		bool collide_flag = false;
		if(ball.get_Ball_speedY() < 0){ // collide with p2_bricks downside
			if(abs(ball.get_Ball_y() - (p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height())) <= abs(ball.get_Ball_speedY())){
				if(i >= 10 && p2_b[i-10].get_Brick_hp()) continue; // can't collide

				if(ball.get_Ball_x() >= p2_b[i].get_Brick_x() - gap*0.5 && ball.get_Ball_x() < p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width() + gap*0.5){
					ball.set_Ball_speedY(-ball.get_Ball_speedY());

					collide_flag = true;
				}
			}
		}
		else{ // collide with p2_bricks topside
			if(abs(ball.get_Ball_y() - p2_b[i].get_Brick_y()) <= abs(ball.get_Ball_speedY())){
				if(i < 20 && p2_b[i+10].get_Brick_hp()) continue; // can't collide

				if(ball.get_Ball_x() >= p2_b[i].get_Brick_x() - gap*0.5 && ball.get_Ball_x() < p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width() + gap*0.5){
					ball.set_Ball_speedY(-ball.get_Ball_speedY());

					collide_flag = true;
				}
			}
		}

		if(collide_flag){
			if(ball.get_Ball_active()) soundBomb.play();
			else soundBricks.play(); 

			if(ball.get_Ball_active()){
				ball.set_Ball_inactive();
				if(i < 20 && p2_b[i+10].get_Brick_hp()){ // top
					p2_b[i+10].set_Brick_hp(p2_b[i+10].get_Brick_hp() - 1);
					if(p2_b[i+10].get_Brick_hp() == 0) p1_get_item(p2_b[i+10]);
				}
				if(i >= 10 && p2_b[i-10].get_Brick_hp()){ // down
					p2_b[i-10].set_Brick_hp(p2_b[i-10].get_Brick_hp() - 1);
					if(p2_b[i-10].get_Brick_hp() == 0) p1_get_item(p2_b[i-10]);
				}
				if(i%10 >= 1 && p2_b[i-1].get_Brick_hp()){ // left
					p2_b[i-1].set_Brick_hp(p2_b[i-1].get_Brick_hp() - 1);
					if(p2_b[i-1].get_Brick_hp() == 0) p1_get_item(p2_b[i-1]);
				}
				if(i%10 < 9 && p2_b[i+1].get_Brick_hp()){ // right
					p2_b[i+1].set_Brick_hp(p2_b[i+1].get_Brick_hp() - 1);
					if(p2_b[i+1].get_Brick_hp() == 0) p1_get_item(p2_b[i+1]);
				}
			}

			p2_b[i].set_Brick_hp(p2_b[i].get_Brick_hp() - 1); // self
			if(p2_b[i].get_Brick_hp() == 0) p1_get_item(p2_b[i]);
			continue;
		}

		if(ball.get_Ball_speedX() > 0){ // collide with p2_bricks leftside
			if(abs(ball.get_Ball_x() - p2_b[i].get_Brick_x()) <= abs(ball.get_Ball_speedX())){	
				if(i%10 >= 1 && p2_b[i-1].get_Brick_hp()) continue; // can't collide

				if(ball.get_Ball_y() >= p2_b[i].get_Brick_y() - gap*0.5 && ball.get_Ball_y() < p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height() + gap*0.5){
					ball.set_Ball_speedX(-ball.get_Ball_speedX());

					collide_flag = true;
				}
			}
		}
		else{ // collide with p1_bricks rightside
			if(abs(ball.get_Ball_x() - (p2_b[i].get_Brick_x() + p2_b[i].get_Brick_width())) <= abs(ball.get_Ball_speedX())){
				if(i%10 < 9 && p2_b[i+1].get_Brick_hp()) continue; // can't collide

				if(ball.get_Ball_y() >= p2_b[i].get_Brick_y() - gap*0.5 && ball.get_Ball_y() < p2_b[i].get_Brick_y() + p2_b[i].get_Brick_height() + gap*0.5){
					ball.set_Ball_speedX(-ball.get_Ball_speedX());

					collide_flag = true;
				}
			}
		}

		if(collide_flag){
			if(ball.get_Ball_active()) soundBomb.play();
			else soundBricks.play(); 

			if(ball.get_Ball_active()){
				ball.set_Ball_inactive();
				if(i < 20 && p2_b[i+10].get_Brick_hp()){ // top
					p2_b[i+10].set_Brick_hp(p2_b[i+10].get_Brick_hp() - 1);
					if(p2_b[i+10].get_Brick_hp() == 0) p1_get_item(p2_b[i+10]);
				}
				if(i >= 10 && p2_b[i-10].get_Brick_hp()){ // down
					p2_b[i-10].set_Brick_hp(p2_b[i-10].get_Brick_hp() - 1);
					if(p2_b[i-10].get_Brick_hp() == 0) p1_get_item(p2_b[i-10]);
				}
				if(i%10 >= 1 && p2_b[i-1].get_Brick_hp()){ // left
					p2_b[i-1].set_Brick_hp(p2_b[i-1].get_Brick_hp() - 1);
					if(p2_b[i-1].get_Brick_hp() == 0) p1_get_item(p2_b[i-1]);
				}
				if(i%10 < 9 && p2_b[i+1].get_Brick_hp()){ // right
					p2_b[i+1].set_Brick_hp(p2_b[i+1].get_Brick_hp() - 1);
					if(p2_b[i+1].get_Brick_hp() == 0) p1_get_item(p2_b[i+1]);
				}
			}

			p2_b[i].set_Brick_hp(p2_b[i].get_Brick_hp() - 1); // self
			if(p2_b[i].get_Brick_hp() == 0) p1_get_item(p2_b[i]);
		}
	}
}

void Game::p1_get_item(Brick &brick){
	int item = brick.get_Brick_item();

	switch(item){
		case 1:	p1.set_Paddle_item(ITEM3, 3); break;
		case 2:	p1.set_Paddle_item(ITEM2, 3); break;
		case 3:	p1.set_Paddle_item(ITEM1, 3); break;
		default: break;		
	}
}
void Game::p2_get_item(Brick &brick){
	int item = brick.get_Brick_item();

	switch(item){
		case 1:	p2.set_Paddle_item(ITEM3, 3); break;
		case 2:	p2.set_Paddle_item(ITEM2, 3); break;
		case 3:	p2.set_Paddle_item(ITEM1, 3); break;
		default: break;		
	}
}

float slow(float speed){
	float array[5]={4.9152, 4.6648, 4, 3.2, 2.8};

	for(int i=0 ; i<4 ; i++){
		if(speed==array[i]){
			speed=array[i+1];
			break;
		}
	}
	for(int i=0 ; i<4 ; i++){
		if(speed==-1*array[i]){
			speed=-1*array[i+1];
			break;
		}
	}

	return speed;
}
float fast(float speed){
	float array[5]={4.9152, 4.6648, 4, 3.2, 2.8};

	for(int i=1 ; i<5 ; i++){
		if(speed==array[i]){
			speed=array[i-1];
			break;
		}
	}
	for(int i=1 ; i<5 ; i++){
		if(speed==-1*array[i]){
			speed=-1*array[i-1];
			break;
		}
	}

	return speed;
}

void startset(sf::Text* text1, sf::Text* text2, sf::Text* prod, sf::Text* start, sf::Font* font1, sf::Font* font2){
	text1->setString("BRICKS");
	text2->setString("BREAKER");
	prod->setString("Prod by 3-codiots");
	start->setString("Press SpaceBar To Start !");

	text1->setFont(*font1);
	text2->setFont(*font1);
	prod->setFont(*font2);
	start->setFont(*font1);

	text1->setCharacterSize(100);
	text2->setCharacterSize(100);
	prod->setCharacterSize(15);
	start->setCharacterSize(28);

	text1->setFillColor(sf::Color::Red);
	text2->setFillColor(sf::Color::Yellow);
	start->setFillColor(sf::Color::Green);
	start->setOutlineColor(sf::Color::Blue);
	start->setOutlineThickness(2.f);
	prod->setFillColor(sf::Color::Blue);
	prod->setStyle(sf::Text::Bold | sf::Text::Underlined);

	text1->setPosition(-10.f, 175.f);
	text2->setPosition(120.f, 180.f);
	text1->setRotation(-30.f);	
	start->setPosition(105.f, 650.f);
	prod->setPosition(170.f,775.f);
}
void startgame(sf::Text* text, sf::Text* p1_control, sf::Text* p2_control, sf::Font* font){
	text->setString("Press Enter to start");
	p1_control->setString("A      D");
	p2_control->setString("<-     ->");

	text->setFont(*font);
	p1_control->setFont(*font);
	p2_control->setFont(*font);

	text->setCharacterSize(30);
	p1_control->setCharacterSize(50);
	p2_control->setCharacterSize(50);

	text->setFillColor(sf::Color::White);
	p1_control->setFillColor(sf::Color(250, 250, 250, 100));
	p2_control->setFillColor(sf::Color(250, 250, 250, 100));

	text->setPosition(100.f, 450.f);
	p1_control->setPosition(160.f, 85.f);
	p2_control->setPosition(160.f, 650.f);
}
void player1_win(sf::Text* text1, sf::Text* text2, sf::Font* font){
	text1->setString("Congratulations!");
	text1->setFont(*font);
	text1->setCharacterSize(50);
	text1->setFillColor(sf::Color::Yellow);
	text1->setPosition(100.f, 325.f);

	text2->setString("PLAYER 1 WINS");
	text2->setFont(*font);
	text2->setCharacterSize(40);
	text2->setFillColor(sf::Color::White);
	text2->setPosition(140.f, 450.f);
}
void player2_win(sf::Text* text1, sf::Text* text2, sf::Font* font){
	text1->setString("Congratulations!");
	text1->setFont(*font);
	text1->setCharacterSize(50);
	text1->setFillColor(sf::Color::Yellow);
	text1->setPosition(100.f, 325.f);

	text2->setString("PLAYER 2 WINS");
	text2->setFont(*font);
	text2->setCharacterSize(40);
	text2->setFillColor(sf::Color::White);
	text2->setPosition(140.f, 450.f);
}
void print_timer(sf::Text* timer, sf::Font* font, float time, float x, float y){
	int t = 10-time;
	timer->setString(std::to_string(t));
	timer->setFont(*font);
	timer->setCharacterSize(30);
	timer->setFillColor(sf::Color::White);
	timer->setPosition(x, y);

}
