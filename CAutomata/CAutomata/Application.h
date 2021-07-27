#include <SFML/Graphics.hpp>
#include "Cell.h"

class Cell;

class Application {
public:
	 Application(std::string name, const unsigned int width, const unsigned int height, int scaleX, int scaleY);
	  
	 const sf::RenderWindow& getWindow() const;
	 void run();
private:
	int getIndex(int x, int y);
	bool isRun;
	float drawradius;
	void handleEvents();
	sf::RenderWindow mApp;
	int mWidth, mHeight;
	std::vector<sf::Vertex> mPixels;
	std::vector<Cell> mCells;
};