#pragma once
#include "tools.hpp"
//------------------------------------------------------------
template<class Item> class CList {
private:
	class Cell {
	public:
		unique_ptr<Item> data;
		Cell* next;
		Cell(Item p = nullptr, Cell *n = nullptr) :data(make_unique<Item>(p)), next(n) {}
		~Cell()= default;
	};
	int counter = 0;
	Cell* head;
	Cell* tail;
	Cell* current;
	Cell* removeFirst();
	Cell* removeAny();
public:
	CList(): head(new Cell()), tail(head), current(nullptr){}
	~CList();
	int count() {return counter;}
	bool empty() {return counter == 0;}
	ostream& print(ostream &out);
	void addCell(Item it);
	void init();
	Item next();
	void remove();
	Item getCurrent(){ return *current->data.get();}
	Item operator++(int);
};
//---------------------------------------------------------
template<class Item> inline ostream&
operator<<(ostream &out, CList<Item> &CL) {
	return CL.print(out);
}
//------------------------------------------------
template<class Item>
CList<Item>::~CList() {
	current = head;
	tail->next = nullptr;
	while (current != nullptr) {
		Cell* temp = current;
		current = current->next;
		delete temp;
		// actual size of CList = counter + 1(head);
		cout << "nCELLS = " << --counter<<endl;
	}
}
//------------------------------------------------
template<class Item> ostream&
CList<Item>::print(ostream &out) {
	Cell* tempPtr = head->next;
	if (tempPtr != nullptr) {
		do {
			out << **(tempPtr->data.get());
			tempPtr = tempPtr->next;
		} while (tempPtr != head);
	}
	return out;
}
//------------------------------------------------
template<class Item> void
CList<Item>::addCell(Item item) {
	Cell* cell = new Cell(item);
	tail->next = cell;
	tail = cell;
	cell->next = head;
	counter++;
}
//-------------------------------------------------
template<class Item> void
CList<Item>::init() {current = head->next;}
//------------------------------------------------
template <class Item> Item
CList<Item>::next() {
	current =current->next;
	if(current == head) current = head->next;
	return *current->data.get();
}
//------------------------------------------------
template<class Item> void
CList<Item>::remove() {
	Cell* nextCell = nullptr;
	if (current != nullptr) {
		if (current == head->next) {
			nextCell = removeFirst();
		} else {
			nextCell = removeAny();
		}
		counter--;
		delete current;
		current = nextCell;
	}
}
//-------------------------------------------------
template <class Item> typename CList<Item>::Cell*
CList<Item>::removeFirst(){
	Cell* nextCell = nullptr;
	if (current != tail) {
		head->next = current->next;
		nextCell = current->next;
	} else {
		tail = head;
		head->next = nullptr;
	}
	return nextCell;
}
//-------------------------------------------------
template <class Item> typename CList<Item>::Cell*
CList<Item>::removeAny(){
	Cell* nextCell = nullptr;
	Cell* tempPtr = head->next;
	while (tempPtr->next != current)
		tempPtr = tempPtr->next;
	tempPtr->next = nextCell = current->next;
	if (current == tail){
		tail = tempPtr;
		nextCell = head->next;
	}
	return nextCell;
}
//-------------------------------------------------------
template <class Item> Item
CList<Item>::operator++(int){
	Item temp = *current->data.get();
	next();
	return temp;
}
