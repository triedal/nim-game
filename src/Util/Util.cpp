#include "Util.h"
#include <iostream>

// Prints contents of a vector
// Used for printing vectors like move1Minus2, bestMove, etc in GDB debugger
void Util::pV1(std::vector<int> v)
{
    for (int i=0; i < 3; ++i)
        std::cout << v[i];
    std::cout << std::endl;
}

// Prints contents of a 2D vector
// Used for printing moves vector in GDB debugger
void Util::pV2(std::vector<std::vector<int> > v)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << v[i][j];
        }
        std::cout << std::endl;
    }

}