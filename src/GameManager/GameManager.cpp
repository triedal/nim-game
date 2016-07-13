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

// Used for debugging 2D moves array in isWinner, bestMove, and getMoves
void GameManager::pMemo(int p1, int p2, int p3) const
{
    std::cout << (memo[p1][p2][p3] == WINNING ? "WIN" : memo[p1][p2][p3] == LOSING ? "LOSS" : "UNSET" ) << std::endl;
}

std::vector<std::vector<int> > GameManager::getMoves(const State currState) const
{
    // Initialize 3x3 array to hold potential moves that could be played
    // from currState
    std::vector<std::vector<int> > moves(3, std::vector<int>(3, -1));

    // move (1 2)
    moves[0][0] = currState.getPileVal(1) - currState.getPileVal(2);
    moves[0][1] = currState.getPileVal(2);
    moves[0][2] = currState.getPileVal(3);

    // move (1 3)
    moves[1][0] = currState.getPileVal(1) - currState.getPileVal(3);
    moves[1][1] = currState.getPileVal(2);
    moves[1][2] = currState.getPileVal(3);

    // move (2 3)
    moves[2][0] = currState.getPileVal(1);
    moves[2][1] = currState.getPileVal(2) - currState.getPileVal(3);
    moves[2][2] = currState.getPileVal(3);

    return moves;
}

bool GameManager::isWinner(const State currState)
{
    int p1 = currState.getPileVal(1),
        p2 = currState.getPileVal(2),
        p3 = currState.getPileVal(3);

    if (memo[p1][p2][p3] == UNSET) // If value is not already memoized, recursively find the solution
    {
        std::vector<std::vector<int> > moves = getMoves(currState);
        /*
         * One pile left
         * If there is only one pile left, the next person who plays will lose
         * POSSIBLE MOVES: NONE
         */
        if ((p1 == 0 && p2 == 0) || (p1 == 0 && p3 == 0) || (p2 == 0 && p3 == 0))
            memo[p1][p2][p3] = LOSING;
        /*
         * Two piles left
         * The only move that can be made from two piles is (1 2),
         * solve that instance recursively
         * POSSIBLE MOVES: (1 2)
         */
        else if (p3 == 0)
        {
            std::vector<int> move1Minus2 = moves[0];
            State tmpState = State(move1Minus2[0], move1Minus2[1], move1Minus2[2]);
            // If (1 2) is a winning move, the current state is losing, vice versa
            memo[p1][p2][p3] = isWinner(tmpState) ? LOSING : WINNING;
        } 
        /*
         * Three piles left
         * POSSIBLE MOVES: (1 2) (1 3) (2 3)
         */
        else 
        {
            std::vector<int> move1Minus2 = moves[0], // (1 2)
                             move1Minus3 = moves[1], // (1 3)
                             move2Minus3 = moves[2]; // (2 3)

            // Three potential outcomes of piles from the above moves
            State s1 (move1Minus2[0], move1Minus2[1], move1Minus2[2]),
                  s2 (move1Minus3[0], move1Minus3[1], move1Minus3[2]),
                  s3 (move2Minus3[0], move2Minus3[1], move2Minus3[2]);

            // If all moves are winning moves, the current move is a losing move and vice versa
            memo[p1][p2][p3] = (isWinner(s1) && isWinner(s2) && isWinner(s3)) ? LOSING : WINNING;
        }
    }
    // Woot woot! The value is memoized, return if it's a winning move or not
    return memo[p1][p2][p3] == WINNING ? true : false;
}

std::vector<int> GameManager::bestMove(const State currState)
{
    std::vector<int> bestMove;
    if (isWinner(currState))
    {
        // 3x3 vector containing possible pile outcomes from all available moves
        std::vector<std::vector<int> > moves = getMoves(currState);
        std::vector<int> move1Minus2 (moves[0]),
                         move1Minus3 (moves[1]),
                         move2Minus3 (moves[2]);

        // Create states from potential outcomes
        State s1 (move1Minus2[0], move1Minus2[1], move1Minus2[2]),
              s2 (move1Minus3[0], move1Minus3[1], move1Minus3[2]),
              s3 (move2Minus3[0], move2Minus3[1], move2Minus3[2]);

        // If result of move (1 2) is losing, play that move so the player loses
        if (memo[s1.getPileVal(1)][s1.getPileVal(2)][s1.getPileVal(3)] == LOSING)
            bestMove = move1Minus2;
        // If result of move (1 3) is losing, play that move so the player loses
        if (memo[s2.getPileVal(1)][s2.getPileVal(2)][s2.getPileVal(3)] == LOSING)
            bestMove = move1Minus3;
        // If result of move (2 3) is losing, play that move so the player loses
        if (memo[s3.getPileVal(1)][s3.getPileVal(2)][s3.getPileVal(3)] == LOSING)
            bestMove = move2Minus3;
    }
    return bestMove;
}

bool GameManager::checkForWin(const State currState) const
{
    /*
     * A win occurs if there is only one pile left
     * If there is a win print the winner and return true
     */
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

    // This will be used to hold the "piles"
    State state(p1, p2, p3);

    // 3D vector is used as a memoized data structure to hold all game outcomes
    initMemoVector(state.getPileVal(1), state.getPileVal(2), state.getPileVal(3));

    // If the initial state is a winning move the computer plays, if it's losing
    // give the bad pile to the player.
    if (isWinner(state))
    {
        std::cout << "I'll go first." << std::endl;
        turn = COMPUTER;
    } else
    {
        std::cout << "You go first." << std::endl;
        turn = PLAYER;
    }
    
    /*
     * MAIN GAME LOOP
     * --------------
     * This will run indefinitely, alternating turns between COMPUTER and PLAYER.
     * After each move is played checkForWin() is called. If it returns true the loop breaks and game ends.
     */
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

            // If player played (1 2) or (1 3)
            if ((minuend == 1 && subtrahend == 2) || (minuend == 1 && subtrahend == 3))
                state.update(state.getPileVal(minuend) - state.getPileVal(subtrahend), state.getPileVal(2), state.getPileVal(3));
            // Else player played (2 3)
            else
                state.update(state.getPileVal(1), state.getPileVal(2) - state.getPileVal(3), state.getPileVal(3));
        }
        state.print();
        if (checkForWin(state)) break;
        turn = (turn == PLAYER) ? COMPUTER : PLAYER; // Set turn to opposite of current value
    }
}