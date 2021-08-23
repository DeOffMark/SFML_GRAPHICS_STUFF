//Fractal viewer by DeOffMark
//This application is going to display mandelbrot set, 
//and by clicking at one of its points in space it will display Julia set using clicked complex coordinates
//You can also zoom-in, set iteration number and apply different color pallets
//By plan this will be utilized by simple GUI as button sprites

#include <iostream>
#include <SFML/Graphics.hpp>
// this will be a simple app no need for framework
const int W = 1280, H = 720;
int iterations = 500;
bool isMandebrot = true;
int pallete = 3; // number that changes color pallete for a selected fractal
// 1: black/white, 2: greyscale, 3: hue
//TODO: Add more palletes
float scaleFactor = 1.0f; // scale factor for zooming into fractal
sf::Vector2f offSet(0.f, 0.f); //offset factor for zooming into specific point

 float length2(sf::Vector2f& vec) {
	return vec.x * vec.x + vec.y * vec.y;
}

float length2(sf::Vector2f& vec1, sf::Vector2f& vec2) {
	return (vec2.x - vec1.x) * (vec2.x - vec1.x) + (vec2.y - vec1.y) * (vec2.y - vec1.y);
}

 float length(sf::Vector2f& vec1, sf::Vector2f& vec2) {
	return std::sqrtf(length2(vec1, vec2));
}

  float length(sf::Vector2f& vec)  {
	 return std::sqrtf(length2(vec));
 }

 sf::Vector2f normalize(sf::Vector2f& vec) {
	return { vec.x / length(vec), vec.y / length(vec) };
}


int clamp(int value, int min, int max) {
	return std::max(min, std::min(max, value));
}

int main() {
	sf::RenderWindow app(sf::VideoMode(W, H), "Fractal Viewer");
	app.setFramerateLimit(60);
	//load initial shader that will display mandelbrot set
	sf::Shader* mandelShader = new sf::Shader();
	mandelShader->loadFromFile("fractal.glsl", sf::Shader::Fragment);
	//give shader initaly resolution and boolean
	mandelShader->setUniform("uPallete", pallete);
	mandelShader->setUniform("uScreenRes", sf::Glsl::Vec2(app.getSize()));
	mandelShader->setUniform("uIsMandelbrot", isMandebrot);
	//render texture for a mandelbrot fractal
	sf::RenderTexture mandelTexture;
	mandelTexture.create(W, H);
	sf::Sprite mandelSprite(mandelTexture.getTexture());

	bool justOpened = true;
	int justOpenediters = 0;

	sf::Vector2f boundaryS(-2.f, -1.f);
	sf::Vector2f boundaryE(1.f, 1.f);
	
	while (app.isOpen()) {
		//handle events
		sf::Event event; 
		while (app.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				app.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					app.close();
					break;
				case sf::Keyboard::Up:
					if(!justOpened)iterations = clamp(iterations + 5, 0, 1000);
					break;
				case sf::Keyboard::Down:
					if (!justOpened)iterations = clamp(iterations - 5, 0, 1000);
					break;
				case sf::Keyboard::Num1:
					pallete = 1;
					break;
				case sf::Keyboard::Num2:
					pallete = 2;
					break;
				case sf::Keyboard::Num3:
					pallete = 3;
					break;
				}
				break;
			case sf::Event::MouseWheelScrolled:
				if (!justOpened) {
					float index = 1.0f;
					if (event.mouseWheelScroll.delta < 0.f) {
						index = 0.9f;
					}
					else {
						index = 1.1f;
					}
					scaleFactor = std::max(scaleFactor * index, 1.0f);
					
					sf::Vector2f mousePos = { float(sf::Mouse::getPosition(app).x), float(H) - float(sf::Mouse::getPosition(app).y) };
				
					mousePos.x = (boundaryS.x + mousePos.x * (boundaryE.x - boundaryS.x) / float(W)) / scaleFactor;
					mousePos.y = (boundaryS.y + mousePos.y * (boundaryE.y - boundaryS.y) / float(H)) / scaleFactor;
					//FOR DEBUG ONLY
					app.setTitle("Mouse pos: x = " + std::to_string(mousePos.x) + " y = " + std::to_string(mousePos.y));
					offSet.x =  std::max(std::min(offSet.x + mousePos.x, boundaryE.x), boundaryS.x);
					offSet.y =  std::max(std::min(offSet.y + mousePos.y, boundaryE.y), boundaryS.y);
			
				}
				break;
			}
		}
		//update()
		mandelShader->setUniform("uOffSet", offSet);
		mandelShader->setUniform("uScale", scaleFactor);
		if (justOpened) {
			mandelShader->setUniform("uIterations", justOpenediters);
			justOpenediters+=5;
			if (justOpenediters >= iterations) {
				justOpenediters = iterations;
				justOpened = false;
			}
		}
		else {
			
			mandelShader->setUniform("uPallete", pallete);
			mandelShader->setUniform("uIterations", iterations);
		}
		
		app.clear();
		app.draw(mandelSprite, mandelShader);
		app.display();
	}
	//delete all new pointers
	delete mandelShader;
	return 0;
}