#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Game/State.h"
#include <vector>

class GameManager
{
enum GameType {WINNING, LOSING, UNSET};
enum Turn {PLAYER, COMPUTER};

public:
    std::vector<int> bestMove(State currState);
    bool isWinner(State currState);
    std::vector<std::vector<int> > getMoves(State currState);
    void run();
    void pV2(std::vector<std::vector<int> > v);
    void pV1(std::vector<int> v);
    void pMemo(int p1, int p2, int p3);

private:
    bool checkForWin(State currState);
    void initMemoVector(int p1, int p2, int p3);
    std::vector<std::vector<std::vector<GameType> > > memo;
    Turn turn;
};
#endif