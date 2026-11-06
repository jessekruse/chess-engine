#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "Bitboard.h"
#include <cmath>
#include "Tests.h"
#include "Position.h"
#include "Move.h"
#include <format>

using namespace std;

int main() {
	
	move_t from = squareIndex('e', '5');
	move_t to = squareIndex('d', '6');
	move_t flag = EP_CAPTURE;

	Move m(from,to,flag);

	cout << format("{:#x}\n", m.m) << endl;

	m.print_from();
	m.print_to();
	m.print_flag();

}
