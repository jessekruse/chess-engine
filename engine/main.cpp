// engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "bitboard.h"

using namespace std;

int main() {

	int a1 = squareIndex('a', '1');
	int e4 = squareIndex('e', '4');
	int h8 = squareIndex('h', '8');

	Bitboard b = sqIndextoBB(a1);
	fillSq(b, e4);
	fillSq(b, h8);

	printBB(b);
}
