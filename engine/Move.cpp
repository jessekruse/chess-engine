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
	print_from();
	print_to();
	print_flag();
}

void MoveList::add(Move m) {

	Move empty;

	for (auto i = list.begin(); i != list.end(); ++i) {
		if (*i != empty) continue;
		if (*i == empty) {
			*i = m;
			break;
		}
	}
}

int MoveList::count() {
	int count = 0;
	Move empty;

	for (auto i = list.begin(); i != list.end(); ++i) {
		if (*i != empty) ++count;
		if (*i == empty) break;
	}
	return count;
}