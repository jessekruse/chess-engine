#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "Bitboard.h"
#include <cmath>
#include "Tests.h"
#include "Position.h"
#include "Move.h"
#include <format>
#include "Attacks.h"
#include "Movegen.h"

using namespace std;

int main() {
	init_attack_tables();

	FEN fStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	FEN fRookKingTest = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1";
	FEN fPawnTest = "1n5k/P7/8/8/8/8/6K1/8 w - - 0 1";

	Position p;
	p.loadFEN(fPawnTest);
	MoveList ml;

	p.print();

	cout << ml.get_count() << endl;

	generateMoves(p, ml);

	cout << ml.get_count() << endl;

	for (int i = 0; i < ml.count; ++i) {
		if (ml.list[i].get_from() == squareIndex('a','7'))	ml.list[i].print_flag();
	}

	run_tests();
}
