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
        grid = vector<vector<char>>(size, vector<char>(size, ' '));
    }

    // TODO - TTT105
    void display() const
    {
        cout << "\n    ";
        for (int c = 0; c < size; ++c)
            cout << "  " << (c + 1) << "  ";
        cout << "\n";

        for (int r = 0; r < size; ++r)
        {
            cout << "  " << (r + 1) << " ";
            for (int c = 0; c < size; ++c)
            {
                char cell = grid[r][c];
                cout << "  " << (cell == ' ' ? '.' : cell) << "  ";
                if (c < size - 1)
                    cout << "|";
            }
            cout << "\n";
            if (r < size - 1)
            {
                cout << "    ";
                for (int c = 0; c < size; ++c)
                {
                    cout << "-----";
                    if (c < size - 1)
                        cout << "+";
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }

    // TODO - TTT103
    bool makeMove(int row, int col, char symbol)
    {
        if (!isFull())
        {
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }

    // TODO - TTT103
    bool isValidMove(int row, int col) const
    {
        return (row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == ' ');
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
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (grid[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    // TODO - TTT102
    char getCell(int row, int col) const
    {
        return grid[row][col];
    }

    // TODO - TTT102
    void reset()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {

                grid[i][j] = ' ';
            }
        }
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
    Player(const string &name, char symbol) : name(name), symbol(symbol) {}

    // TODO - TTT101
    virtual void getMove(int &row, int &col) = 0;

    // TODO - TTT101
    string getName() const
    {
        return name;
    }

    // TODO - TTT101
    char getSymbol() const
    {
        return symbol;
    }

    // TODO - TTT101
    void setName(const string &newName)
    {
        name = newName;
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

    // TTT202
    void getRandomMove(const Board &board, int &row, int &col) const
    {
        vector<pair<int, int>> validMoves;
        int sz = board.getSize();

        for (int r = 0; r < sz; ++r)
            for (int c = 0; c < sz; ++c)
                if (board.isValidMove(r, c))
                    validMoves.push_back({r, c});

        if (!validMoves.empty())
        {
            int idx = rand() % validMoves.size();
            row = validMoves[idx].first;
            col = validMoves[idx].second;
        }
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
        boardRef = board;
    }

    // TODO - TTT204
    void getMove(int &row, int &col) override
    {
        if (boardRef == nullptr)
            return;

        if (difficulty == Difficulty::EASY)
            getRandomMove(*boardRef, row, col);
        else
            getBestMove(*boardRef, row, col); // HARD (minimax) implemented in TTT203
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

    // TTT303
    void printSeparator() const
    {
        cout << "  ================================\n";
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

    // TTT303
    bool checkGameEnd()
    {
        // Check if either player has won
        for (int i = 0; i < 2; ++i)
        {
            if (players[i] != nullptr && board.checkWin(players[i]->getSymbol()))
            {
                gameOver = true;
                winner = i;
                return true;
            }
        }

        // Check for draw (board full, no winner)
        if (board.isFull())
        {
            gameOver = true;
            winner = -1; // -1 signals a draw
            return true;
        }

        return false;
    }

    // TTT303
    void displayResult() const
    {
        board.display();
        printSeparator();

        if (winner == -1)
        {
            cout << "         It's a DRAW!\n";
        }
        else
        {
            cout << "    🎉  " << players[winner]->getName() << " WINS!  🎉\n";
        }

        printSeparator();
        cout << "\n";
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
