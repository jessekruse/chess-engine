#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "Bitboard.h"
#include <cmath>
#include "Tests.h"
#include "Position.h"

using namespace std;

int main() {
	FEN fTest = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 1 2";

	Position p;

	p.loadFEN(fTest);
	p.print();
}
