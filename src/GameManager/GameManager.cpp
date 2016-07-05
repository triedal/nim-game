#include "GameManager.h"
#include <iostream>

GameManager::GameManager()
{
  int p1, p2, p3;
  std::cout << "Enter number of stones per pile:" << std::endl;
  std::cin >> p1;
  std::cin >> p2;
  std::cin >> p3;

  memo.resize(p1);
  for (int i = 0; i < p1; ++i) {
    memo[i].resize(p2);
    for (int j = 0; j < p2; ++j)
      memo[i][j].resize(p3);
  }

  for (int i = 0; i < p1; ++i)
    for (int j = 0; j < p2; ++j)
      for (int k = 0; k < p3; ++k)
        memo[i][j][k] = UNSET;
}