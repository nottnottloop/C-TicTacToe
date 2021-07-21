#include <iostream>
#include <ctime>
#include <cctype>
#include <limits>

using std::cout;
using std::cin;

char board[9] = {' ', ' ', ' ',
                 ' ', ' ', ' ',
                 ' ', ' ', ' '};

bool game_initialised = false;
bool human_to_move = false;
bool tutorial_done = false;
int input = -1;
char winner;

void print_board() {
    cout << " " << board[0] << " " << "|" << " " << board[1] << " " << "|" << " " << board[2] << " " << "\n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " " << "|" << " " << board[4] << " " << "|" << " " << board[5] << " " << "\n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " " << "|" << " " << board[7] << " " << "|" << " " << board[8] << " " << "\n";
}

bool is_legal(char pos) {
    return board[pos] == ' ';
}

void comp_moves() {
    char comp_pos;
    while (!is_legal((comp_pos = rand() % 9))) {
        continue;
    }
    board[comp_pos] = 'O';
    human_to_move = !human_to_move;
}

void decide_who_starts() {
    if ((rand() % 2) < 1) {
        human_to_move = false;
        cout << "\nIt has been chosen that I will move first :)\n";
    } else {
        human_to_move = true;
        cout << "\nIt looks like you're moving first :O\n";
    }
    game_initialised = true;
}

void make_move(char pos) {
    pos--;
    if (!is_legal(pos)) {
        cout << "That position is taken. Try again.\n";
    } else {
        board[pos] = 'X';
        human_to_move = !human_to_move;
    }
}

char take_input() {
    while (1) {
        if (!(cin >> input) || 1 > input || input > 9) {
            print_board();
            cout << "Invalid input. Enter a number between 1 and 9.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return input;
    }
}

bool check_win(char check) {
        // Horizontal
        if (board[0] == check && board[1] == check && board[2] == check || board[3] == check && board[4] == check && board[5] == check || board[6] == check && board[7] == check && board[8] == check) {
            winner = check;
            return true;
        }
        // Vertical
        if (board[0] == check && board[3] == check && board[6] == check || board[1] == check && board[4] == check && board[7] == check || board[2] == check && board[5] == check && board[8] == check) {
            winner = check;
            return true;
        }
        // Diagonal
        if (board[0] == check && board[4] == check && board[8] == check || board[2] == check && board[4] == check && board[6] == check) {
            winner = check;
            return true;
        }
    return false;
}

void announce_winner() {
    print_board();
    if (winner == 'O') {
        cout << "Hahaha! I won!!! Better luck next time, pal\n";
    } else {
        cout << "Crikey, you won! Aw jeez...\n";
    }
}

void ask_for_repeat() {
    char answer;
    cout << "Would you like to play again? (y/n)\n";
    while (1) {
        cin >> answer;
        answer = tolower(answer);
        if (answer == 'y') {
            game_initialised = false;
            for (int i = 0; i < 9; ++i) {
                board[i] = ' ';
            }
            break;
        } else if (answer == 'n') {
            exit(0);
        } else {
            cout << "Please enter valid input (y/n)\n";
        }
    }
}

bool check_stalemate() {
    for (int i = 0; i < 8; ++i) {
        if (is_legal(i)) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "Welcome to a really cool C++ TicTacToe game :O\n";
    cout << "I will try to beat you!!! Watch out\n";
    while (true) {
        if (!game_initialised) {
            decide_who_starts();
        }
        if (!tutorial_done) {
            cout << "Select where you want to move from 1 to 9. 1, 2 and 3 are top, 4, 5 and 6 for middle, 7, 8 and 9 for the bottom.\n";
            tutorial_done = !tutorial_done;
        }
        if (human_to_move) {
            print_board();
            make_move(take_input());
        }
        else comp_moves();
        if (check_win('X') || check_win('O')) {
            announce_winner();
            ask_for_repeat();
        }
        if (check_stalemate() && game_initialised) {
            cout << "STALEMATE!!!!\n";
            ask_for_repeat();
        }
    }
}