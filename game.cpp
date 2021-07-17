#include <iostream>
#include <vector>
#include <cassert>

class Board {
	int cur_player = 1; 										// here 1 means us, 0 means none, and -1 means opponent
	int spaces_filled = 0;
	std::vector<std::vector<int>> board;

public:
	Board() : board(3, std::vector<int>(3, 0)) {}

	int get_cur_player() const {
		return cur_player;
	}

	bool is_pos_valid(int row, int col) const {
		return row <= 2 && col <= 2 && row >= 0 && col >= 0;
	}

	int& get_pos(int row, int col) {
		assert(is_pos_valid(row, col));
		return board[row][col];
	}

	//false means invalid move
	bool place_move(int row, int col) {
		if (!is_pos_valid(row, col)) {
			return false;
		}

		if (get_pos(row, col)) {
			return false;
		}

		get_pos(row, col) = cur_player;
		cur_player *= -1;
		spaces_filled++;
		return true;
	}

	bool check_for_tie() const {
		return spaces_filled == 9;
	}

	//check if and who already won the game using brute force cuz im friking lazy
	int check_for_win() const {
		for (int i = 0; i < 3; i++) {
			if (board[i][0] == board[i][1] && board[i][2] == board[i][0]) {
				if (board[i][0])
					return board[i][0];
			} 
		}	
		
		for (int i = 0; i < 3; i++) {
			if (board[0][i] == board[1][i] && board[2][i] == board[0][i]) {
				if (board[0][i])
					return board[0][i];
			} 
		}	

		if ((board[0][0] == board[1][1] && board[2][2] == board[0][0]) 
				|| (board[2][0] == board[1][1] && board[1][1] == board[0][2])) {
			if (board[1][1])
				return board[1][1];
 		}
		return 0;
	}
	
	void print_board() const {
		for (auto& v : board) {
			for (int p : v) {
				std::cout << (p == 1 ? 'X' : (!p ? '.' : 'O')) << ' ';
			}
			std::cout << std::endl;
		}
	}
};

int main() {
	Board b;

	while (!b.check_for_tie()) {
		int w = b.check_for_win();
		
		if (w) {
			std::cout << (w == 1 ? 'X' : 'O') << " won" << std::endl;
			break;
		}

		int row, col;

		b.print_board();
		std::cout << std::endl;
		printf("%c's turn: ", b.get_cur_player() == 1 ? 'X' : 'O');
		std::cin >> row >> col;
		if (!b.place_move(row, col)) 
			std::cout << "move invalid" << std::endl;
	}
	b.print_board();
}
