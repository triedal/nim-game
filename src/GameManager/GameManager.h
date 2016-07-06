#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Game/State.h"
#include <vector>

class GameManager
{
enum GameType {WINNING, LOSING, UNSET};

public:
    GameManager();
    std::vector<int> bestMove(State currState);
    bool isWinner(State currState);
    std::vector<std::vector<int> > getMoves(State currState);

private:
    std::vector<std::vector<std::vector<GameType> > > memo;
};
#endif