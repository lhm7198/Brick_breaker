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
