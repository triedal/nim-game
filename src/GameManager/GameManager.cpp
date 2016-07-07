#include "GameManager.h"
#include "../Util/Util.h"
#include <iostream>

void GameManager::initMemoVector(int p1, int p2, int p3)
{
    // initialze 3D array to hold memoized states
    memo.resize(p1+1);
    for (int i = 0; i <= p1; ++i) {
        memo[i].resize(p2+1);
        for (int j = 0; j <= p2; ++j)
            memo[i][j].resize(p3+1);
    }

    // set all values in array to UNSET
    for (int i = 0; i <= p1; ++i)
        for (int j = 0; j <= p2; ++j)
            for (int k = 0; k <= p3; ++k)
                memo[i][j][k] = UNSET;
}

void GameManager::pMemo(int p1, int p2, int p3)
{
    std::cout << (memo[p1][p2][p3] == WINNING ? "WIN" : memo[p1][p2][p3] == LOSING ? "LOSS" : "UNSET" ) << std::endl;
}

std::vector<std::vector<int> > GameManager::getMoves(State currState)
{
    std::vector<std::vector<int> > moves(3, std::vector<int>(3, -1));

    // move (1 2)
    moves[0][0] = currState.piles[0] - currState.piles[1];
    moves[0][1] = currState.piles[1];
    moves[0][2] = currState.piles[2];

    // move (1 3)
    moves[1][0] = currState.piles[0] - currState.piles[2];
    moves[1][1] = currState.piles[1];
    moves[1][2] = currState.piles[2];

    // move (2 3)
    moves[2][0] = currState.piles[0];
    moves[2][1] = currState.piles[1] - currState.piles[2];
    moves[2][2] = currState.piles[2];

    return moves;
}

bool GameManager::isWinner(State currState)
{
    int p1 = currState.piles[0],
        p2 = currState.piles[1],
        p3 = currState.piles[2];

    if (memo[p1][p2][p3] == UNSET)
    {
        std::vector<std::vector<int> > moves = getMoves(currState);
        // One pile left
        if ((p1 == 0 && p2 == 0) || (p1 == 0 && p3 == 0) || (p2 == 0 && p3 == 0))
            memo[p1][p2][p3] = LOSING;
        // Two piles left
        else if (p3 == 0)
        {
            std::vector<int> move1Minus2 = moves[0];
            State tmpState = State(move1Minus2[0], move1Minus2[1], move1Minus2[2]);
            memo[p1][p2][p3] = isWinner(tmpState) ? LOSING : WINNING;
        } 
        // Three piles left
        else 
        {
            std::vector<int> move1Minus2 = moves[0],
                             move1Minus3 = moves[1],
                             move2Minus3 = moves[2];

            State s1 (move1Minus2[0], move1Minus2[1], move1Minus2[2]),
                  s2 (move1Minus3[0], move1Minus3[1], move1Minus3[2]),
                  s3 (move2Minus3[0], move2Minus3[1], move2Minus3[2]);

            memo[p1][p2][p3] = (isWinner(s1) && isWinner(s2) && isWinner(s3)) ? LOSING : WINNING;
        }
    }
    return memo[p1][p2][p3] == WINNING ? true : false;
}

std::vector<int> GameManager::bestMove(State currState)
{
    std::vector<int> bestMove;
    if (isWinner(currState))
    {
        std::vector<std::vector<int> > moves = getMoves(currState);
        std::vector<int> move1Minus2 (moves[0]),
                         move1Minus3 (moves[1]),
                         move2Minus3 (moves[2]);

        State s1 (move1Minus2[0], move1Minus2[1], move1Minus2[2]),
              s2 (move1Minus3[0], move1Minus3[1], move1Minus3[2]),
              s3 (move2Minus3[0], move2Minus3[1], move2Minus3[2]);

        if (memo[s1.getPileVal(1)][s1.getPileVal(2)][s1.getPileVal(3)] == LOSING)
            bestMove = move1Minus2;
        if (memo[s2.getPileVal(1)][s2.getPileVal(2)][s2.getPileVal(3)] == LOSING)
            bestMove = move1Minus3;
        if (memo[s3.getPileVal(1)][s3.getPileVal(2)][s3.getPileVal(3)] == LOSING)
            bestMove = move2Minus3;
    }
    return bestMove;
}

bool GameManager::checkForWin(State currState)
{
    if (currState.getPileVal(2) == 0 && currState.getPileVal(3) == 0)
    {
        std::cout << (turn == COMPUTER ? "Computer wins!" : "Player wins!") << std::endl;
        return true;
    }
    return false;
}

void GameManager::run()
{
    int p1, p2, p3;
    std::cout << "Enter number of stones per pile:" << std::endl;
    std::cin >> p1;
    std::cin >> p2;
    std::cin >> p3;

    initMemoVector(p1, p2, p3);
    State state(p1, p2, p3);

    if (isWinner(state))
    {
        std::cout << "I'll go first." << std::endl;
        turn = COMPUTER;
    } else
    {
        std::cout << "You go first." << std::endl;
        turn = PLAYER;
    }
    
    while (true)
    {
        if (turn == COMPUTER)
        {
            std::cout << "Computer's turn:" << std::endl;
            std::vector<int> move = bestMove(state);

            state.update(move[0], move[1], move[2]);
        } else
        {
            int minuend, subtrahend;
            std::cout << "Player's turn:" << std::endl;
            std::cin >> minuend;
            std::cin >> subtrahend;

            if ((minuend == 1 && subtrahend == 2) || (minuend == 1 && subtrahend == 3))
                state.update(state.getPileVal(minuend) - state.getPileVal(subtrahend), state.getPileVal(2), state.getPileVal(3));
            else
                state.update(state.getPileVal(1), state.getPileVal(2) - state.getPileVal(3), state.getPileVal(3));
        }
        state.print();
        if (checkForWin(state)) break;
        turn = (turn == PLAYER) ? COMPUTER : PLAYER;
    }
}