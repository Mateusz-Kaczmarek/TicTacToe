#include <iostream>
#include <algorithm>
#include <vector>
#include "../inc/game.hh"
using std::cin;
using std::cout;
// struct Field
// {
//     int number;
//     char mark;
//     bool isMarked;
// };

// enum class State
// {
//     WinPlayer1,
//     WinPlayer2,
//     Draw,
//     Running,
// };

char Game::printMark(const int number)
{
    auto it = std::find_if(board.begin(), board.end(), [&number](Field &f) { return f.number == number; });
    if (it->isMarked)
    {
        return it->mark;
    }
    else
    {
        return *(std::to_string(it->number).c_str());
    }
}

void Game::printBoard()
{
    cout << printMark(1) << " | " << printMark(2) << " | " << printMark(3) << "\n";
    cout << "----------\n";
    cout << printMark(4) << " | " << printMark(5) << " | " << printMark(6) << "\n";
    cout << "----------\n";
    cout << printMark(7) << " | " << printMark(8) << " | " << printMark(9) << "\n";
    cout << "\n";
    cout << "\n";
}

bool Game::markField(int number, char playerMark)
{
    auto it = std::find_if(board.begin(), board.end(), [&number](Field &f) { return f.number == number; });
    if (not it->isMarked)
    {
        it->mark = playerMark;
        it->isMarked = true;
        return true;
    }
    else
    {
        return false;
    }
}

void Game::checkBoard()
{
    
}

void Game::creatBoard()
{
    for (int i = 1; i < 10; i++)
    {
        Field temp{i, '.', false};
        board.emplace_back(temp);
    }
}
void Game::playerMove(std::string str, char player)
{
    cout << str;
    std::string playerInput;
    int playerChoice;
    cin >> playerInput;

    try
    {
        bool isMarkComplete;
        playerChoice = std::stoi(playerInput); //may throw exception

        if (0 < playerChoice and playerChoice < 10)
        {
            isMarkComplete = markField(playerChoice, player);
        }
        else
        {
            cout << "You chose wrong number, please try again\n";
            playerMove(str, player);
        }

        if (isMarkComplete)
        {
            printBoard(); // add protection against multiply printing "board" in case when this function is called recursively
        }
        else
        {
            cout << "This field is occupied by another player, please try again\n";
            playerMove(str, player);
        }
    }
    catch (...)
    {
        cout << "You chose letter instead number, please try again\n";
        playerMove(str, player);
    }
}

void Game::start()
{
    creatBoard();
    gameState = State::Running;

    cout << "\n";
    cout << "\n";
    cout << "Do you wanna to play with tic tac toe ?!\n";
    printBoard();
    cout << "Player one begin, chose field form 1 to 9\n";

    while (gameState == State::Running)
    {
        playerMove("Player1:", player1);
        playerMove("Player2:", player2);
    }
}

// class Game
// {
// public:
// private:
//     std::vector<Field> board;
//     char player1 = 'x';
//     char player2 = 'o';
//     State gameState;
// };
