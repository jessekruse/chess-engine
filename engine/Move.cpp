#include "Move.h"
#include <iostream>
#include "ChessFunctions.h"
#include <cassert>


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

void Move::update(const std::string& from, const std::string& to, move_t flag) {
	move_t f = squareIndex(from[0], from[1]);
	move_t t = squareIndex(to[0], to[1]);

	m = (f | (t << 6) | (flag << 12));
}

void MoveList::add(Move m) {
	assert(count < 256);
	list[count] = m;
	count++;
}

int MoveList::get_count() const {
	return count;
}

void MoveList::clear() {
	count = 0;
}

