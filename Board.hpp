#pragma once
#include "Column.hpp"
#include "tools.hpp"

class Board {
private:
	int counter = 0;
	int towerPos[3] = {0};
    unique_ptr<Column> backBone[13];
	Player* player;
public:
	Board();
    ~Board()=default;
    ostream& print(ostream&);
    void startTurn(Player *);
    bool move(int);
    void stop();
    void bust();
    void quit();
};
inline ostream& operator<<(ostream& out, Board& B) {
	return B.print(out);
}

