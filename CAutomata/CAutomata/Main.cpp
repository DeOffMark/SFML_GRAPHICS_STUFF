#include "Application.h"
#include <iostream>
//Cellular automata, by DeOffMark
//This application simulates similarly to Game Of Life, 
//However, some rules were twisted, resulting shape related to Sierpinski Triangle



int main() {
	std::cout << "Game of Life made by Mark Medvedev!\n"
		<< "Press P to pause the game and draw cells and press P again start a simulation\n"
		<< "Press C to clear the map\n"
		<< "Use LMB to draw living cells\n"
		<< "Press RMB to erase living cells\n"
		<< "Mouse Wheel to increase/decrease size of the draw sector" << std::endl;
	Application app("Game of Life", 1280, 960, 1, 1);

	app.run();
	return 0;
}