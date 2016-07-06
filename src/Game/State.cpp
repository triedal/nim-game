#include "State.h"
#include <iostream>

State::State(int a, int b, int c)
{
    piles[0] = a;
    piles[1] = b;
    piles[2] = c;
    this->sort();
}

// sorts piles in desc order
void State::sort()
{
    int tmp = 0;
    for (int i=0; i < 3; ++i)
       for (int j=i+1; j < 3; ++j)
           if (piles[i] < piles[j])
           {
                tmp = piles[i];
                piles[i] = piles[j];
                piles[j] = tmp;
            }
}