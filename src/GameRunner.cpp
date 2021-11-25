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
	// variable
	screen_width = w;
	screen_height = h;
	is_start_page = true;
	is_game_start = false;
	is_game_end = 0;

	// items
	srand(time(NULL));
	int items1[3] = {0};
	int items2[3] = {0};
	for(int i=0; i<3; i++){
		items1[i] = rand() % BRICKS_PER_ROW;
		items2[i] = rand() % BRICKS_PER_ROW;
	}
	if(!bufferBomb.loadFromFile("./sound/bomb.wav"))
		printf("cannot play");
	soundBomb.setBuffer(bufferBomb);
	soundBomb.setLoop(false);
	soundBomb.setVolume(50.0);

	// item_slot
	p1_item.loadFromFile("image/P1_item.png");
	p1_item.setSmooth(true);
	p1_item_slot.setTexture(p1_item);
	p1_item_slot.scale(0.5f,0.5f);
	p1_item_slot.setPosition(0.f,120.f);


	p2_item.loadFromFile("image/P2_item.png");
	p2_item.setSmooth(true);
	p2_item_slot.setTexture(p2_item);
	p2_item_slot.scale(0.5f,0.5f);
	p2_item_slot.setPosition(424.f,450.f);

	// item1
	item1_1.loadFromFile("./image/item1_1.jpg");
	item1_1.setSmooth(true);
	p1_s_item1_1.setTexture(item1_1);
	p1_s_item1_1.setScale(0.21f, 0.17f);
	p1_s_item1_1.setPosition(2.1f, 138.f);
	p2_s_item1_1.setTexture(item1_1);
	p2_s_item1_1.setScale(0.21f, 0.17f);
	p2_s_item1_1.setPosition(427.f, 468.f);

	item1_2.loadFromFile("./image/item1_2.jpg");
	item1_2.setSmooth(true);
	p1_s_item1_2.setTexture(item1_2);
	p1_s_item1_2.setScale(0.16f, 0.14f);
	p1_s_item1_2.setPosition(2.1f, 138.f);
	p2_s_item1_2.setTexture(item1_2);
	p2_s_item1_2.setScale(0.16f, 0.14f);
	p2_s_item1_2.setPosition(427.f, 468.f);

	item1_3.loadFromFile("./image/item1_3.jpg");
	item1_3.setSmooth(true);
	p1_s_item1_3.setTexture(item1_3);
	p1_s_item1_3.setScale(0.14f, 0.13f);
	p1_s_item1_3.setPosition(2.1f, 138.f);
	p2_s_item1_3.setTexture(item1_3);
	p2_s_item1_3.setScale(0.14f, 0.13f);
	p2_s_item1_3.setPosition(427.f, 468.f);

	// item2
	item2_1.loadFromFile("./image/item2_1.jpg");
	item2_1.setSmooth(true);
	p1_s_item2_1.setTexture(item2_1);
	p1_s_item2_1.setScale(0.25f, 0.3f);
	p1_s_item2_1.setPosition(2.1f, 205.f);
	p2_s_item2_1.setTexture(item2_1);
	p2_s_item2_1.setScale(0.25f, 0.3f);
	p2_s_item2_1.setPosition(427.f, 535.f);

	item2_2.loadFromFile("./image/item2_2.jpg");
	item2_2.setSmooth(true);
	p1_s_item2_2.setTexture(item2_2);
	p1_s_item2_2.setScale(0.28f, 0.38f);
	p1_s_item2_2.setPosition(2.1f, 205.f);
	p2_s_item2_2.setTexture(item2_2);
	p2_s_item2_2.setScale(0.28f, 0.38f);
	p2_s_item2_2.setPosition(427.f, 535.f);

	item2_3.loadFromFile("./image/item2_3.jpg");
	item2_3.setSmooth(true);
	p1_s_item2_3.setTexture(item2_3);
	p1_s_item2_3.setScale(0.28f, 0.38f);
	p1_s_item2_3.setPosition(2.1f, 205.f);
	p2_s_item2_3.setTexture(item2_3);
	p2_s_item2_3.setScale(0.28f, 0.38f);
	p2_s_item2_3.setPosition(427.f, 535.f);

	// item3
	item3_1.loadFromFile("./image/item3_1.jpg");
	item3_1.setSmooth(true);
	p1_s_item3_1.setTexture(item3_1);
	p1_s_item3_1.setScale(0.16f, 0.16f);
	p1_s_item3_1.setPosition(2.1f, 275.f);
	p2_s_item3_1.setTexture(item3_1);
	p2_s_item3_1.setScale(0.16f, 0.16f);
	p2_s_item3_1.setPosition(427.f, 605.f);

	item3_2.loadFromFile("./image/item3_2.jpg");
	item3_2.setSmooth(true);
	p1_s_item3_2.setTexture(item3_2);
	p1_s_item3_2.setScale(0.3f, 0.35f);
	p1_s_item3_2.setPosition(2.1f, 275.f);
	p2_s_item3_2.setTexture(item3_2);
	p2_s_item3_2.setScale(0.3f, 0.35f);
	p2_s_item3_2.setPosition(427.f, 605.f);

	item3_3.loadFromFile("./image/item3_3.jpg");
	item3_3.setSmooth(true);
	p1_s_item3_3.setTexture(item3_3);
	p1_s_item3_3.setScale(0.33f, 0.28f);
	p1_s_item3_3.setPosition(2.1f, 275.f);
	p2_s_item3_3.setTexture(item3_3);
	p2_s_item3_3.setScale(0.33f, 0.28f);
	p2_s_item3_3.setPosition(427.f, 605.f);
	
	// Bricks
	float brick_width = w / (BRICKS_PER_ROW * 1.1);
	float brick_height = brick_width * 0.4;
	gap = (w - BRICKS_PER_ROW*brick_width) / (BRICKS_PER_ROW + 1);
	for(int i=0; i<BRICKS_PER_COL; i++){
		for(int j=0; j<BRICKS_PER_ROW; j++){ // player1 bricks
			Brick brick;
			if(items1[i] == j) brick.set_Brick_item(i+1);
			brick.set_Brick_size(brick_width, brick_height);
			brick.set_Brick_position(gap + j*(brick_width + gap), gap + i*(brick_height + gap));
			brick.set_Brick_hp(3-i);
			brick.set_Brick_color();
			p1_b.push_back(brick);
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
			p2_b.push_back(brick);
		}
	}
	if(!bufferBricks.loadFromFile("./sound/collision.wav"))
		printf("cannot play");
	soundBricks.setBuffer(bufferBricks);
	soundBricks.setLoop(false);
	soundBricks.setVolume(50.0);

	// Paddles
	float paddle_width = w * 0.2;
	float paddle_height = paddle_width * 0.05;
	p1_item2_timer = false;
	p1_item3_timer = false;
	p2_item2_timer = false;
	p2_item3_timer = false;

	p1.set_Paddle_size(paddle_width, paddle_height); // player1 paddle
	p1.set_Paddle_position(w*0.5 - paddle_width/2, h*0.2);
	p1.set_Paddle_speedX(0);
	p1.set_Paddle_color();

	p2.set_Paddle_size(paddle_width, paddle_height); // player2 paddle
	p2.set_Paddle_position(w*0.5 - paddle_width/2, h*0.8 - paddle_height);
	p2.set_Paddle_speedX(0);
	p2.set_Paddle_color();

	/*p1.set_Paddle_item(ITEM3, 10);
	p2.set_Paddle_item(ITEM3, 10);
	p1.set_Paddle_item(ITEM1, 10);
	p2.set_Paddle_item(ITEM1, 10);*/

	if(!bufferPaddle.loadFromFile("./sound/collision.wav"))
		printf("cannot play");
	soundPaddle.setBuffer(bufferPaddle);
	soundPaddle.setLoop(false);
	soundPaddle.setVolume(50.0);


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

	//bgm
	if(!bgm.openFromFile("./sound/victory.wav"))
		printf("cannot open victory.wav");
	bgm.setVolume(25.0);
}

void Game::gameStart(){
	sf::Clock clock;
	float time = 0, delay = 800;
	while(window.isOpen() && is_start_page){
		time += clock.getElapsedTime().asMilliseconds();
		clock.restart();

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

		// twinkle
		if(time < delay) window.draw(start);
		if(time > 2*delay) time = 0;

		window.draw(text1);
		window.draw(text2);
		window.draw(prod);

		window.display();
	}

	gameRunning();
}

void Game::gameRunning(){
	sf::Clock clock;
	float p1_item2_t = 0, p1_item3_t = 0;
	float p2_item2_t = 0, p2_item3_t = 0;
	bool timer_flag[4]={0,};
	float delay = 10;
	while(window.isOpen() && !is_game_end){
		if(p1_item2_timer) p1_item2_t += clock.getElapsedTime().asSeconds();
		if(p1_item3_timer) p1_item3_t += clock.getElapsedTime().asSeconds();
		if(p2_item2_timer) p2_item2_t += clock.getElapsedTime().asSeconds();
		if(p2_item3_timer) p2_item3_t += clock.getElapsedTime().asSeconds();
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

		sf::Font font;
		font.loadFromFile("NanumGothic.ttf");
		sf::Text timer[4];

		if(p1_item2_t > delay){
			p1_item2_timer = false;
			p1_item2_t = 0;
			p1.set_Paddle_item_inactive(ITEM2);
			p1.set_Paddle_size(p1.get_Paddle_width() / 1.5, p1.get_Paddle_height());
			timer_flag[0]=false;
		}
		else if(p1_item2_t > 0){
			print_timer(&timer[0], &font, p1_item2_t, 60, 225);
			timer_flag[0]=true;			
		}
		if(p1_item3_t > delay){
			p1_item3_timer = false;
			p1_item3_t = 0;
			p1.set_Paddle_item_inactive(ITEM3);
			p2.set_Paddle_speedX(p2.get_Paddle_speedX() * 2);
			timer_flag[1]=false;
		}
		else if(p1_item3_t > 0){
			print_timer(&timer[1], &font, p1_item3_t, 60, 290);			
			timer_flag[1]=true;
		}
		if(p2_item2_t > delay){
			p2_item2_timer = false;
			p2_item2_t = 0;
			p2.set_Paddle_item_inactive(ITEM2);
			p2.set_Paddle_size(p2.get_Paddle_width() / 1.5, p2.get_Paddle_height());
			timer_flag[2]=false;
		}
		else if(p2_item2_t > 0){
			print_timer(&timer[2], &font, p2_item2_t, 400, 555);			
			timer_flag[2]=true;
		}
		if(p2_item3_t > delay){
			p2_item3_timer = false;
			p2_item3_t = 0;
			p2.set_Paddle_item_inactive(ITEM3);
			p1.set_Paddle_speedX(p1.get_Paddle_speedX() * 2);
			timer_flag[3]=false;
		}
		else if(p2_item3_t > 0){
			print_timer(&timer[3], &font, p2_item3_t, 400, 620);			
			timer_flag[3]=true;
		}
		object_draw();
		for(int i=0 ; i<4 ; i++){
			if(timer_flag[i])
				window.draw(timer[i]);
		}

		window.display();
	}

	while(window.isOpen() && is_game_end){
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}
		}

		sf::Font font;
		font.loadFromFile("NanumGothic.ttf");
		sf::Text text1, text2;

		window.clear(sf::Color::Black);

		if(is_game_end == 1) player1_win(&text1, &text2, &font);
		else if(is_game_end == 2) player2_win(&text1, &text2, &font);

		window.draw(text1);
		window.draw(text2);
		window.display();
	}
}

void Game::receiveKeyinputs(){
	if(event.type == sf::Event::KeyPressed){
		switch(event.key.code){
			// player1
			case sf::Keyboard::A:
				if(p2.get_Paddle_item_work(ITEM3)) p1.set_Paddle_speedX(-abs(p1.get_Paddle_speedX()));
				else p1.set_Paddle_speedX(-PADDLE_SPEED);
				break;
			case sf::Keyboard::S:
				p1.set_Paddle_speedX(0);
				break;
			case sf::Keyboard::D:
				if(p1.get_Paddle_speedX() != 0) p1.set_Paddle_speedX(abs(p1.get_Paddle_speedX()));
				else p1.set_Paddle_speedX(PADDLE_SPEED);
				break;
			case sf::Keyboard::Q:
				if(p1.get_Paddle_item(ITEM1) && !p1.get_Paddle_item_work(ITEM1)){
					p1.set_Paddle_item_active(ITEM1);
					p1.set_Paddle_item(ITEM1, p1.get_Paddle_item(ITEM1) - 1);
				}
				break;
			case sf::Keyboard::W:
				if(p1.get_Paddle_item(ITEM2) && !p1.get_Paddle_item_work(ITEM2)){
					p1.set_Paddle_item_active(ITEM2);
					p1.set_Paddle_item(ITEM2, p1.get_Paddle_item(ITEM2) - 1);
					p1.set_Paddle_size(p1.get_Paddle_width() * 1.5, p1.get_Paddle_height());
					p1_item2_timer = true;
				}
				break;
			case sf::Keyboard::E:
				if(p1.get_Paddle_item(ITEM3) && !p1.get_Paddle_item_work(ITEM3)){
					p1.set_Paddle_item_active(ITEM3);
					p1.set_Paddle_item(ITEM3, p1.get_Paddle_item(ITEM3) - 1);
					p2.set_Paddle_speedX(p2.get_Paddle_speedX() / 2);
					p1_item3_timer = true;
				}
				break;
				// player2
			case sf::Keyboard::Left:
				if(p1.get_Paddle_item_work(ITEM3)) p2.set_Paddle_speedX(-abs(p2.get_Paddle_speedX()));
				else p2.set_Paddle_speedX(-PADDLE_SPEED);
				break;
			case sf::Keyboard::Down:
				p2.set_Paddle_speedX(0);
				break;
			case sf::Keyboard::Right:
				if(p2.get_Paddle_speedX() != 0) p2.set_Paddle_speedX(abs(p2.get_Paddle_speedX()));
				else p2.set_Paddle_speedX(PADDLE_SPEED);
				break;
			case sf::Keyboard::Delete:
				if(p2.get_Paddle_item(ITEM1) && !p2.get_Paddle_item_work(ITEM1)){
					p2.set_Paddle_item_active(ITEM1);
					p2.set_Paddle_item(ITEM1, p2.get_Paddle_item(ITEM1) - 1);
				}
				break;
			case sf::Keyboard::End:
				if(p2.get_Paddle_item(ITEM2) && !p2.get_Paddle_item_work(ITEM2)){
					p2.set_Paddle_item_active(ITEM2);
					p2.set_Paddle_item(ITEM2, p2.get_Paddle_item(ITEM2) - 1);
					p2.set_Paddle_size(p2.get_Paddle_width() * 1.5, p2.get_Paddle_height());
					p2_item2_timer = true;
				}
				break;
			case sf::Keyboard::PageDown:
				if(p2.get_Paddle_item(ITEM3) && !p2.get_Paddle_item_work(ITEM3)){
					p2.set_Paddle_item_active(ITEM3);
					p2.set_Paddle_item(ITEM3, p2.get_Paddle_item(ITEM3) - 1);
					p1.set_Paddle_speedX(p1.get_Paddle_speedX() / 2);
					p2_item3_timer = true;
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
	window.draw(p1_item_slot);
	window.draw(p2_item_slot);

	// item1
	switch(p1.get_Paddle_item(ITEM1)){
		case 1: window.draw(p1_s_item1_1); break;
		case 2: window.draw(p1_s_item1_2); break;
		case 3: window.draw(p1_s_item1_3); break;
		default: break;
	}
	switch(p2.get_Paddle_item(ITEM1)){
		case 1: window.draw(p2_s_item1_1); break;
		case 2: window.draw(p2_s_item1_2); break;
		case 3: window.draw(p2_s_item1_3); break;
		default: break;
	}
	// item2
	switch(p1.get_Paddle_item(ITEM2)){
		case 1: window.draw(p1_s_item2_1); break;
		case 2: window.draw(p1_s_item2_2); break;
		case 3: window.draw(p1_s_item2_3); break;
		default: break;
	}
	switch(p2.get_Paddle_item(ITEM2)){
		case 1: window.draw(p2_s_item2_1); break;
		case 2: window.draw(p2_s_item2_2); break;
		case 3: window.draw(p2_s_item2_3); break;
		default: break;
	}
	// item3
	switch(p1.get_Paddle_item(ITEM3)){
		case 1: window.draw(p1_s_item3_1); break;
		case 2: window.draw(p1_s_item3_2); break;
		case 3: window.draw(p1_s_item3_3); break;
		default: break;
	}
	switch(p2.get_Paddle_item(ITEM3)){
		case 1: window.draw(p2_s_item3_1); break;
		case 2: window.draw(p2_s_item3_2); break;
		case 3: window.draw(p2_s_item3_3); break;
		default: break;
	}

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
		if(p1_b[i].get_Brick_hp() == 0) continue;
		p1_b[i].set_Brick_color();		
		window.draw(p1_b[i]);
	}
	for(int i=0; i<BRICKS_PER_ROW*BRICKS_PER_COL; i++){ // player2 bricks
		if(p2_b[i].get_Brick_hp() == 0) continue;
		p2_b[i].set_Brick_color();		
		window.draw(p2_b[i]);
	}

	p1.set_Paddle_color(); // player1 paddle
	window.draw(p1);

	p2.set_Paddle_color(); // player2 paddle
	window.draw(p2);

	for(int i=0; i<balls.size(); i++){ // balls
		balls[i].set_Ball_color();
		window.draw(balls[i]);
	}
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
			if(balls[i].get_Ball_y() - balls[i].get_Ball_radius() >= p1.get_Paddle_y() + p1.get_Paddle_height() 
					&& balls[i].get_Ball_y() - balls[i].get_Ball_radius() < p1.get_Paddle_y() + p1.get_Paddle_height() - balls[i].get_Ball_speedY()){
				if(balls[i].get_Ball_x() > p1.get_Paddle_x() && balls[i].get_Ball_x() < p1.get_Paddle_x() + p1.get_Paddle_width()){ // collide with p1_paddle
					soundPaddle.play();
					if(p1.get_Paddle_item_work(ITEM1) && !balls[i].get_Ball_active()){ // p1 was active && balls[i] was inactive
						p1.set_Paddle_item_inactive(ITEM1);
						balls[i].set_Ball_active();
					}

					if(balls[i].get_Ball_speedX() * p1.get_Paddle_speedX() > 0){ // accelerate
						balls[i].set_Ball_speedX(fast(balls[i].get_Ball_speedX()));
						balls[i].set_Ball_speedY(slow(balls[i].get_Ball_speedY()));
					}
					else{ // unaccelerate
						balls[i].set_Ball_speedX(slow(balls[i].get_Ball_speedX()));
						balls[i].set_Ball_speedY(fast(balls[i].get_Ball_speedY()));
					}

					balls[i].set_Ball_speedY(-balls[i].get_Ball_speedY());
				}
			}
			if(balls[i].get_Ball_y() - balls[i].get_Ball_radius() >= p2.get_Paddle_y() + p2.get_Paddle_height() 
					&& balls[i].get_Ball_y() - balls[i].get_Ball_radius() < p2.get_Paddle_y() + p2.get_Paddle_height() - balls[i].get_Ball_speedY()){ 
				if(balls[i].get_Ball_x() > p2.get_Paddle_x() && balls[i].get_Ball_x() < p2.get_Paddle_x() + p2.get_Paddle_width()){ // collide with p2_paddle
					soundPaddle.play();
					if(p2.get_Paddle_item_work(ITEM1) && !balls[i].get_Ball_active()){ // p1 was active && balls[i] was inactive
						p2.set_Paddle_item_inactive(ITEM1);
						balls[i].set_Ball_active();
					}				

					if(balls[i].get_Ball_speedX() * p2.get_Paddle_speedX() > 0){ // accelerate
						balls[i].set_Ball_speedX(fast(balls[i].get_Ball_speedX()));
						balls[i].set_Ball_speedY(slow(balls[i].get_Ball_speedY()));
					}
					else{ // unaccelerate
						balls[i].set_Ball_speedX(slow(balls[i].get_Ball_speedX()));
						balls[i].set_Ball_speedY(fast(balls[i].get_Ball_speedY()));
					}

					balls[i].set_Ball_speedY(-balls[i].get_Ball_speedY());
				}
			}

		}
		else{ // when ball moves top to down
			if(balls[i].get_Ball_y() + balls[i].get_Ball_radius() <= p1.get_Paddle_y() 
					&& balls[i].get_Ball_y() + balls[i].get_Ball_radius() > p1.get_Paddle_y() - balls[i].get_Ball_speedY()){
				if(balls[i].get_Ball_x() > p1.get_Paddle_x() && balls[i].get_Ball_x() < p1.get_Paddle_x() + p1.get_Paddle_width()){ // collide with p1_paddle
					soundPaddle.play();
					if(p1.get_Paddle_item_work(ITEM1) && !balls[i].get_Ball_active()){ // p1 was active && balls[i] was inactive
						p1.set_Paddle_item_inactive(ITEM1);
						balls[i].set_Ball_active();
					}

					if(balls[i].get_Ball_speedX() * p1.get_Paddle_speedX() > 0){ // accelerate
						balls[i].set_Ball_speedX(fast(balls[i].get_Ball_speedX()));
						balls[i].set_Ball_speedY(slow(balls[i].get_Ball_speedY()));
					}
					else{ // unaccelerate
						balls[i].set_Ball_speedX(slow(balls[i].get_Ball_speedX()));
						balls[i].set_Ball_speedY(fast(balls[i].get_Ball_speedY()));
					}

					balls[i].set_Ball_speedY(-balls[i].get_Ball_speedY());
				}
			}
			if(balls[i].get_Ball_y() + balls[i].get_Ball_radius() <= p2.get_Paddle_y() 
					&& balls[i].get_Ball_y() + balls[i].get_Ball_radius() > p2.get_Paddle_y() - balls[i].get_Ball_speedY()){
				if(balls[i].get_Ball_x() > p2.get_Paddle_x() && balls[i].get_Ball_x() < p2.get_Paddle_x() + p2.get_Paddle_width()){ // collide with p2_paddle
					soundPaddle.play();
					if(p2.get_Paddle_item_work(ITEM1) && !balls[i].get_Ball_active()){ // p1 was active && balls[i] was inactive
						p2.set_Paddle_item_inactive(ITEM1);
						balls[i].set_Ball_active();
					}

					if(balls[i].get_Ball_speedX() * p2.get_Paddle_speedX() > 0){ // accelerate
						balls[i].set_Ball_speedX(fast(balls[i].get_Ball_speedX()));
						balls[i].set_Ball_speedY(slow(balls[i].get_Ball_speedY()));
					}
					else{ // unaccelerate
						balls[i].set_Ball_speedX(slow(balls[i].get_Ball_speedX()));
						balls[i].set_Ball_speedY(fast(balls[i].get_Ball_speedY()));
					}

					balls[i].set_Ball_speedY(-balls[i].get_Ball_speedY());
				}
			}
		}
	}	
}
void Game::ball_brick_collision(Ball &ball){
	// p1_brick
	for(int i=0; i<p1_b.size(); i++){
		if(p1_b[i].get_Brick_hp() == 0) continue;

		bool collide_flag = false;
		if(ball.get_Ball_speedY() < 0){ // collide with p1_bricks downside
			if(abs(ball.get_Ball_y() - (p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height())) <= abs(ball.get_Ball_speedY())){
				if(i < 20 && p1_b[i+10].get_Brick_hp()) continue; // can't collide

				if(ball.get_Ball_x() >= p1_b[i].get_Brick_x() - gap*0.5 && ball.get_Ball_x() < p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width() + gap*0.5){
					ball.set_Ball_speedY(-ball.get_Ball_speedY());

					collide_flag = true;
				}
			}
		}
		else{ // collide with p1_bricks topside
			if(abs(ball.get_Ball_y() - p1_b[i].get_Brick_y()) <= abs(ball.get_Ball_speedY())){
				if(i >= 10 && p1_b[i-10].get_Brick_hp()) continue; // can't collide

				if(ball.get_Ball_x() >= p1_b[i].get_Brick_x() - gap*0.5 && ball.get_Ball_x() < p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width() + gap*0.5){
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
			if(abs(ball.get_Ball_x() - p1_b[i].get_Brick_x()) <= abs(ball.get_Ball_speedX())){	
				if(i%10 >= 1 && p1_b[i-1].get_Brick_hp()) continue; // can't collide

				if(ball.get_Ball_y() >= p1_b[i].get_Brick_y() - gap*0.5 && ball.get_Ball_y() < p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height() + gap*0.5){
					ball.set_Ball_speedX(-ball.get_Ball_speedX());

					collide_flag = true;

					soundBricks.play();
				}
			}
		}
		else{ // collide with p1_bricks rightside
			if(abs(ball.get_Ball_x() - (p1_b[i].get_Brick_x() + p1_b[i].get_Brick_width())) <= abs(ball.get_Ball_speedX())){
				if(i%10 < 9 && p1_b[i+1].get_Brick_hp()) continue; // can't collide

				if(ball.get_Ball_y() >= p1_b[i].get_Brick_y() - gap*0.5 && ball.get_Ball_y() < p1_b[i].get_Brick_y() + p1_b[i].get_Brick_height() + gap*0.5){
					ball.set_Ball_speedX(-ball.get_Ball_speedX());

					collide_flag = true;

					soundBricks.play();
				}
			}
		}

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
	text1->setCharacterSize(30);
	text1->setFillColor(sf::Color::Yellow);
	text1->setPosition(100.f, 450.f);

	text2->setString("PLAYER1 WINS");
	text2->setFont(*font);
	text2->setCharacterSize(30);
	text2->setFillColor(sf::Color::White);
	text2->setPosition(100.f, 600.f);
}
void player2_win(sf::Text* text1, sf::Text* text2, sf::Font* font){
	text1->setString("Congratulations!");
	text1->setFont(*font);
	text1->setCharacterSize(30);
	text1->setFillColor(sf::Color::Yellow);
	text1->setPosition(100.f, 450.f);

	text2->setString("PLAYER2 WINS");
	text2->setFont(*font);
	text2->setCharacterSize(30);
	text2->setFillColor(sf::Color::White);
	text2->setPosition(100.f, 600.f);
}
void print_timer(sf::Text* timer, sf::Font* font, float time, float x, float y){
	int t = 10-time;
	timer->setString(std::to_string(t));
	timer->setFont(*font);
	timer->setCharacterSize(30);
	timer->setFillColor(sf::Color::White);
	timer->setPosition(x, y);

}
