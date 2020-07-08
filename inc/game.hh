#include <iostream>
#include <vector>
#include <string>

struct Field
{
    int number;
    char mark;
    bool isMarked;
};

enum class State
{
    WinPlayer1,
    WinPlayer2,
    Draw,
    Running,
};

class Game
{
public:
    void printBoard();
    char printMark(const int);
    bool markField(int, char);
    bool checkBoard(char);
    bool isBoardFull();
    bool isEndGame(char);
    void creatBoard();
    void printResult();
    void playerMove(std::string, char);
    void start();

private:
    std::vector<Field> board;
    char player1 = 'x';
    char player2 = 'o';
    State gameState;
};
