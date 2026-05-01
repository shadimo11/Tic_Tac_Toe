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
    void display() const {
        cout << "\n    ";
        for (int c = 0; c < size; ++c)
            cout << "  " << (c + 1) << "  ";
        cout << "\n";

        for (int r = 0; r < size; ++r) {
            cout << "  " << (r + 1) << " ";
            for (int c = 0; c < size; ++c) {
                char cell = grid[r][c];
                cout << "  " << (cell == ' ' ? '.' : cell) << "  ";
                if (c < size - 1) cout << "|";
            }
            cout << "\n";
            if (r < size - 1) {
                cout << "    ";
                for (int c = 0; c < size; ++c) {
                    cout << "-----";
                    if (c < size - 1) cout << "+";
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }

    // TODO - TTT103
    bool makeMove(int row, int col, char symbol) {
        if (!isFull()){
            grid[row][col]=symbol;
            return true;
        }
        return false;
    }


    // TODO - TTT103
    bool isValidMove(int row, int col) const {
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
    bool isFull() const {
        for (int i=0;i<size;i++){
            for (int j=0;j<size;j++){
                if (grid[i][j]==' ')
                    return false;
            }
        }
        return true;
    }

    // TODO - TTT102
    char getCell(int row, int col) const
    {
        return grid[row][col];;
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
        players[0] = nullptr;
        players[1] = nullptr;
        currentPlayerIndex = 0;
        gameOver = false;
        winner = -1;
        srand(static_cast<unsigned>(time(nullptr)));    // Essential for randomization
    }

    // TODO - TTT205
    ~Game()
    {
        delete players[0];
        delete players[1];      // Remove redundant pointer checks
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
        // Removed redundant pointer null checks
        delete players[0]; delete players[1];
        string name1, name2;
        
        cout << "\n  Enter name for Player 1 (X): ";
        cin >> name1;
        cout << "  Enter name for Player 2 (O): ";
        cin >> name2;
        
        players[0] = new HumanPlayer(name1, 'X');
        players[1] = new HumanPlayer(name2, 'O');
        
        cout << "\n  >> " << name1 << " (X) vs " << name2 << " (O)\n";
    }

    // TODO - TTT302
    void setupPvC(Difficulty difficulty)
    {
        // Injected the board reference into the AI so it can calculate moves.
        delete players[0]; delete players[1];
        string name;
        
        cout << "\n  Enter your name (X): ";
        cin >> name;
        
        players[0] = new HumanPlayer(name, 'X');
        
        // Create AI, set its board reference, then assign to the polymorphic array
        AIPlayer* ai = new AIPlayer("Computer", 'O', difficulty);
        ai->setBoardRef(&board);
        players[1] = ai;
        
        string diffStr = (difficulty == Difficulty::EASY) ? "Easy" : "Hard";
        cout << "\n  >> " << name << " (X) vs Computer/" << diffStr << " (O)\n";
    }

    // TODO - TTT205
    void switchPlayer()
    {
        currentPlayerIndex = (currentPlayerIndex == 0) ? 1 : 0;
    }

    // TODO - TTT205
    void handleHumanMove(Player *player)
    {
        // Valdiate the move before making the move.
        int row, col;
        while (true) {
            cout << "\n  >> " << player->getName()
                 << " (" << player->getSymbol() << ") — your turn\n";
            
            player->getMove(row, col);
            
            // Validate input strictly before attempting state change
            if (board.isValidMove(row, col)) {
                board.makeMove(row, col, player->getSymbol());
                break;
            } else {
                cout << "  [!] Invalid move. Cell is occupied or out of range. Try again.\n";
            }
        }
    }

    // TODO - TTT205
    void handleAIMove(AIPlayer *aiPlayer)
    {
        // Removed aiPlayer->setBoardRef() since it is now securely injected during setupPvC
        cout << "\n  >> " << aiPlayer->getName()
             << " (" << aiPlayer->getSymbol() << ") is thinking...\n";
        
        int row, col;
        aiPlayer->getMove(row, col);
        board.makeMove(row, col, aiPlayer->getSymbol());
        
        cout << "  >> Computer plays at row " << (row+1)
             << ", col " << (col+1) << "\n";
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
