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

	int s = 28;

	printBB(knightAttacks[s]);
	printBB(kingAttacks[s]);
	printBB(pawnAttacks[WHITE][s]);
	printBB(pawnAttacks[BLACK][s]);

}
