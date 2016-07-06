#include "GameManager.h"
#include <iostream>

GameManager::GameManager()
{
    int p1, p2, p3;
    std::cout << "Enter number of stones per pile:" << std::endl;
    std::cin >> p1;
    std::cin >> p2;
    std::cin >> p3;

    // initialze 3D array to hold memoized states
    memo.resize(p1);
    for (int i = 0; i < p1; ++i) {
        memo[i].resize(p2);
        for (int j = 0; j < p2; ++j)
            memo[i][j].resize(p3);
    }

    // set all values in array to UNSET
    for (int i = 0; i < p1; ++i)
        for (int j = 0; j < p2; ++j)
            for (int k = 0; k < p3; ++k)
                memo[i][j][k] = UNSET;
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

            State s1 = State(move1Minus2[0], move1Minus2[1], move1Minus3[2]),
                  s2 = State(move1Minus3[0], move1Minus3[1], move2Minus3[2]),
                  s3 = State(move2Minus3[0], move2Minus3[1], move2Minus3[2]);

            memo[p1][p2][p3] = (isWinner(s1) && isWinner(s2) && isWinner(s3)) ? LOSING : WINNING;
        }
    }
    return memo[p1][p2][p3] == WINNING ? true : false;
}