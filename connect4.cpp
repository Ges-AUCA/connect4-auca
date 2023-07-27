#include <iostream>
#include <vector>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding the random number generator

const int ROWS = 6;
const int COLS = 7;
const char EMPTY = ' ';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

class ConnectFour {
public:
    ConnectFour(bool isAIPlayer1, bool isAIPlayer2)
            : currentPlayer(PLAYER1),
              aiPlayer1(isAIPlayer1),
              aiPlayer2(isAIPlayer2) {
        board = std::vector<std::vector<char>>(ROWS, std::vector<char>(COLS, EMPTY));
        // Seed the random number generator for AI moves
        std::srand(std::time(nullptr));
    }

    void play() {
        while (!isGameOver()) {
            displayBoard();
            if ((currentPlayer == PLAYER1 && aiPlayer1) ||
                (currentPlayer == PLAYER2 && aiPlayer2)) {
                int column;
                do {
                    column = getAIMove();
                } while (!isValidMove(column));

                std::cout << "AI Player " << currentPlayer << " chooses column " << column << std::endl;
                dropDisc(column);
            } else {
                int column;
                do {
                    std::cout << "Player " << currentPlayer << ", enter a column (1-7): ";
                    std::cin >> column;
                } while (!isValidMove(column));

                dropDisc(column);
            }

            if (isWinningMove()) {
                displayBoard();
                if ((currentPlayer == PLAYER1 && aiPlayer1) ||
                    (currentPlayer == PLAYER2 && aiPlayer2)) {
                    std::cout << "AI Player " << currentPlayer << " wins!" << std::endl;
                } else {
                    std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                }
                return;
            }

            // Switch to the other player for the next turn
            currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
        }

        displayBoard();
        std::cout << "It's a draw!" << std::endl;
    }

private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    bool aiPlayer1;
    bool aiPlayer2;
    //TODO: Add ability to choose AI difficulty (easy, medium, hard)

    void displayBoard() {
        std::cout << "\n";
        for (int i = ROWS - 1; i >= 0; --i) {
            std::cout << "|";
            for (int j = 0; j < COLS; ++j) {
                std::cout << board[i][j] << "|";
            }
            std::cout << "\n";
        }
        std::cout << "-----------------\n";
        std::cout << " 1 2 3 4 5 6 7\n";
    }

    bool isValidMove(int column) {
        return column >= 1 && column <= COLS && board[ROWS - 1][column - 1] == EMPTY;
    }

    void dropDisc(int column) {
        for (int i = 0; i < ROWS; ++i) {
            if (board[i][column - 1] == EMPTY) {
                board[i][column - 1] = currentPlayer;
                break;
            }
        }
    }

    bool isWinningMove() {
        // Check for a win in rows, columns, and diagonals
        return checkRows() || checkColumns() || checkDiagonals();
    }

    bool checkRows() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS - 3; ++j) {
                if (board[i][j] == currentPlayer &&
                    board[i][j + 1] == currentPlayer &&
                    board[i][j + 2] == currentPlayer &&
                    board[i][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

    bool checkColumns() {
        for (int i = 0; i < ROWS - 3; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == currentPlayer &&
                    board[i + 1][j] == currentPlayer &&
                    board[i + 2][j] == currentPlayer &&
                    board[i + 3][j] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

    bool checkDiagonals() {
        for (int i = 0; i < ROWS - 3; ++i) {
            for (int j = 0; j < COLS - 3; ++j) {
                if (board[i][j] == currentPlayer &&
                    board[i + 1][j + 1] == currentPlayer &&
                    board[i + 2][j + 2] == currentPlayer &&
                    board[i + 3][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }

        for (int i = 0; i < ROWS - 3; ++i) {
            for (int j = 3; j < COLS; ++j) {
                if (board[i][j] == currentPlayer &&
                    board[i + 1][j - 1] == currentPlayer &&
                    board[i + 2][j - 2] == currentPlayer &&
                    board[i + 3][j - 3] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isGameOver() {
        // Check for a draw
        for (int i = 0; i < COLS; ++i) {
            if (board[ROWS - 1][i] == EMPTY) {
                return false;
            }
        }
        return true;
    }

    int getAIMove() {
        // Generate a move for AI player
        return 0;
        //TODO: Implement random player
        //TODO: Implement minimax player
    }
};

int main() {
    bool isAIPlayer1 = true; // Set to 'true' if player 1 is AI
    bool isAIPlayer2 = true; // Set to 'true' if player 2 is AI
    //TODO: ADD UI with the chose of AI and difficulty
    ConnectFour game(isAIPlayer1, isAIPlayer2);
    game.play();
    return 0;
}