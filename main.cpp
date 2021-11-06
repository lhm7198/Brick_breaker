/*
*	SW3 (SSE2034-41) Term Project
*	Copyright 2021 by 3-codiots
*	Members : Jasung Koo   (2016311909)
*		  Jiho Lee     (2016313011)
*		  Hyeonmin Lee (2016310191)
*/


#include <SFML/Graphics.hpp>
#include "GameRunner.h"

int main(){
	int Screen_Width = 800;
	int Screen_Height = 480;

	Game game(Screen_Width, Screen_Height);

	game.gameStart();

	return 0;
}
