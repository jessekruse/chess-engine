#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "Bitboard.h"
#include <cmath>
#include "Tests.h"
#include "Position.h"

using namespace std;

int main() {
	FEN fTest = "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w - f6 0 3";

	Position p;
	p.loadFEN(fTest);
	p.print();

}
