#include "Move.h"
#include <iostream>
#include "ChessFunctions.h"


void Move::print_from() const {
	std::cout << "Starting square: " << squareName(get_from()) << std::endl;
}

void Move::print_to() const {
	std::cout << "Ending square: " << squareName(get_to()) << std::endl;
}

void Move::print_flag() const {
	move_t flag = get_flag();

	std::cout << flag_names[flag] << std::endl;

}

