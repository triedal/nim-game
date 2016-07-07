#include "Util.h"
#include <iostream>

void Util::pV1(std::vector<int> v)
{
    for (int i=0; i < 3; ++i)
        std::cout << v[i];
    std::cout << std::endl;
}
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