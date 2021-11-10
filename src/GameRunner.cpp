/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare game object
*
*	Copyright 2021 by 3-codiots
*/

#include "GameRunner.h"

void startset(sf::Text* text1, sf::Text* text2, sf::Text* prod, sf::Text* start, sf::Font* font1, sf::Font* font2);

Game::Game(int w, int h){
	// variable
	screen_width = w;
	screen_height = h;
	is_start_page = true;
	is_game_start = false;

	// Players

	// Bricks
	float brick_width = w / (BRICKS_PER_ROW * 1.15);
	float brick_height = brick_width * 0.3;
	gap = (w - BRICKS_PER_ROW*brick_width) / (BRICKS_PER_ROW + 1);
	p1_bricks_num = BRICKS_PER_ROW;
	p2_bricks_num = BRICKS_PER_ROW;

	for(int i=0; i<BRICKS_PER_ROW; i++){ // player1 bricks
		Brick brick;
		brick.set_Brick_size(brick_width, brick_height);
		brick.set_Brick_position(gap + i*(brick_width+gap), gap);
		p1_bricks.push_back(brick);
	}

	for(int i=0; i<BRICKS_PER_ROW; i++){ // player2 bricks
		Brick brick;
		brick.set_Brick_size(brick_width, brick_height);
		brick.set_Brick_position(gap + i*(brick_width+gap), h - gap - brick_height);
		p2_bricks.push_back(brick);
	}

	// Paddles
	float paddle_width = w * 0.2;
	float paddle_height = paddle_width * 0.05;

	Paddle paddle1; // player1 paddle
	paddle1.set_Paddle_size(paddle_width, paddle_height);
	paddle1.set_Paddle_position(w*0.5 - paddle_width/2, h*0.05);
	paddle1.set_Paddle_speedX(PADDLE_SPEED);
	p1_paddle.push_back(paddle1);

	Paddle paddle2; // player2 paddle
	paddle2.set_Paddle_size(paddle_width, paddle_height);
	paddle2.set_Paddle_position(w*0.5 - paddle_width/2, h*0.95 - paddle_height);
	paddle2.set_Paddle_speedX(PADDLE_SPEED);
	p2_paddle.push_back(paddle2);

	// Ball
	Ball ball;
	ball.set_Ball_size(BALL_RADIUS);
	ball.set_Ball_speedX(BALL_SPEED);
	ball.set_Ball_speedY(-BALL_SPEED);
	ball.set_Ball_position(w*0.5 - BALL_RADIUS, h*0.5 - BALL_RADIUS);
	balls.push_back(ball);
	
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

		sf::Font font1;
		sf::Font font2;
		font1.loadFromFile("RixVideoGame Bold.ttf");
		font2.loadFromFile("NanumGothic.ttf");
		sf::Text text1, text2, prod, start;
		startset(&text1, &text2, &prod, &start, &font1, &font2);

		window.clear(sf::Color::Black);
		
		window.draw(text1);
		window.draw(text2);
		window.draw(start);
		window.draw(prod);

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

		if(is_game_start){
			balls[0].Ball_move(screen_width, screen_height);
		}

		object_draw();
		window.display();
	}
}

void Game::receiveKeyinputs(){
	float p2_paddle_speed;
	if(event.type == sf::Event::KeyPressed){
		switch(event.key.code){
			case sf::Keyboard::Left:
				if(p2_paddle[0].get_Paddle_x() > 0){
					p2_paddle_speed = p2_paddle[0].get_Paddle_speedX();
					p2_paddle[0].move(-p2_paddle_speed, 0);
				}
				break;
			case sf::Keyboard::Right:
				if(p2_paddle[0].get_Paddle_x() < screen_width - p2_paddle[0].get_Paddle_width()){
					p2_paddle_speed = p2_paddle[0].get_Paddle_speedX();
					p2_paddle[0].move(p2_paddle_speed, 0);
				}
				break;
			case sf::Keyboard::Return:
				is_game_start = true;
				break;
			default:
				break;
		}
	}
}

void Game::object_draw(){
	window.clear(sf::Color::Black);
	for(int i=0; i<BRICKS_PER_ROW; i++){ // player1 bricks
		window.draw(p1_bricks[i]);
	}
	for(int i=0; i<BRICKS_PER_ROW; i++){ // player2 bricks
		window.draw(p2_bricks[i]);
	}
	for(int i=0; i<p1_paddle.size(); i++){ // player1 paddle
		window.draw(p1_paddle[i]);
	}
	for(int i=0; i<p2_paddle.size(); i++){ // player2 paddle
		window.draw(p2_paddle[i]);
	}
	for(int i=0; i<balls.size(); i++){ // ball
		window.draw(balls[i]);
	}
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
