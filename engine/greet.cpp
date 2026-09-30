#include "greet.h"

void greet() {
	std::cout << "Hello, world!" << std::endl;

	int i = 0;

	while (i < 5) {
		std::cout << i << std::endl;
		i++;
	}
}