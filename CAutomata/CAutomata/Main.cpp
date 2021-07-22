#include "Application.h"
//Cellular automata, by DeOffMark
//This application simulates similarly to Game Of Life, 
//However, some rules were twisted, resulting shape related to Sierpinski Triangle



int main() {
	Application app("Game of Life", 640, 480, 1, 1);

	app.run();
	return 0;
}