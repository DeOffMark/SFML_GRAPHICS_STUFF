#include <iostream>
#include <complex>
const int X =150, Y = 100;
const int iterations = 100;
int main() {
	std::cout << "Mandelbrot set\n" << std::endl;
	
	for (unsigned int y = 0; y <= Y; ++y) {
		for (unsigned int x = 0; x <= X; ++x) {
			double r = -2.0 + ((double(x) / (double(X)/2.0)) * 2.0); // get a real complex number from - 2 to 2
			double i = -2.0 + ((double(y) / (double(Y)/2.0)) * 2.0); // get an imaginary complex number from -2 to 2
			double a = r; //cx
			double b = i; //cy
			//r = -0.7600;
			//i = 0.0900;
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
	
	return EXIT_SUCCESS;
}