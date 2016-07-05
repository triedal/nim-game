#ifndef GAMESTATE_H
#define GAMESTATE_H

class State
{
enum Turn {PLAYER, COMPUTER};

public:
    State(int a, int b, int c);
    int piles[3];

private:
	void sort();
};
#endif