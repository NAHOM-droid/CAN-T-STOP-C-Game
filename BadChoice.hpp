#pragma once
#include "tools.hpp"

class BadChoice{
public:
	BadChoice(){};
	virtual ~BadChoice() = default;
	virtual void print() {
		cout << "-----------Bad choice entered.-----------\n";
		pr();
	}
    void pr(){cout<<"Please reenter your choice.\n\n";}
};
//---------------------------------------------------------
class DuplicateSlot: public BadChoice{
public:
	DuplicateSlot(){}
	virtual ~DuplicateSlot(){}
	virtual void print() {
		cout << "-----------Duplicate slot entered.-----------\n";
		pr();
	}
};
//----------------------------------------------------------
class BadSlot: public BadChoice{
public:
	BadSlot(){}
	virtual ~BadSlot(){}
	virtual void print() {
		cout << "-----------Bad slot entered.-----------\n";
		pr();
	}
};
