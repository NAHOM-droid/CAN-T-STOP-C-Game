#pragma once
#include "enum.hpp"
#include "CList.hpp"
#include "BadPlayer.hpp"
#include "tools.hpp"

class Player {
private:
	string name;
	EColor color;
	int score = 0;
	int scoreBoard[3];
public:
	Player(string Name, EColor Color) :name(Name), color(Color) {}
	~Player() = default;
	const string Name(){return name;}
	EColor Color() {return color;}
	int Score() {return score;}
	const int* getWonColumn(){return scoreBoard;}
	bool wonColumn(int);
	ostream& print(ostream&);
};
//----------------------------------------------------------
inline ostream& operator<<(ostream& out, Player& P) {
	return P.print(out);
}
