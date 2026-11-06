#include "Move.h"
#include <iostream>
#include "ChessFunctions.h"
#include <string>
#include <array>

void Move::print_from() const {
	std::cout << "Starting square: " << squareName(get_from()) << std::endl;
}

void Move::print_to() const {
	std::cout << "Ending square: " << squareName(get_to()) << std::endl;
}

void Move::print_flag() const {
	move_t flag = get_flag();

	std::array<std::string, 16> flag_names = {
		"Flag: quiet move",
		"Flag: double pawn push",
		"Flag: king castle",
		"Flag: queen castle",
		"Flag: capture",
		"Flag: en passant capture",
		"Flag: promote to knight",
		"Flag: promote to bishop",
		"Flag: promote to rook",
		"Flag: promote to queen",
		"Flag: promote to knight with capture",
		"Flag: promote to bishop with capture",
		"Flag: promote to rook with capture",
		"Flag: promote to queen with capture"
	};

	std::cout << flag_names[flag] << std::endl;

}

