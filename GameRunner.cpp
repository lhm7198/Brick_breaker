/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare game object
*
*	Copyright 2021 by 3-codiots
*/

#include "GameRunner.h"

Game::Game(int w, int h){
	// variable
	screen_width = w;
	screen_height = h;
	is_start_page = true;

	// Players

	// Bricks
	brick_width = w / (BRICKS_PER_ROW * 1.15);
	brick_height = brick_width * 0.3;
	gap = (w - BRICKS_PER_ROW*brick_width) / (BRICKS_PER_ROW + 1);
	for(int i=0; i<BRICKS_PER_ROW; i++){
		p1_bricks.push_back(Brick(brick_width, brick_height, 
				 gap + i*(brick_width+gap), gap));
		p2_bricks.push_back(Brick(brick_width, brick_height, 
				 gap + i*(brick_width+gap), h - gap - brick_height));
	}

	// Paddles
	paddle_width = w * 0.2;
	paddle_height = paddle_width * 0.05;
	p1_paddles.push_back(Paddle(paddle_width, paddle_height, 
				 w*0.5 - paddle_width/2, h*0.05, PADDLE_SPEED));
	p2_paddles.push_back(Paddle(paddle_width, paddle_height, 
				 w*0.5 - paddle_width/2, h*0.95 - paddle_height, PADDLE_SPEED));

	// Ball
	ball_radius = BALL_RADIUS;
	balls.push_back(Ball(ball_radius, w*0.5 - ball_radius, h*0.5 - ball_radius));
	
	// Window
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

		window.clear(sf::Color::Black);

		window.display();
	}

	gameRunning();
}

void Game::gameRunning(){
	while(window.isOpen()){
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();
			}

			receiveKeyinputs();
		}

		draw();
		window.display();
	}
}

void Game::receiveKeyinputs(){
	if(event.type == sf::Event::KeyPressed){
		switch(event.key.code){
			case sf::Keyboard::Left:
				if(p2_paddles[0].getPosition().x > 0){
					p2_paddle_speed = p2_paddles[0].get_Speed();
					p2_paddles[0].move(-p2_paddle_speed, 0);
				}
				break;
			case sf::Keyboard::Right:
				if(p2_paddles[0].getPosition().x < screen_width - paddle_width){
					p2_paddle_speed = p2_paddles[0].get_Speed();
					p2_paddles[0].move(p2_paddle_speed, 0);
				}
				break;
			default:
				break;
		}
	}
}

void Game::draw(){
	window.clear(sf::Color::Black);
	for(int i=0; i<BRICKS_PER_ROW; i++){
		window.draw(p1_bricks[i]);
		window.draw(p2_bricks[i]);
	}
	for(int i=0; i<p1_paddles.size(); i++){
		window.draw(p1_paddles[i]);
	}
	for(int i=0; i<p2_paddles.size(); i++){
		window.draw(p2_paddles[i]);
	}
	for(int i=0; i<balls.size(); i++){
		window.draw(balls[i]);
	}
}
