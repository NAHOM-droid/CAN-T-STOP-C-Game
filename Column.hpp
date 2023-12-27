#pragma once
#include "enum.hpp"
#include "Player.hpp"
#include "tools.hpp"

class Column {
private:
	int colNum;
	ColState state = ColState::available;
	int content[5]={0};
    static const int colLengths[13];
public:
	Column(int num): colNum(num) {}
	~Column()=default;
	ColState State(){return state;}
	ostream& print(ostream&);
	bool startTower(Player*);
	bool move();
	void stop(Player*);
	void bust();
	void quit(Player*);
};
//-----------------------------------------------------------------------
inline ostream& operator<<(ostream& out, Column& C) {
	return C.print(out);
}
