/*
*	SW3 (SSE2034-41) Term Project
*	
*	Briefly explain : Declare game object
*
*	Copyright 2021 by 3-codiots
*/

#include "GameRunner.h"

Game::Game(int w, int h){
	screen_width = w;
	screen_height = h;

	is_start_page = true;

	// Players

	// Bricks
	brick_width = w * 0.09;
	brick_height = h * 0.04;
	gap = ((w / 11) / 13) * 1.5;
	for(int i=0; i<10; i++){
		bricks.push_back(Brick(brick_width, brick_height, gap + i*(brick_width+gap), gap + window.getSize().y*0.11));
	}
	
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
		sf::Text text1,text2;
		sf::Text prod;
		sf::Text start;
		sf::Font font1;
		sf::Font font2;
		if(!font1.loadFromFile("RixVideoGame Bold.ttf")){
			;
		}
		if(!font2.loadFromFile("NanumGothic.ttf")){
			;
		}
		text1.setFont(font1);
		text2.setFont(font1);
		prod.setFont(font2);
		start.setFont(font1);
		text1.setString("BRICKS");
		text2.setString("BREAKER");
		start.setString("Press SpaceBar To Start !");
		prod.setString("Prod by 3-codiots");
		text1.setCharacterSize(100);
		text2.setCharacterSize(100);
		start.setCharacterSize(28);
		prod.setCharacterSize(15);
		start.setOutlineColor(sf::Color::Blue);
		start.setOutlineThickness(2.f);
		text1.setFillColor(sf::Color::Red);
		text2.setFillColor(sf::Color::Yellow);
		start.setFillColor(sf::Color::Green);
		prod.setFillColor(sf::Color::Blue);
		prod.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text1.setPosition(-10.f, 175.f);
		text2.setPosition(120.f, 180.f);
		text1.setRotation(-30.f);
		start.setPosition(105.f, 650.f);
		prod.setPosition(170.f,775.f);

		window.clear(sf::Color::Black);
		window.draw(text1);
		window.draw(text2);
		window.draw(start);
		window.draw(prod);
		window.display();
	}

	window.clear(sf::Color::Black);

	gameRunning();
}

void Game::gameRunning(){
	while(window.isOpen()){
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();
			}
		}

		draw();
		window.display();
	}
}

void Game::draw(){
	for(int i=0; i<bricks.size(); i++){
		window.draw(bricks[i]);
	}
}
