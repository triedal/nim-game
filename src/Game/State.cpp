#include "State.h"
#include <iostream>

State::State(int a, int b, int c)
{
    piles[0] = a;
    piles[1] = b;
    piles[2] = c;
    sort();
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

void State::update(int a, int b, int c)
{
    piles[0] = a;
    piles[1] = b;
    piles[2] = c;
    // If piles are not in desc order, sort them
    if (piles[1] > piles[0] || 
        piles[2] > piles[1] || 
        piles[2] > piles[0])
    {
        sort();
    }
}

int State::getPileVal(int i) const
{
    return piles[i-1];
}

void State::print() const
{
    std::cout << "Game state: ";
    for (int i=0; i<3; ++i)
        std::cout << piles[i] << (i == 2 ? " " : ", ");
    std::cout << std::endl;
}