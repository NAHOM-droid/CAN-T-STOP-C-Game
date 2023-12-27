#include "Column.hpp"
#include "Player.hpp"
#include "tools.hpp"
//-----------------------------------------------------------
const int Column::colLengths[13]= {0,0,3,5,7,9,11,13,11,9,7,5,3};
//-----------------------------------------------------------
bool Column::startTower(Player *p) {
	if (state != ColState::available) return false;
	int prev = content[(int) p->Color()];
	content[0] = ( prev> 0) ? prev + 1 : 1;
	state = (content[0] == colLengths[colNum]) ?
			ColState::pending : state;
	return true;
}
//----------------------------------------------------------
bool Column::move() {
	content[0]++;
	state = (content[0] == colLengths[colNum]) ? ColState::pending : state;
	return true;
}
//---------------------------------------------------------------
void Column::stop(Player* p){
    int colorIndex  = (int)p->Color();
    content[colorIndex] = content[0];
    if(content[0]==colLengths[colNum]){
       state = ColState::captured;
       p->wonColumn(colNum);
    }
    content[0] = 0;
}
//-----------------------------------------------
void Column::bust(){content[0] = 0;}
//------------------------------------------------
void Column::quit(Player* p){
	content[0] = 0;
	content[(int)p->Color()] = 0;
	const int* arr = p->getWonColumn();
	int score = p->Score();
	for(int k=0;k<score;k++) if(arr[k] == colNum) state = ColState::available;
}
//-----------------------------------------------
ostream& Column::print(ostream &out) {
	if(colNum<10) out<<" ";
	out << colNum << "  " << colStates[(int) state] << " ";
	string printArray[colLengths[colNum]];
	fill_n(printArray, colLengths[colNum], "-----");
	for (int k = 0; k < 5; k++) {
		if (content[k] != 0)
			printArray[content[k] - 1].replace(k, 1, towerMarker[k]);
	}
	for (string str : printArray) out << str << " ";
	out<<endl;
	return out;
}



