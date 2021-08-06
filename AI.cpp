#include <iostream>
#include <vector>
#include <cassert>

#include "board.hpp"

static inline void print_indent(int c) {
	for (int i = 0; i < c; i++) {
		std::cout << " ";
	}
}

static void print_board_line(Board& board) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			auto k = board.get_pos(i, j);
			std::cout << (!k ? '.' : (k == AI) ? 'X' : 'O');
		}
	}
}

//so two things to consider while scoring a move
//1. +1 if its a win for the computer, +-0 if tie, -1 if win for opponent.
//2. pick moves that will result in a win as fast as possible meaning least tree depth
//ok lets go
static int score_pos(Board& board, int tree_depth) {
//function is unfinished, TODO:
	int winner = board.check_for_win();
	bool tie = board.check_for_tie();
	
	if (winner) {
		//std::cout << "! ";
		return winner;
	}
	
	if (tie) {
		//std::cout << "? ";
		return 0;
	}

	int best_score = (board.get_cur_player() == AI ? -100000 : 100000);
	int op_i, op_j;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!board.get_pos(i, j)) {
				board.get_pos(i, j) = board.get_cur_player();			

//				print_indent(tree_depth);
//				print_board_line(board);
//				std::cout << '\n';
				//std::cout << board.get_cur_player() << ": " << s << '\n';

				board.switch_player();

				int s = score_pos(board, tree_depth + 1); 

				board.switch_player();

				if (board.get_cur_player() == AI) {
					if (s > best_score) {
						op_i = i;
						op_j = j;
						best_score = s;
					}
				} else {
					if (s < best_score) {
						op_i = i;
						op_j = j;
						best_score = s;
					}
				}
				board.get_pos(i, j) = 0;			
			}
		}
	}
	return best_score;	
}

//dummy function that will do for now and will be the actual minimax part
//int score_pos(int i, int j, Board board) {
//	return 1;
//}

//going through all moves we can make
Coor make_move(Board board) {
	assert(board.get_cur_player() == AI);
	int best_score = -10000000;
	int op_i, op_j;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int tree_depth = 0;
			if (!board.get_pos(i, j)) {
				board.get_pos(i, j) = AI;
				board.switch_player();
				int s = score_pos(board, tree_depth); 
				board.switch_player();
				if (s > best_score) {
					op_i = i;
					op_j = j;
					best_score = s;
				}			
				board.get_pos(i, j) = 0; 
			}
		}
	}
	std::cout << "move: " << op_i << ' ' << op_j << std::endl;
	return {op_i, op_j};
}
