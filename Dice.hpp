#pragma once
#include "tools.hpp"
#include "BadChoice.hpp"

class Dice{
private:
	int nDice;
	unique_ptr<int[]> valuesArray;
public:
	Dice(int);
	virtual ~Dice()= default;
	virtual const int* roll();
	const int* getDiceValues(){return valuesArray.get();}
	ostream& print(ostream&);
};
inline ostream& operator<<(ostream& out, Dice& d){
    return d.print(out);
}
//----------------------------------------------------------------
class CantStopDice: public Dice {
protected:
	int totalPairs[2];
public:
	CantStopDice():Dice(4){}
	virtual ~CantStopDice() = default;
	virtual const int* roll();
    void checkInput(const int*, char, char);
};
//-------------------------------------------------------------------
class FakeDice: public CantStopDice {
public:
	FakeDice(): CantStopDice(){}
    ~FakeDice()= default;
	const int* roll(ifstream&);
};


