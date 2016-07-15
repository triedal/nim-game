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
    void pMemo(int p1, int p2, int p3) const;

private:
    bool checkForWin(const State currState) const;
    bool isWinner(const State currState);
    void initMemoVector(int p1, int p2, int p3);
    std::vector<int> bestMove(const State currState);
    std::vector<std::vector<int> > getMoves(const State currState) const;
    std::vector<std::vector<std::vector<GameType> > > memo;
    Turn turn;
};
#endif