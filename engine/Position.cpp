#pragma once
#include "Position.h"

void Position::loadFEN(FEN f) {
	fen = f;
}

void Position::print() {
	int num = 0;
	int row = 8;
	std::cout << row << ' ';
	for (auto c = fen.cbegin(); c != fen.cend(); ++c) {
		if (std::isdigit(*c)) {
			num = *c - '0';
			std::cout << std::string(num*2, ' ');
			continue;
		}
		if (std::isalpha(*c)) {
			std::cout << *c << ' ';
		}
		if (*c == '/') {
			std::cout << std::endl;
			row = --row;
			std::cout << row << ' ';
			continue;
		}
		if (*c == ' ') {
			break;
		}
	}

	std::cout << "\n  a b c d e f g h " << std::endl;
}

void Position::printFEN() {
	std::cout << fen << std::endl;
}