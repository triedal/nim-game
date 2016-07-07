#ifndef GAMESTATE_H
#define GAMESTATE_H

class State
{
public:
    State(int a, int b, int c);
    void update(int a, int b, int c);
    int getPileVal(int i);
    void print();

private:
    void sort();
    int piles[3];
};
#endif