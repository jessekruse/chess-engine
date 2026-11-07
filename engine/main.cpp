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

	int sq = squareIndex('e', '4');

	Bitboard occupied = sqIndextoBB(squareIndex('c', '2'));
	fillSq(occupied, squareIndex('b', '4'));
	
	printBB(rookAttacks(sq, occupied));
	printBB(bishopAttacks(sq, occupied));
	printBB(queenAttacks(sq, occupied));
}
