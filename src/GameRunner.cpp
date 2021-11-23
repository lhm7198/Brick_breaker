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
Game::Game(int w, int h){
	// variable
	screen_width = w;
	screen_height = h;
	is_start_page = true;
	is_game_start = false;

	// items
	srand(time(NULL));
	int items1[3] = {0};
	int items2[3] = {0};
	for(int i=0; i<3; i++){
		items1[i] = rand() % BRICKS_PER_ROW;
		items2[i] = rand() % BRICKS_PER_ROW;
		printf("%d %d\n", items1[i], items2[i]);
	}

	// Bricks
	float brick_width = w / (BRICKS_PER_ROW * 1.1);
	float brick_height = brick_width * 0.4;
	gap = (w - BRICKS_PER_ROW*brick_width) / (BRICKS_PER_ROW + 1);
	p1_bricks_num = BRICKS_PER_ROW*BRICKS_PER_COL;
	p2_bricks_num = BRICKS_PER_ROW*BRICKS_PER_COL;
	for(int i=0; i<BRICKS_PER_COL; i++){
		for(int j=0; j<BRICKS_PER_ROW; j++){ // player1 bricks
			Brick brick;
			if(items1[i] == j) brick.set_Brick_item(i+1);
			brick.set_Brick_size(brick_width, brick_height);
			brick.set_Brick_position(gap + j*(brick_width + gap), gap + i*(brick_height + gap));
			brick.set_Brick_hp(3-i);
			brick.set_Brick_color();
			p1_bricks.push_back(brick);
		}
	}
	for(int i=0; i<BRICKS_PER_COL; i++){
		for(int j=0; j<BRICKS_PER_ROW; j++){ // player2 bricks
			Brick brick;
			if(items2[i] == j) brick.set_Brick_item(i+1);
			brick.set_Brick_size(brick_width, brick_height);
			brick.set_Brick_position(gap + j*(brick_width + gap), screen_height - gap - brick_height - i*(brick_height + gap));
			brick.set_Brick_hp(3-i);
			brick.set_Brick_color();
			p2_bricks.push_back(brick);
		}
	}

	// Paddles
	float paddle_width = w * 0.2;
	float paddle_height = paddle_width * 0.05;

	Paddle paddle1; // player1 paddle
	paddle1.set_Paddle_size(paddle_width, paddle_height);
	paddle1.set_Paddle_position(w*0.5 - paddle_width/2, h*0.2);
	paddle1.set_Paddle_speedX(0);
	paddle1.set_Paddle_color();
	p1_paddle.push_back(paddle1);

	Paddle paddle2; // player2 paddle
	paddle2.set_Paddle_size(paddle_width, paddle_height);
	paddle2.set_Paddle_position(w*0.5 - paddle_width/2, h*0.8 - paddle_height);
	paddle2.set_Paddle_speedX(0);
	paddle2.set_Paddle_color();
	p2_paddle.push_back(paddle2);

	// Balls
	Ball ball1; // ball1
	ball1.set_Ball_size(BALL_RADIUS);
	ball1.set_Ball_speedX(BALL_SPEED);
	ball1.set_Ball_speedY(-BALL_SPEED);
	ball1.set_Ball_position(w*0.3 - BALL_RADIUS, h*0.5 - BALL_RADIUS);
	balls.push_back(ball1);

	Ball ball2; // ball2
	ball2.set_Ball_size(BALL_RADIUS);
	ball2.set_Ball_speedX(-BALL_SPEED);
	ball2.set_Ball_speedY(BALL_SPEED);
	ball2.set_Ball_position(w*0.7 - BALL_RADIUS, h*0.5 - BALL_RADIUS);
	balls.push_back(ball2);

	// Window
	window.create(sf::VideoMode(w, h), "3-codiots");
	window.setFramerateLimit(60);
}

void Game::gameStart(){
	int cnt = 0;
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

		if(cnt % 90 >=0 && cnt % 90 < 45){ // twinkle
			window.draw(start);
		}
		window.draw(text1);
		window.draw(text2);
		window.draw(prod);

		window.display();
		cnt++;
	}

	gameRunning();
}

void Game::gameRunning(){
	while(window.isOpen()){
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();
			}

			receiveKeyinputs();
		}

		if(is_game_start){
			p1_paddle[0].Paddle_move(screen_width, screen_height); // player1 paddle move
			p2_paddle[0].Paddle_move(screen_width, screen_height); // player2 paddle move
			balls[0].Ball_move(screen_width, screen_height, p1_paddle[0], p2_paddle[0], p1_bricks, p2_bricks); // ball1 move
			balls[1].Ball_move(screen_width, screen_height, p1_paddle[0], p2_paddle[0], p1_bricks, p2_bricks); // ball2 move
			object_draw();
		}
		//printf("%f %f\n", balls[0].get_Ball_speedX(), balls[0].get_Ball_speedY());
		printf("%d %d\n", p1_paddle[0].get_Paddle_bomb(), p2_paddle[0].get_Paddle_bomb());
		object_draw();
		window.display();
	}
}

void Game::receiveKeyinputs(){
	if(event.type == sf::Event::KeyPressed){
		switch(event.key.code){
			case sf::Keyboard::A:
				p1_paddle[0].set_Paddle_speedX(-PADDLE_SPEED);
				break;
			case sf::Keyboard::D:
				p1_paddle[0].set_Paddle_speedX(PADDLE_SPEED);
				break;
			case sf::Keyboard::F:
				if(p1_paddle[0].get_Paddle_bomb()){
					p1_paddle[0].set_Paddle_bomb_active();
					p1_paddle[0].set_Paddle_bomb(p1_paddle[0].get_Paddle_bomb() - 1);
				}
				break;
			case sf::Keyboard::Left:
				p2_paddle[0].set_Paddle_speedX(-PADDLE_SPEED);
				break;
			case sf::Keyboard::Right:
				p2_paddle[0].set_Paddle_speedX(PADDLE_SPEED);
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
	sf::Font font;
	font.loadFromFile("NanumGothic.ttf");
	sf::Text text, p1_control, p2_control;
	startgame(&text, &p1_control, &p2_control, &font);
	if(!is_game_start){
		window.draw(text);
	}
	window.draw(p1_control);
	window.draw(p2_control);

	for(int i=0; i<BRICKS_PER_ROW*BRICKS_PER_COL; i++){ // player1 bricks
		if(p1_bricks[i].get_Brick_deleted() == true) continue;
		p1_bricks[i].set_Brick_color();		
		window.draw(p1_bricks[i]);
	}
	for(int i=0; i<BRICKS_PER_ROW*BRICKS_PER_COL; i++){ // player2 bricks
		if(p2_bricks[i].get_Brick_deleted() == true) continue;
		p2_bricks[i].set_Brick_color();		
		window.draw(p2_bricks[i]);
	}
	for(int i=0; i<p1_paddle.size(); i++){ // player1 paddle
		p1_paddle[i].set_Paddle_color();
		window.draw(p1_paddle[i]);
	}
	for(int i=0; i<p2_paddle.size(); i++){ // player2 paddle
		p2_paddle[i].set_Paddle_color();
		window.draw(p2_paddle[i]);
	}
	for(int i=0; i<balls.size(); i++){ // balls
		//balls[i].set_Ball_color();
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
