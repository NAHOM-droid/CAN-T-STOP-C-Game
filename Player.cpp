#include "Player.hpp"
//adding won column to the scoreboard and increamenting score--------
bool Player::wonColumn(int colNum) {
	scoreBoard[score++] = colNum;
	return score == 3;
}
//---------------------------------------------------------------
ostream& Player::print(ostream& out) {
	extern const string Ecolors[];
	out << "Name: " << name << ", Color: " << Ecolors[(int) color]
			<< ", Score: " << score;
	out << ", WonColumns: { ";
	for (int j = 0; j < score; j++) {
		out << scoreBoard[j] << " ";
	}
	out << "}" << endl;
	return out;
}

