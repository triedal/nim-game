#ifndef GAMESTATE_H
#define GAMESTATE_H

class State
{
public:
    State(int a, int b, int c);
    void update(int a, int b, int c);
    int getPileVal(int i);
    // TODO: Make piles private and construct a setter
    int piles[3];

private:
    void sort();
};
#endif