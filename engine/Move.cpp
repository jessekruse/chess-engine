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

void Move::print_move() const {
	if (m == 0) {
		std::cout << "Empty move" << std::endl;
	}
	else {
		print_from();
		print_to();
		print_flag();
	}
}

void MoveList::add(Move m) {
	list[count] = m;
	count++;
}

int MoveList::get_count() const {
	return count;
}

void MoveList::clear() {
	Move empty;
	list.fill(empty);
	count = 0;
}