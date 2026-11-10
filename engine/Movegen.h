#pragma once

#include "Position.h"
#include "Move.h"
#include "Bitboard.h"
#include "Attacks.h"

void generateMoves(const Position& p, MoveList& move_list);