#include <iostream>
#include <vector>
#include <cassert>

// the code's a bit sad rn :(
enum {
    OPPONENT = -1,
    AI = 1,
};

struct Coor {
	int i, j;
};

class Board {
    int cur_player = OPPONENT;                               // here 0 means none
    std::vector<std::vector<int>> board;

public:
    Board() : board(3, std::vector<int>(3, 0)) {}

    int get_cur_player() const {
        return cur_player;
    }

    void switch_player() {
        cur_player *= -1;
    }

    bool is_pos_valid(int row, int col) const {
        return row <= 2 && col <= 2 && row >= 0 && col >= 0;
    }

    int& get_pos(int row, int col) {
        assert(is_pos_valid(row, col));
        return board[row][col];
    }

	// board[{1, 0}]
	int& operator[](std::pair<int,int> const& loc);
	int operator[](std::pair<int,int> const& loc) const;


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
        //spaces_filled++;
        return true;
    }

	//check if game tied
    bool check_for_tie() const {
		int c = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (!board[i][j]) {
					c++;
				}
			}
		}
		return c == 0;
    }

    //check if and who already won the game using brute force cuz im friking lazy
	//returns 1 if compooter wins, -1 if oppenent wins, and 0 if no wins
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
	
	//print go brrrrrrrr
    void print_board() const {
        for (auto& v : board) {
            for (int p : v) {
                std::cout << (p == AI ? 'X' : (!p ? '.' : 'O')) << ' ';
            }
            std::cout << std::endl;
        }
    }
};
