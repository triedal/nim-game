#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#import "../Game/State.h"

class GameManager
{
public:
  GameManager();
  ~GameManager();
  void bestMove(State currState);
  bool isWinner();
  void getMoves();
};
#endif