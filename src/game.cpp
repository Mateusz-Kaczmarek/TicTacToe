#include <iostream>
#include <algorithm>
#include <vector>
#include "../inc/game.hh"
using std::cin;
using std::cout;

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

bool Game::checkBoard(char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i].mark == player and board[i + 3].mark == player and board[i + 6].mark == player)
        {
            return true;
        }

        int j = i * 3;
        if (board[j].mark == player and board[j + 1].mark == player and board[j + 2].mark == player)
        {
            return true;
        }
    }

    if (board[0].mark == player and board[4].mark == player and board[8].mark == player)
    {
        return true;
    }
    else if (board[2].mark == player and board[4].mark == player and board[6].mark == player)
    {
        return true;
    }

    return false;
}

bool Game::isBoardFull()
{
    int emptyFileds = std::count_if(board.begin(), board.end(), [](Field &f) { return f.mark == '.'; });

    if (0 == emptyFileds)
        return true;

    return false;
}

bool Game::isEndGame(const char player)
{
    if (checkBoard(player))
    {
        if (player == 'x')
        {
            gameState = State::WinPlayer1;
        }
        else
        {
            gameState = State::WinPlayer2;
        }
        return true;
    }
    if (isBoardFull())
    {
        gameState = State::Draw;
        return true;
    }

    return false;
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

void Game::printResult()
{
    switch (gameState)
    {
    case State::Draw:
        cout << "No one won is a DRAW\n";
        break;
    case State::WinPlayer1:
        cout << "Player1 won, Congratulations!!!!\n";
        break;
    case State::WinPlayer2:
        cout << "Player2 won, Congratulations!!!!\n";
        break;
    default:
        "Something went wrong :(\n";
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
        if (isEndGame(player1))
            break;

        playerMove("Player2:", player2);
        if (isEndGame(player2))
            break;
    }

    printResult();
}
