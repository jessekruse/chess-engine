// engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "bitboard.h"
#include <cmath>
#include "Tests.h"

using namespace std;

int main() {
	

	run_bitboard_tests();
	cout << "All tests cleared" << endl;
}
