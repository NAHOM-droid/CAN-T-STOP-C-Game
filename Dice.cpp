#include "Dice.hpp"
#include "tools.hpp"
//Constructor with n value passed
Dice::Dice(int n = 1) {
	if(n < 1) n = 1;
	nDice = n;
	valuesArray = make_unique<int[]>(n);
	srand(time(NULL));
}
//Populating array with randon values -----------------
const int* Dice::roll() {
	for (int k = 0; k < nDice; k++) {
		valuesArray[k] = 1 + rand() % 6;
    }
	return valuesArray.get();
}
//Print Function  -------------------------------------
ostream& Dice::print(ostream& out) {
	char option = 'a';
	for (int k = 0; k < nDice; k++) {
		cout << option++ << ")" << valuesArray[k] << " ";
	}
	out<<endl;
	return out;
}

//---------------------------------------------------
//---------------------------------------------------
const int* CantStopDice::roll() {
	Dice::roll();
	const int* diceValues = Dice::getDiceValues();
	char input1, input2;
	for (;;) {
		try {
			Dice::print(cout);
			cout << "Choose 2 letters: ";
			cin >> input1 >> input2;
		    checkInput(diceValues, input1, input2);
			break;
		} catch (BadChoice& b) { b.print(); }
	}
	return totalPairs;
}
//-------------------------------------------------------------------------
void CantStopDice::checkInput(const int* diceValues, char input1, char input2){
	bool badSlot = strchr("abcd", input1) == NULL
			|| strchr("abcd", input2) == NULL;
	if (badSlot) throw BadSlot();
	if (input1 == input2) throw DuplicateSlot();
	int tot = 0;
	for (int k = 0; k < 4; k++) tot += diceValues[k];
	totalPairs[0] = diceValues[input1 - 'a'] + diceValues[input2 - 'a'];
	totalPairs[1] = tot - totalPairs[0];
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
const int* FakeDice::roll(ifstream& file){
	int diceValues[4];
	for(int k = 0;k<4;k++) file>>diceValues[k];
	char input1,input2;
	for (;;) {
		try {
			file >> input1 >> input2;
			cout<<"Dice Values: "<<diceValues[0]<<" "<<diceValues[1]<<" "<<diceValues[2]<<" "
					<<diceValues[3]<<"\nSelected dices: "<<input1<<" & "<<input2<<endl;
			checkInput(diceValues, input1, input2);
			break;
		} catch (BadSlot& b) { b.print(); }
		catch (DuplicateSlot& d) { d.print(); }
	}
	return totalPairs;
}

