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