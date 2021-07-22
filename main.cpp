#include <iostream>
#include <ctime>
#include <cctype>
#include <limits>
#include <vector>
#include <algorithm>
#include <stdint.h>

using std::cout;
using std::cin;

char board[9] = {' ', ' ', ' ',
                 ' ', ' ', ' ',
                 ' ', ' ', ' '};

bool game_initialised = false;
bool human_to_move = false;
bool tutorial_done = false;

char winner;

int wins = 0;
int losses = 0;

void print_board() {
    cout << " " << board[0] << " " << "|" << " " << board[1] << " " << "|" << " " << board[2] << " " << "\n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " " << "|" << " " << board[4] << " " << "|" << " " << board[5] << " " << "\n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " " << "|" << " " << board[7] << " " << "|" << " " << board[8] << " " << "\n";
}

bool is_legal(short pos) {
    return board[pos] == ' ';
}

bool check_win(char check, bool testing = false) {
        // Horizontal
        if (board[0] == check && board[1] == check && board[2] == check || board[3] == check && board[4] == check && board[5] == check || board[6] == check && board[7] == check && board[8] == check) {
            if (!testing) winner = check;
            return true;
        }
        // Vertical
        if (board[0] == check && board[3] == check && board[6] == check || board[1] == check && board[4] == check && board[7] == check || board[2] == check && board[5] == check && board[8] == check) {
            if (!testing) winner = check;
            return true;
        }
        // Diagonal
        if (board[0] == check && board[4] == check && board[8] == check || board[2] == check && board[4] == check && board[6] == check) {
            if (!testing) winner = check;
            return true;
        }
    return false;
}

void comp_moves() {
    short comp_pos;
    bool position_found = false;
    // while (!is_legal((comp_pos = rand() % 9))) {
    //     continue;
    // }
    
    // First, check if the comp can win on the next turn
    if (!position_found) {
        int i = 0;
        while (!position_found && i++ != 9) {
            char temp = board[i];
            board[i] = 'O';
            if (check_win('O', true) && is_legal(i)) {
                position_found = true;
                comp_pos = i;
            }
            board[i] = temp;
        }
    }
    // Then, see if the comp can block the player from winning
    if (!position_found) {
        int i = 0;
        while (!position_found && i++ != 9) {
            char temp = board[i];
            board[i] = 'O';
            if (check_win('X', true) && is_legal(i)) {
                position_found = true;
                comp_pos = i;
            }
            board[i] = temp;
        }
    }

    // Finally, target the center, the corners and then sides in that order
    // Center
    if (!position_found) {
        if (is_legal(4)) {
            position_found = true;
            comp_pos = 4;
        }
    }

    // Corners
    if (!position_found) {
        std::vector<int> possible_positions;
        for (int i = 0; i < 9; i += 2) {
            if (is_legal(i)) {
                possible_positions.push_back(i);
                position_found = true;
            }
        }
        if (position_found) {
            std::random_shuffle(possible_positions.begin(), possible_positions.end());
            comp_pos = possible_positions[0];
        }
    }

    // Sides
    if (!position_found) {
        std::vector<int> possible_positions;
        for (int i = 1; i < 9; i += 2) {
            if (is_legal(i)) {
                possible_positions.push_back(i);
                position_found = true;
            }
        }
        if (position_found) {
            std::random_shuffle(possible_positions.begin(), possible_positions.end());
            comp_pos = possible_positions[0];
        }
    }

    board[comp_pos] = 'O';
}

void decide_who_starts() {
    if ((rand() % 2) < 1) {
        cout << "\nIt has been chosen that I will move first :)\n";
    } else {
        cout << "\nIt looks like you're moving first :O\n";
        human_to_move = true;
    }
    game_initialised = true;
}

void make_move(short pos) {
    pos--;
    if (!is_legal(pos)) {
        cout << "That position is taken. Try again.\n";
    } else {
        board[pos] = 'X';
    }
}

char take_input() {
    short input = -1;
    while (1) {
        cin >> input;
        if (cin.fail() || 1 > input || input > 9) {
            print_board();
            cout << "Invalid input. Enter a number between 1 and 9.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return input;
    }
}

void announce_winner() {
    print_board();
    if (winner == 'O') {
        cout << "Hahaha! I won!!! Better luck next time, pal\n";
    } else {
        cout << "Crikey, you won! Aw jeez...\n";
    }
}

void print_wins_and_losses() {
    cout << "You have won " << wins << " times, you have lost " << losses << " times.\n";
}

void increment_win_or_loss() {
    if (winner == 'X') {
        wins++;
    } else {
        losses++;
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
    cout << "\nWelcome to a really cool C++ TicTacToe game :O\n";
    cout << "I will try to beat you!!! I have a mega advanced AI, so watch out\n";
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
            increment_win_or_loss();
            print_wins_and_losses();
            ask_for_repeat();
        }
        if (check_stalemate() && game_initialised) {
            print_board();
            cout << "STALEMATE!!!!\n";
            print_wins_and_losses();
            ask_for_repeat();
        }
        human_to_move = !human_to_move;
    }
}