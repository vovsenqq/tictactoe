#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::string;

//########################################################################################
void print_board(vector<int> board) {
    system("cls");
    vector<char> convert_values(vector<int> board);
    vector<char> n_board = convert_values(board);
    int len_board = board.size();
    int size = sqrt(len_board);
    for (int i = 0; i < len_board; i += size) {
        for (int j = 0; j < size - 1; j++) {
            cout << "     |";
        }
        cout << "\n";
	int pos = i;
        for (int j = 0; j < size; j++) {
            
            if (j != size - 1) {
                cout << "  " << n_board[pos] << "  |";
            } else {
                cout << "  " << n_board[pos];
            }
            pos++;
        }
        cout << "\n";
        for (int j = 0; j < size; j++) {
            if (i != len_board - size) {
                if (j != size - 1) {
                cout << "_____|";
                } else {
                cout << "_____";
                }
            } else if (j < size - 1) {
                cout << "     |";
            }
        }
        cout << "\n";
    }
    return;
}


vector<int> gen_board(int size) {
    vector<int> board;
    int zxc = size * size;
    for (int i = 0; i < zxc; i++) {
        board.push_back(0);
    }
    return board;
}


vector<char> convert_values(vector<int> board) {
    int len_board = board.size();
    vector<char> n_board;
    for (int i = 0; i < len_board; i++) {
        if (board[i] == 0) {
            n_board.push_back(' ');
        } else if (board[i] == 1) {
            n_board.push_back('X');
        } else if (board[i] == -1) {
            n_board.push_back('O');
        }
    }
    return n_board;
}


void make_move(vector<int> &board, int pos, int turn) {
    board[pos] = turn;
}
//########################################################################################


int evaluation(vector<int> board) {    //bad realization
    int len_board = board.size();
    int size = sqrt(len_board);
    vector<vector<int> > res;
    vector<int> tmp;

    for (int i = 0; i < len_board; i+=size) {
        tmp.clear();
        for (int j = i; j < size + i; j++) {
            tmp.push_back(board[j]);
        }
        res.push_back(tmp);
    }

    for (int i = 0; i < size; i++) {
        tmp.clear();
        for (int j = i; j < len_board; j+=size) {
            tmp.push_back(board[j]);
        }
        res.push_back(tmp);
    }

    tmp.clear();
    for (int i = 0; i < len_board; i+=size + 1) {
        tmp.push_back(board[i]);
	}
    res.push_back(tmp);
    tmp.clear();

    for (int i = size - 1; i <= len_board - size; i+=size-1) {
        tmp.push_back(board[i]);
    }
    res.push_back(tmp);
    tmp.clear();

    for (int i = 0; i < size * 2 + 2; i++) {
	    if (std::equal(res[i].begin() + 1, res[i].end(), res[i].begin()) && res[i][0] != 0) {
	        if (res[i][0] == 1) {
            return 10;
            }
            else {
                return -10;
            }
	    }
    }

    return 0;
}


vector<vector<int> > gen_boards(vector<int> board, int turn) {
    int len_board = board.size();
    vector<vector<int> > res;
    vector<int> tmp;
    for (int i = 0; i < len_board; i++) {
        tmp.clear();
        if (board[i] == 0) {
	        tmp = board;
	        tmp[i] = turn;
	        res.push_back(tmp);
        }
    }
    return res;
}


bool isMovesLeft(vector<int> board) {
    int len_board = board.size();
    for (int i = 0; i < len_board; i++) {
        if (board[i] == 0) {
            return 1;
        }
    }
    return 0;
}


int minimax(vector<int> board, bool maximizingPlayer) {
    int score = evaluation(board);
    if (score == 10) {return score;}
    if (score == -10) {return score;}
    if (isMovesLeft(board) == false) {return 0;}

    if (maximizingPlayer) {
        int maxEval = -1000;
        vector<vector<int> > child_pos = gen_boards(board, 1);
        int len_pos_moves = child_pos.size();
        for (int i = 0; i < len_pos_moves; i++) {
            maxEval = std::max(maxEval, minimax(child_pos[i], false));
        }
        return maxEval;
    } else {
        int minEval = 1000;
        vector<vector<int> > child_pos = gen_boards(board, -1);
        int len_pos_moves = child_pos.size();
        for (int i = 0; i < len_pos_moves; i++) {
            minEval = std::min(minEval, minimax(child_pos[i], true));
        }
        return minEval;
    }
}


int findBestAiMove(vector<int> board) {
    int len_board = board.size();
    int best = 1000;
    int bebra = 0;
    for (int i = 0; i < len_board; i++) {
           if (board[i] == 0) {
               board[i] = -1;
               int val = minimax(board, true);
               board[i] = 0;
               if (val < best) {
                   best = val;
                   bebra = i;
               }
           }
        }
    return bebra;
}


int main() {
    vector<int> board = gen_board(3);
    int asd = 0;
    while (1) {
        print_board(board);
        cout << "Choose your square: \n";
        cin >> asd; 
        if (board[asd] == 0) {
            make_move(board, asd, 1);
            print_board(board);
            if (evaluation(board) == 10) {
                cout << "You win!";
                break;
            }
        }

        if (!isMovesLeft(board)) {
            cout << "Draw!";
            break;
        }
        
        make_move(board, findBestAiMove(board), -1);
        print_board(board);
        if (evaluation(board) == -10) {
            cout << "You loose";
            break;
           }
        if (!isMovesLeft(board)) {
            cout << "Draw!";
            break;
        }
    }

    return 1;
}
