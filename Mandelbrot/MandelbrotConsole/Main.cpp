//Mandelbrot/Julia set on cmd console by DeOffMark
//This program simply creates a fractal by your request


#include <iostream>
#include <complex>
const int X =100, Y = 50;
const int iterations = 100;
int main() {
	std::cout << "Welcome to Complex Plane Fractal Builder\n" << std::endl; //greeting message
	bool isAppdone = false;
	do {
		//select which complex fractal to draw
		char fractChoice; 
		bool fractChoiceDone = false;
	
		double jX = -1.0, jY = -1.0;
		do {
			std::cout << "Which fractal do you wish to create? Mandelbrot(m) or Julia(j) set? Or Press(x) to exit: ";
			std::cin >> fractChoice;
			switch (std::tolower(fractChoice)) {
			case 'm':
				std::cout << "Chosen: Mandelbrot Set!\n";
				std::system("pause");
				fractChoiceDone = true;
				break;
			case 'j':
				std::cout << "Chosen: Julia Set!\n\nFor Julia set, please enter its values\n";
				std::cout << "Set constants for real and imaginary number: ";
				std::cin >> jX >> jY;
				std::system("pause");
				fractChoiceDone = true;
				break;
			case 'x':
				std::cout << "Goodbye!\n";
				isAppdone = true;
				fractChoiceDone = true;
				break;
			default:
				std::cout << "Error: Unrecognizable input. Please entee 'm' or 'j' to choose a fractal\n";
				break;
			}
		} while (!fractChoiceDone);

		if (isAppdone)
			break;

		
		for (unsigned int y = 0; y <= Y; ++y) {
			for (unsigned int x = 0; x <= X; ++x) {
				double r, i;
				if (std::tolower(fractChoice) == 'j') {
					r = -2.0 + ((double(x) / (double(X) / 2.0)) * 2.0); // get a real complex number from - 2 to 2
					i = -1.5 + ((double(y) / (double(Y) / 2.0)) * 1.5); // get an imaginary complex number from -2 to 2
				}
				else {
					r = -2.0 + ((double(x) / (double(X) / 2.0)) * 1.5); // get a real complex number from - 2 to 1.5
					i = -1.0 + ((double(y) / (double(Y) / 2.0)) * 1.0); // get an imaginary complex number from -1 to 1
				}

				double a = r; //cx
				double b = i; //cy
				if (std::tolower(fractChoice) == 'j') {
					r = jX;
					i = jY;
				}
			
				int n = 0; 
				while (n < iterations) {
					double aa = a * a;
					double bb = b * b;
				
					double twoab = 2.0 * a * b;
					a = aa - bb + r;
					b = twoab + i;
					if (a > 2.0 || b > 2.0)
						break;
					++n;
				}
				if (n == iterations) {
					std::cout << '#';
				}
				else if (n > iterations * 0.7f) {
					std::cout << '*';
				}
				else if (n > iterations * 0.4f) {
					std::cout << '.';
				}
				else {
					std::cout << ' ';
				}
			}
			std::cout << '\n';
		}
	} while (!isAppdone);
	return EXIT_SUCCESS;
}