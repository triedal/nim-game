#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Game/State.h"
#include <vector>

class GameManager
{
enum GameType {WINNING, LOSING, UNSET};

public:
  GameManager();
  void bestMove(State currState);
  bool isWinner(State currState);
  void getMoves(State currState);

private:
  std::vector<std::vector<std::vector<GameType> > > memo;
};
#endif