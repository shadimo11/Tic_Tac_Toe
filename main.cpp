#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// ─────────────────────────────────────────
//  Difficulty enum
// ─────────────────────────────────────────
// TODO - TTT202
enum class Difficulty
{
    EASY,
    HARD
};

// ═════════════════════════════════════════
//  Board Class
// ═════════════════════════════════════════
class Board
{
private:
    vector<vector<char>> grid;
    const int size;

public:
    // TODO - TTT102
    Board(int size = 3) : size(size)
    {
    }

    // TODO - TTT105
    void display() const
    {
    }

    // TODO - TTT103
    bool makeMove(int row, int col, char symbol)
    {
        return false;
    }

    // TODO - TTT103
    bool isValidMove(int row, int col) const
    {
        return false;
    }

    // TTT104 - Win Condition Logic
    bool checkWin(char symbol) const
    {
        bool diag1 = true, diag2 = true;

        for (int i = 0; i < size; ++i)
        {
            bool rowWin = true, colWin = true;

            for (int j = 0; j < size; ++j)
            {
                if (grid[i][j] != symbol)
                    rowWin = false;
                if (grid[j][i] != symbol)
                    colWin = false;
            }

            if (rowWin || colWin)
                return true;

            if (grid[i][i] != symbol)
                diag1 = false;
            if (grid[i][size - 1 - i] != symbol)
                diag2 = false;
        }

        return diag1 || diag2;
    }

    // TODO - TTT103
    bool isFull() const
    {
        return false;
    }

    // TODO - TTT102
    char getCell(int row, int col) const
    {
        return ' ';
    }

    // TODO - TTT102
    void reset()
    {
    }

    // TODO - TTT102
    int getSize() const
    {
        return size;
    }
};

// ═════════════════════════════════════════
//  Player Class (Abstract)
// ═════════════════════════════════════════
class Player
{
protected:
    string name;
    char symbol;

public:
    // TODO - TTT101
    Player(const string &name, char symbol)
    {
    }

    // TODO - TTT101
    virtual void getMove(int &row, int &col) = 0;

    // TODO - TTT101
    string getName() const
    {
        return "";
    }

    // TODO - TTT101
    char getSymbol() const
    {
        return ' ';
    }

    // TODO - TTT101
    void setName(const string &newName)
    {
    }

    virtual ~Player() {}
};

// ═════════════════════════════════════════
//  HumanPlayer Class (Derived from Player)
// ═════════════════════════════════════════
class HumanPlayer : public Player
{
public:
    HumanPlayer(const string &name, char symbol) : Player(name, symbol) {}

    // TODO - TTT201
    void getMove(int &row, int &col) override
    {
    }
};

// ═════════════════════════════════════════
//  AIPlayer Class (Derived from Player)
// ═════════════════════════════════════════
class AIPlayer : public Player
{
private:
    Difficulty difficulty;
    Board *boardRef;

    // TODO - TTT204
    char opponentSymbol() const
    {
        return ' ';
    }

    // TODO - TTT202
    void getRandomMove(const Board &board, int &row, int &col) const
    {
    }

    // TODO - TTT203
    int evaluateBoard(const Board &board) const
    {
        return 0;
    }

    // TODO - TTT203
    int minimaxClean(Board boardCopy, int depth, bool isMaximizing) const
    {
        return 0;
    }

    // TODO - TTT203
    void getBestMove(Board &board, int &row, int &col) const
    {
    }

public:
    AIPlayer(const string &name, char symbol, Difficulty diff)
        : Player(name, symbol), difficulty(diff), boardRef(nullptr) {}

    void setDifficulty(Difficulty newDifficulty) { difficulty = newDifficulty; }

    // TODO - TTT204
    void setBoardRef(Board *board)
    {
    }

    // TODO - TTT204
    void getMove(int &row, int &col) override
    {
    }
};

// ═════════════════════════════════════════
//  Game Class
// ═════════════════════════════════════════
class Game
{
private:
    Board board;
    Player *players[2];
    int currentPlayerIndex;
    bool gameOver;
    int winner;

    // TODO - TTT305
    void clearScreen() const
    {
    }

    // TODO - TTT303
    void printSeparator() const
    {
    }

public:
    // TODO - TTT205
    Game() : board(3)
    {
    }

    // TODO - TTT205
    ~Game()
    {
    }

    // TODO - TTT305
    void start()
    {
    }

    // TODO - TTT301
    void showMenu()
    {
    }

    // TODO - TTT302
    void setupPvP()
    {
    }

    // TODO - TTT302
    void setupPvC(Difficulty difficulty)
    {
    }

    // TODO - TTT205
    void switchPlayer()
    {
    }

    // TODO - TTT205
    void handleHumanMove(Player *player)
    {
    }

    // TODO - TTT205
    void handleAIMove(AIPlayer *aiPlayer)
    {
    }

    // TODO - TTT303
    bool checkGameEnd()
    {
        return false;
    }

    // TODO - TTT303
    void displayResult() const
    {
    }

    // TODO - TTT304
    void reset()
    {
    }

private:
    // TODO - TTT304
    void playRound()
    {
    }

    // TODO - TTT304
    bool askReplay() const
    {
        return false;
    }
};

// ═════════════════════════════════════════
//  main
// ═════════════════════════════════════════
// TODO - TTT305
int main()
{
    return 0;
}
