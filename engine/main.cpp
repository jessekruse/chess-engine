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

using namespace std;

int main() {
	init_attack_tables();

	int sq = squareIndex('d', '4');

	Bitboard occupied = sqIndextoBB(squareIndex('d', '6'));
	fillSq(occupied, squareIndex('g', '4'));
	
	printBB(rookAttacks(sq, occupied));

	run_tests();
}
