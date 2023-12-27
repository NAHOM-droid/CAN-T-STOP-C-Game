#include "enum.hpp"
#include "Column.hpp"
#include "Board.hpp"
#include "tools.hpp"

Board::Board() {
	backBone[0] = NULL;
	backBone[1] = NULL;
	for (int k = 2; k < 13; k++) backBone[k] = make_unique<Column>(k);
	player = nullptr;
}
//----------------------------------------------------------
ostream& Board::print(ostream &out) {
	if(player!=nullptr)	out<<"Current Player- "<<*player;
	out<<"Tower Positions: [ "<<towerPos[0]<<", "<<towerPos[1]
							<<", "<<towerPos[2]<<" ] "<<endl;
	for (int k = 2; k < 13; k++) out<< *backBone[k];
	return out;
}
//-----------------------------------------------------------
void Board::startTurn(Player *p) {
	player = p;
	counter = 0;
	towerPos[0] = towerPos[1] = towerPos[2] = 0;
}
//-----------------------------------------------------------
bool Board::move(int col) {
	if (backBone[col]->State() != ColState::available) return false;
	bool colInTowers = towerPos[0] == col || towerPos[1] == col
			          || towerPos[2] == col;
	if(colInTowers) return backBone[col]->move();
	if(counter < 3 && !colInTowers) {
		towerPos[counter++] = col;
		return backBone[col]->startTower(player);
	}
	return false;
}
//------------------------------------------------------------
void Board::stop() {
	for (int k = 0; k < counter; k++) backBone[towerPos[k]]->stop(player);
	cout << "Stopped." << endl;
}
//------------------------------------------------------------
void Board::bust(){
	for (int k = 0; k < counter; k++) backBone[towerPos[k]]->bust();
	cout << "Busted." << endl;
}
//------------------------------------------------------------------
void Board::quit(){
	for(int k=2; k < 13; k++) backBone[k]->quit(player);
}
