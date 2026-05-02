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
        if (isValidMove(row, col))
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
    void getMove(int &row, int &col) override {
        while (true)
        {

            cout << "  Enter row and column (1-3): ";

            int r, c;
            cin >> r >> c;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Enter numbers only.\n";
               continue;
            }

            if (r < 1 || r > 3 || c < 1 || c > 3)
            {

                cout << "Out of range. Enter values between 1 and 3.\n";
                continue;
            }

            row = r - 1;
            col = c - 1;
            break;
        }

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

    char opponentSymbol() const{
        return (symbol == 'X') ? 'O' : 'X';
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
        if (board.checkWin(symbol))
            return +10;

        if (board.checkWin(opponentSymbol()))
            return -10;

        return 0;
    }

    // TODO - TTT203
    int minimaxClean(Board boardCopy, int depth, bool isMaximizing) const
    {
        int score = evaluateBoard(boardCopy);
        if (score != 0)
            return score;
        if (boardCopy.isFull())
            return 0;

        int sz = boardCopy.getSize();
        if (isMaximizing)
        {
            int best = numeric_limits<int>::min();
            for (int r = 0; r < sz; ++r)
                for (int c = 0; c < sz; ++c)
                    if (boardCopy.isValidMove(r, c))
                    {
                        Board next = boardCopy;
                        next.makeMove(r, c, symbol);
                        best = max(best, minimaxClean(next, depth + 1, false));
                    }
            return best;
        }
        else
        {
            int best = numeric_limits<int>::max();
            char opp = opponentSymbol();
            for (int r = 0; r < sz; ++r)
                for (int c = 0; c < sz; ++c)
                    if (boardCopy.isValidMove(r, c))
                    {
                        Board next = boardCopy;
                        next.makeMove(r, c, opp);
                        best = min(best, minimaxClean(next, depth + 1, true));
                    }
            return best;
        }
    }

    // TODO - TTT203
    void getBestMove(Board &board, int &row, int &col) const
    {
        int sz = board.getSize();
        int bestVal = numeric_limits<int>::min();
        row = -1;
        col = -1;

        for (int r = 0; r < sz; ++r)
        {
            for (int c = 0; c < sz; ++c)
            {
                if (board.isValidMove(r, c))
                {
                    Board next = board;
                    next.makeMove(r, c, symbol);
                    int moveVal = minimaxClean(next, 0, false);
                    if (moveVal > bestVal)
                    {
                        bestVal = moveVal;
                        row = r;
                        col = c;
                    }
                }
            }
        }
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
        cout << "\n\n";
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
        players[0] = nullptr;
        players[1] = nullptr;
        currentPlayerIndex = 0;
        gameOver = false;
        winner = -1;
        srand(static_cast<unsigned>(time(nullptr))); // Essential for randomization
    }

    // TODO - TTT205
    ~Game()
    {
        delete players[0];
        delete players[1]; // Remove redundant pointer checks
    }

    // TODO - TTT305
    void start()
    {
        clearScreen();
        cout << "\n";
        printSeparator();
        cout << "      TIC-TAC-TOE GAME\n";
        printSeparator();
        cout << "\n";

        bool running = true;
        while (running)
        {
            showMenu();

            bool replay = true;
            while (replay)
            {
                reset();
                playRound();
                displayResult();
                replay = askReplay();
            }

            running = false;
        }

        cout << "\n  Thanks for playing! Goodbye.\n\n";
    }

    int chooseMenuOption(){
        int playerChoice=0;
        clearScreen();
        cout<<" 1- Player vs Player " <<endl;
        printSeparator();
        cout<<" 2- Player vs Computer (Easy) " <<endl;
        printSeparator();
        cout<<" 3- Player vs Computer (Hard) " <<endl;
        printSeparator();
        cout<<" 4- Exit " <<endl;
        printSeparator();
        cout << "Choose one from the listed numbers:"<<endl;
        cin >> playerChoice;
        return playerChoice;
    }

    // TODO - TTT301
    void showMenu() {

        while (true) {
            int playerChoice = chooseMenuOption();  

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Enter a number.\n";
                continue;
            }

            if (playerChoice < 1 || playerChoice > 4) {
                cout << "Enter 1-4.\n";
                continue;
            }

            switch (playerChoice) {
                case 1:
                    setupPvP();
                    return;          
                case 2:
                    setupPvC(Difficulty::EASY);
                    return;
                case 3:
                    setupPvC(Difficulty::HARD);
                    return;
                case 4:
                    cout << "Goodbye!\n";
                    exit(0);
            }
        }
    }

    // TODO - TTT302
    void setupPvP()
    {
        // Removed redundant pointer null checks
        delete players[0];
        delete players[1];
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
        delete players[0];
        delete players[1];
        string name;

        cout << "\n  Enter your name (X): ";
        cin >> name;

        players[0] = new HumanPlayer(name, 'X');

        // Create AI, set its board reference, then assign to the polymorphic array
        AIPlayer *ai = new AIPlayer("Computer", 'O', difficulty);
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
        while (true)
        {
            cout << "\n  >> " << player->getName()
                 << " (" << player->getSymbol() << ") — your turn\n";

            player->getMove(row, col);

            // Validate input strictly before attempting state change
            if (board.isValidMove(row, col))
            {
                board.makeMove(row, col, player->getSymbol());
                break;
            }
            else
            {
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

        cout << "  >> Computer plays at row " << (row + 1)
             << ", col " << (col + 1) << "\n";
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
        board.reset();
        gameOver = false;
        winner = -1;
        currentPlayerIndex = 0;
    }

private:
    // TODO - TTT304
    void playRound()
    {
        while (!gameOver)
        {
            clearScreen();
            board.display();

            Player* current = players[currentPlayerIndex];

            if (AIPlayer* ai = dynamic_cast<AIPlayer*>(current)){
                handleAIMove(ai);

            }
            
            else{
                handleHumanMove(current);

            }
            
            if (checkGameEnd()){
                break;
            }

            switchPlayer();
        }
    }

    // TODO - TTT304
    bool askReplay() const
    {
        char choice;
        cout << "  Play again? (y/n): ";
        cin >> choice;

        return (choice == 'y' || choice == 'Y');
    }
};

// ═════════════════════════════════════════
//  main
// ═════════════════════════════════════════
// TODO - TTT305
int main()
{
    Game game;
    game.start();
    return 0;
}
