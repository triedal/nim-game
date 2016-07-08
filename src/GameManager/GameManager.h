#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Game/State.h"
#include <vector>

class GameManager
{
// Enums are used because its easier to read than having to deal with bools or 1's and 0's
enum GameType {WINNING, LOSING, UNSET};
enum Turn {PLAYER, COMPUTER};

public:
    void run();
    void pMemo(int p1, int p2, int p3);

private:
    bool checkForWin(State currState);
    bool isWinner(State currState);
    void initMemoVector(int p1, int p2, int p3);
    std::vector<int> bestMove(State currState);
    std::vector<std::vector<int> > getMoves(State currState);
    std::vector<std::vector<std::vector<GameType> > > memo;
    Turn turn;
};
#endif