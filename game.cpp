#include <iostream>
#include <vector>
#include <cassert>

#include "board.hpp"

//right now ai is X
//and X usally has to go first

Coor make_move(Board);

int main() {
	Board b;
//note to self:
//please rewrite this entire main function, 
	while (true) {
		int w = b.check_for_win();

		if (b.check_for_tie() && !w) 
			break;
		
		if (w) {
			std::cout << (w == AI ? 'X' : 'O') << " won" << std::endl;
			b.print_board();
			exit(0);
		}

		int row, col;

		b.print_board();
		std::cout << std::endl;
		printf("%c's turn: ", b.get_cur_player() == AI ? 'X' : 'O');

		if (b.get_cur_player() == AI) {
			std::cout << std::endl;
			Coor c = make_move(b);
			b.place_move(c.i, c.j);
		} else {
			std::cin.clear();
			std::cin >> row >> col;
			if (!b.place_move(row, col)) 
				std::cout << "move invalid" << std::endl;
		}
	}

	b.print_board();
	std::cout << "Tied" << std::endl;
}
