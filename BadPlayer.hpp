#pragma once
#include "tools.hpp"
class BadPlayer {
public:
	string name;
	char color;
	BadPlayer(string name, char color):
		name(name), color(color){};
	virtual ~BadPlayer()=default;
	virtual void print(){
		cout<< "-------------Name and Color values already taken.-------------\n";
		pr();
	}
	void pr(){
		cout <<"You entered name: "<<name <<" & color: "
				<<color <<". Please reenter Player info. \n";
	}
};
//---------------------------------------------------
class BadName: public BadPlayer{
public:
	BadName(string name, char color): BadPlayer(name, color){};
	virtual ~BadName(){};
	virtual void print(){
		cout<< "-------------Name already taken.-------------\n";
		pr();
	}
};
//---------------------------------------------------
class BadColor: public BadPlayer{
public:
	BadColor(string name, char color): BadPlayer(name, color){};
	virtual ~BadColor(){};
	virtual void print(){
		cout<< "-------------This Color is not available.-------------\n";
		pr();
	}
};

